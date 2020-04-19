#include "library.h"
#include "../gstring.h"
#include "../eval.h"

// LispLibrary

object *fn_require (object *args, object *env) {
#if !defined(__AVR_ATtiny3216__)
  object *arg = first(args);
  object *globals = GlobalEnv;
  if (!symbolp(arg)) error(REQUIRE, PSTR("argument is not a symbol"), arg);
  while (globals != NULL) {
    object *pair = first(globals);
    object *var = car(pair);
    if (symbolp(var) && var == arg) return nil;
    globals = cdr(globals);
  }
  GlobalStringIndex = 0;
  object *line = read(glibrary);
  while (line != NULL) {
    // Is this the definition we want
    int fname = first(line)->name;
    if ((fname == DEFUN || fname == DEFVAR) && symbolp(second(line)) && second(line)->name == arg->name) {
      eval(line, env);
      return tee;
    }
    line = read(glibrary);
  }
  return nil;
#else
  error2(REQUIRE, PSTR("not supported"));
#endif
}

object *fn_listlibrary (object *args, object *env) {
  (void) args, (void) env;
  GlobalStringIndex = 0;
  object *line = read(glibrary);
  while (line != NULL) {
    int fname = first(line)->name;
    if (fname == DEFUN || fname == DEFVAR) {
      pstring(symbolname(second(line)->name), pserial); pserial(' ');
    }
    line = read(glibrary);
  }
  return symbol(NOTHING); 
}
