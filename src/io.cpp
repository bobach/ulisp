#include "io.h"
#include "error.h"
#include "function.h"
#include "gstring.h"
#include "eval.h"
#include "ulisp/streams.h"
#include <limits.h>
#include "flags.h"

int digitvalue (char d) {
  if (d>='0' && d<='9') return d-'0';
  d = d | 0x20;
  if (d>='a' && d<='f') return d-'a'+10;
  return 16;
}


void testescape () {
  if (Serial.read() == '~') error2(0, PSTR("escape!"));
}

void pserial (char c) {
  LastPrint = c;
  if (c == '\n') Serial.write('\r');
  Serial.write(c);
}


void pcharacter (char c, pfun_t pfun) {
  if (!tstflag(PRINTREADABLY)) pfun(c);
  else {
    pfun('#'); pfun('\\');
    if (c > 32) pfun(c);
    else {
      const char *p = ControlCodes;
      while (c > 0) {p = p + strlen(p) + 1; c--; }
      pfstring(p, pfun);
    }
  }
}

void pstring (char *s, pfun_t pfun) {
  while (*s) pfun(*s++);
}

void printstring (object *form, pfun_t pfun) {
  if (tstflag(PRINTREADABLY)) pfun('"');
  form = cdr(form);
  while (form != NULL) {
    int chars = form->integer;
    for (int i=(sizeof(int)-1)*8; i>=0; i=i-8) {
      char ch = chars>>i & 0xFF;
      if (tstflag(PRINTREADABLY) && (ch == '"' || ch == '\\')) pfun('\\');
      if (ch) pfun(ch);
    }
    form = car(form);
  }
  if (tstflag(PRINTREADABLY)) pfun('"');
}

void pfstring (PGM_P s, pfun_t pfun) {
  int p = 0;
  while (1) {
    #if defined(__AVR_ATmega4809__) || defined(__AVR_ATtiny3216__)
    char c = s[p++];
    #else
    char c = pgm_read_byte(&s[p++]);
    #endif
    if (c == 0) return;
    pfun(c);
  }
}

void pint (int i, pfun_t pfun) {
  int lead = 0;
  #if INT_MAX == 32767
  int p = 10000;
  #else
  int p = 1000000000;
  #endif
  if (i<0) pfun('-');
  for (int d=p; d>0; d=d/10) {
    int j = i/d;
    if (j!=0 || lead || d==1) { pfun(abs(j)+'0'); lead=1;}
    i = i - j*d;
  }
}

void pfl (pfun_t pfun) {
  if (LastPrint != '\n') pfun('\n');
}

void printobject (object *form, pfun_t pfun){
  if (form == NULL) pfstring(PSTR("nil"), pfun);
  else if (listp(form) && issymbol(car(form), CLOSURE)) pfstring(PSTR("<closure>"), pfun);
  else if (listp(form)) {
    pfun('(');
    printobject(car(form), pfun);
    form = cdr(form);
    while (form != NULL && listp(form)) {
      pfun(' ');
      printobject(car(form), pfun);
      form = cdr(form);
    }
    if (form != NULL) {
      pfstring(PSTR(" . "), pfun);
      printobject(form, pfun);
    }
    pfun(')');
  } else if (integerp(form)) pint(form->integer, pfun);
  else if (symbolp(form)) { if (form->name != NOTHING) pstring(symbolname(form->name), pfun); }
  else if (characterp(form)) pcharacter(form->integer, pfun);
  else if (stringp(form)) printstring(form, pfun);
  else if (streamp(form)) {
    pfstring(PSTR("<"), pfun);
    if ((form->integer)>>8 == SPISTREAM) pfstring(PSTR("spi"), pfun);
    else if ((form->integer)>>8 == I2CSTREAM) pfstring(PSTR("i2c"), pfun);
    else if ((form->integer)>>8 == SDSTREAM) pfstring(PSTR("sd"), pfun);
    else pfstring(PSTR("serial"), pfun);
    pfstring(PSTR("-stream "), pfun);
    pint(form->integer & 0xFF, pfun);
    pfun('>');
  } else
    error2(0, PSTR("Error in print"));
}



int glibrary () {
  if (LastChar) { 
    char temp = LastChar;
    LastChar = 0;
    return temp;
  }
  #if defined(__AVR_ATmega4809__) || defined(__AVR_ATtiny3216__)
  char c = LispLibrary[GlobalStringIndex++];
  #else
  char c = pgm_read_byte(&LispLibrary[GlobalStringIndex++]);
  #endif
  return (c != 0) ? c : -1; // -1?
}

