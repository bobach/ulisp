#include "objects.h"
#include "alloc.h"
#include "ulisp/list.h"
#include "workspace.h"
#include "function.h"

// Make each type of object

object *number (int n) {
  object *ptr = myalloc();
  ptr->type = NUMBER;
  ptr->integer = n;
  return ptr;
}

object *character (char c) {
  object *ptr = myalloc();
  ptr->type = CHARACTER;
  ptr->integer = c;
  return ptr;
}

object *cons (object *arg1, object *arg2) {
  object *ptr = myalloc();
  ptr->car = arg1;
  ptr->cdr = arg2;
  return ptr;
}

object *symbol (symbol_t name) {
  object *ptr = myalloc();
  ptr->type = SYMBOL;
  ptr->name = name;
  return ptr;
}

object *newsymbol (symbol_t name) {
  for (int i=WORKSPACESIZE-1; i>=0; i--) {
    object *obj = &Workspace[i];
    if (obj->type == SYMBOL && obj->name == name) return obj;
  }
    return symbol(name);
}

object *stream (unsigned char streamtype, unsigned char address) {
  object *ptr = myalloc();
  ptr->type = STREAM;
  ptr->integer = streamtype<<8 | address;
  return ptr;
}

int checkchar (symbol_t name, object *obj) {
  if (!characterp(obj)) error(name, PSTR("argument is not a character"), obj);
  return obj->integer;
}

void checkargs (symbol_t name, object *args) {
  int nargs = listlength(name, args);
  if (name >= ENDFUNCTIONS) error(0, PSTR("not valid here"), symbol(name));
  if (nargs<lookupmin(name)) error2(name, PSTR("has too few arguments"));
  if (nargs>lookupmax(name)) error2(name, PSTR("has too many arguments"));
}


int checkinteger (symbol_t name, object *obj) {
  if (!integerp(obj)) error(name, PSTR("argument is not an integer"), obj);
  return obj->integer;
}


int eq (object *arg1, object *arg2) {
  if (arg1 == arg2) return true;  // Same object
  if ((arg1 == nil) || (arg2 == nil)) return false;  // Not both values
  if (arg1->cdr != arg2->cdr) return false;  // Different values
  if (symbolp(arg1) && symbolp(arg2)) return true;  // Same symbol
  if (integerp(arg1) && integerp(arg2)) return true;  // Same integer
  if (characterp(arg1) && characterp(arg2)) return true;  // Same character
  return false;
}


bool consp (object *x) {
  if (x == NULL) return false;
  unsigned int type = x->type;
  return type >= PAIR || type == ZERO;
}

bool atom (object *x) {
  if (x == NULL) return true;
  unsigned int type = x->type;
  return type < PAIR && type != ZERO;
}

bool listp (object *x) {
  if (x == NULL) return true;
  unsigned int type = x->type;
  return type >= PAIR || type == ZERO;
}

bool improperp (object *x) {
  if (x == NULL) return false;
  unsigned int type = x->type;
  return type < PAIR && type != ZERO;
}

