#include "symbol.h"
#include "objects.h"
#include "function.h"
#include <string.h>
#include "error.h"

char SymbolTable[SYMBOLTABLESIZE];
char *SymbolTop = SymbolTable;

int fromradix40 (int n) {
  if (n >= 1 && n <= 26) return 'a'+n-1;
   if (n >= 30 && n <= 39) return '0'+n-30;
  return 0;
}

int pack40 (char *buffer) {
  return (((toradix40(buffer[0]) * 40) + toradix40(buffer[1])) * 40 + toradix40(buffer[2]));
}

bool valid40 (char *buffer) {
 return (toradix40(buffer[0]) >= 0 && toradix40(buffer[1]) >= 0 && toradix40(buffer[2]) >= 0);
}

char *symbolname (symbol_t x) {
  if (x < ENDFUNCTIONS) return lookupbuiltin(x);
  else if (x >= 64000) return lookupsymbol(x);
  char *buffer = SymbolTop;
  buffer[3] = '\0';
  for (int n=2; n>=0; n--) {
    buffer[n] = fromradix40(x % 40);
    x = x / 40;
  }
  return buffer;
}


int longsymbol (char *buffer) {
  char *p = SymbolTable;
  int i = 0;
  while (strcasecmp(p, buffer) != 0) {p = p + strlen(p) + 1; i++; }
  if (p == buffer) {
    // Add to symbol table?
    char *newtop = SymbolTop + strlen(p) + 1;
    if (SYMBOLTABLESIZE - (newtop - SymbolTable) < BUFFERSIZE) error2(0, PSTR("no room for long symbols"));
    SymbolTop = newtop;
  }
  if (i > 1535) error2(0, PSTR("Too many long symbols"));
  return i + 64000; // First number unused by radix40
}

char *lookupsymbol (symbol_t name) {
  char *p = SymbolTable;
  int i = name - 64000;
  while (i > 0 && p < SymbolTop) {p = p + strlen(p) + 1; i--; }
  if (p == SymbolTop) return NULL; else return p;
}

void deletesymbol (symbol_t name) {
  char *p = lookupsymbol(name);
  if (p == NULL) return;
  char *q = p + strlen(p) + 1;
  *p = '\0'; p++;
  while (q < SymbolTop) *(p++) = *(q++);
  SymbolTop = p;
}

int issymbol (object *obj, symbol_t n) {
  return symbolp(obj) && obj->name == n;
}

int toradix40 (char ch) {
  if (ch == 0) return 0;
  if (ch >= '0' && ch <= '9') return ch-'0'+30;
  ch = ch | 0x20;
  if (ch >= 'a' && ch <= 'z') return ch-'a'+1;
  return -1; // Invalid
}