void loadfromlibrary (object *env) {   
  GlobalStringIndex = 0;
  object *line = read(glibrary);
  while (line != NULL) {
    eval(line, env);
    line = read(glibrary);
  }
}

int gserial () {
  if (LastChar) { 
    char temp = LastChar;
    LastChar = 0;
    return temp;
  }
  while (!Serial.available());
  char temp = Serial.read();
  if (temp != '\n') pserial(temp);
  return temp;
}

object *nextitem (gfun_t gfun) {
  int ch = gfun();
  while(isspace(ch)) ch = gfun();

  if (ch == ';') {
    while(ch != '(') ch = gfun();
    ch = '(';
  }
  if (ch == '\n') ch = gfun();
  if (ch == -1) return nil;
  if (ch == ')') return (object *)KET;
  if (ch == '(') return (object *)BRA;
  if (ch == '\'') return (object *)QUO;
  if (ch == '.') return (object *)DOT;

  // Parse string
  if (ch == '"') return readstring('"', gfun);
  
  // Parse symbol, character, or number
  int index = 0, base = 10, sign = 1;
  char *buffer = SymbolTop;
  int bufmax = maxbuffer(buffer); // Max index
  unsigned int result = 0;
  if (ch == '+') {
    buffer[index++] = ch;
    ch = gfun();
  } else if (ch == '-') {
    sign = -1;
    buffer[index++] = ch;
    ch = gfun();
  } else if (ch == '#') {
    ch = gfun();
    char ch2 = ch & ~0x20; // force to upper case
    if (ch == '\\') base = 0; // character
    else if (ch2 == 'B') base = 2;
    else if (ch2 == 'O') base = 8;
    else if (ch2 == 'X') base = 16;
    else if (ch == '\'') return nextitem(gfun);
    else if (ch == '.') {
      setflag(NOESC);
      object *result = eval(read(gfun), NULL);
      clrflag(NOESC);
      return result;
    } else error2(0, PSTR("illegal character after #"));
    ch = gfun();
  }
  int isnumber = (digitvalue(ch)<base);
  buffer[2] = '\0'; // In case symbol is one letter

  while(!isspace(ch) && ch != ')' && ch != '(' && index < bufmax) {
    buffer[index++] = ch;
    int temp = digitvalue(ch);
    result = result * base + temp;
    isnumber = isnumber && (digitvalue(ch)<base);
    ch = gfun();
  }

  buffer[index] = '\0';
  if (ch == ')' || ch == '(') LastChar = ch;

  if (isnumber) {
    if (base == 10 && result > ((unsigned int)INT_MAX+(1-sign)/2)) 
      error2(0, PSTR("Number out of range"));
    return number(result*sign);
  } else if (base == 0) {
    if (index == 1) return character(buffer[0]);
    PGM_P p = ControlCodes; char c = 0;
    while (c < 33) {
      #if defined(__AVR_ATmega4809__) || defined(__AVR_ATtiny3216__)
      if (strcasecmp(buffer, p) == 0) return character(c);
      p = p + strlen(p) + 1; c++;
      #else
      if (strcasecmp_P(buffer, p) == 0) return character(c);
      p = p + strlen_P(p) + 1; c++;
      #endif
    }
    error2(0, PSTR("Unknown character"));
  }
  
  int x = builtin(buffer);
  if (x == NIL) return nil;
  if (x < ENDFUNCTIONS) return newsymbol(x);
  else if (index < 4 && valid40(buffer)) return newsymbol(pack40(buffer));
  else return newsymbol(longsymbol(buffer));
}

object *readrest (gfun_t gfun) {
  object *item = nextitem(gfun);
  object *head = NULL;
  object *tail = NULL;

  while (item != (object *)KET) {
    if (item == (object *)BRA) {
      item = readrest(gfun);
    } else if (item == (object *)QUO) {
      item = cons(symbol(QUOTE), cons(read(gfun), NULL));
    } else if (item == (object *)DOT) {
      tail->cdr = read(gfun);
      if (readrest(gfun) != NULL) error2(0, PSTR("malformed list"));
      return head;
    } else {
      object *cell = cons(item, NULL);
      if (head == NULL) head = cell;
      else tail->cdr = cell;
      tail = cell;
      item = nextitem(gfun);
    }
  }
  return head;
}

object *read (gfun_t gfun) {
  object *item = nextitem(gfun);
  if (item == (object *)KET) error2(0, PSTR("incomplete list"));
  if (item == (object *)BRA) return readrest(gfun);
  if (item == (object *)DOT) return read(gfun);
  if (item == (object *)QUO) return cons(symbol(QUOTE), cons(read(gfun), NULL)); 
  return item;
}
