#include "string.h"
#include "../gstring.h"
#include "../gc.h"
#include "../eval.h"
#include "../env.h"
#include "../flags.h"

object *fn_stringp (object *args, object *env) {
  (void) env;
  return stringp(first(args)) ? tee : nil;
}

bool stringcompare (symbol_t name, object *args, bool lt, bool gt, bool eq) {
  object *arg1 = first(args); if (!stringp(arg1)) error(name, notastring, arg1);
  object *arg2 = second(args); if (!stringp(arg2)) error(name, notastring, arg2); 
  arg1 = cdr(arg1);
  arg2 = cdr(arg2);
  while ((arg1 != NULL) || (arg2 != NULL)) {
    if (arg1 == NULL) return lt;
    if (arg2 == NULL) return gt;
    if (arg1->integer < arg2->integer) return lt;
    if (arg1->integer > arg2->integer) return gt;
    arg1 = car(arg1);
    arg2 = car(arg2);
  }
  return eq;
}

object *fn_stringeq (object *args, object *env) {
  (void) env;
  return stringcompare(STRINGEQ, args, false, false, true) ? tee : nil;
}

object *fn_stringless (object *args, object *env) {
  (void) env;
  return stringcompare(STRINGLESS, args, true, false, false) ? tee : nil;
}

object *fn_stringgreater (object *args, object *env) {
  (void) env;
  return stringcompare(STRINGGREATER, args, false, true, false) ? tee : nil;
}

object *fn_sort (object *args, object *env) {
  if (first(args) == NULL) return nil;
  object *list = cons(nil,first(args));
  push(list,GCStack);
  object *predicate = second(args);
  object *compare = cons(NULL, cons(NULL, NULL));
  push(compare,GCStack);
  object *ptr = cdr(list);
  while (cdr(ptr) != NULL) {
    object *go = list;
    while (go != ptr) {
      car(compare) = car(cdr(ptr));
      car(cdr(compare)) = car(cdr(go));
      if (apply(SORT, predicate, compare, env)) break;
      go = cdr(go);
    }
    if (go != ptr) {
      object *obj = cdr(ptr);
      cdr(ptr) = cdr(obj);
      cdr(obj) = cdr(go);
      cdr(go) = obj;
    } else ptr = cdr(ptr);
  }
  pop(GCStack); pop(GCStack);
  return cdr(list);
}

object *fn_stringfn (object *args, object *env) {
  (void) env;
  object *arg = first(args);
  int type = arg->type;
  if (type == STRING) return arg;
  object *obj = myalloc();
  obj->type = STRING;
  if (type == CHARACTER) {
    object *cell = myalloc();
    cell->car = NULL;
    uint8_t shift = (sizeof(int)-1)*8;
    cell->integer = (arg->integer)<<shift;
    obj->cdr = cell;
  } else if (type == SYMBOL) {
    char *s = symbolname(arg->name);
    char ch = *s++;
    object *head = NULL;
    int chars = 0;
    while (ch) {
      if (ch == '\\') ch = *s++;
      buildstring(ch, &chars, &head);
      ch = *s++;
    }
    obj->cdr = head;
  } else error(STRINGFN, PSTR("can't convert to string"), arg);
  return obj;
}

object *fn_concatenate (object *args, object *env) {
  (void) env;
  object *arg = first(args);
  symbol_t name = arg->name;
  if (name != STRINGFN) error2(CONCATENATE, PSTR("only supports strings"));
  args = cdr(args);
  object *result = myalloc();
  result->type = STRING;
  object *head = NULL;
  int chars = 0;
  while (args != NULL) {
    object *obj = first(args);
    if (obj->type != STRING) error(CONCATENATE, notastring, obj);
    obj = cdr(obj);
    while (obj != NULL) {
      int quad = obj->integer;
      while (quad != 0) {
         char ch = quad>>((sizeof(int)-1)*8) & 0xFF;
         buildstring(ch, &chars, &head);
         quad = quad<<8;
      }
      obj = car(obj);
    }
    args = cdr(args);
  }
  result->cdr = head;
  return result;
}

object *fn_subseq (object *args, object *env) {
  (void) env;
  object *arg = first(args);
  if (!stringp(arg)) error(SUBSEQ, notastring, arg);
  int start = checkinteger(SUBSEQ, second(args));
  int end;
  args = cddr(args);
  if (args != NULL) end = checkinteger(SUBSEQ, car(args)); else end = stringlength(arg);
  object *result = myalloc();
  result->type = STRING;
  object *head = NULL;
  int chars = 0;
  for (int i=start; i<end; i++) {
    char ch = nthchar(arg, i);
    if (ch == 0) error2(SUBSEQ, PSTR("index out of range"));
    buildstring(ch, &chars, &head);
  }
  result->cdr = head;
  return result;
}

object *fn_princtostring (object *args, object *env) {   
  (void) env;
  object *arg = first(args);
  object *obj = myalloc();
  obj->type = STRING;
  GlobalString = NULL;
  GlobalStringIndex = 0;
  char temp = Flags;
  clrflag(PRINTREADABLY);
  printobject(arg, pstr);
  Flags = temp;
  obj->cdr = GlobalString;
  return obj;
}

object *fn_prin1tostring (object *args, object *env) {   
  (void) env;
  object *arg = first(args);
  object *obj = myalloc();
  obj->type = STRING;
  GlobalString = NULL;
  GlobalStringIndex = 0;
  printobject(arg, pstr);
  obj->cdr = GlobalString;
  return obj;
}

object *fn_readfromstring (object *args, object *env) {   
  (void) env;
  object *arg = first(args);
  if (!stringp(arg)) error(READFROMSTRING, notastring, arg);
  GlobalString = arg;
  GlobalStringIndex = 0;
  return read(gstr);
}
