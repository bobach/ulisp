#include "prettyprint.h"
#include "../objects.h"
#include "../function.h"
#include "../printers.h"
#include "../env.h"
#include "../io.h"
#include "streams.h"

object *fn_pprint (object *args, object *env) {
  (void) env;
  object *obj = first(args);
  pfun_t pfun = pstreamfun(cdr(args));
  pln(pfun);
  superprint(obj, 0, pfun);
  return symbol(NOTHING);
}

object *fn_pprintall (object *args, object *env) {
  (void) args, (void) env;
  object *globals = GlobalEnv;
  while (globals != NULL) {
    object *pair = first(globals);
    object *var = car(pair);
    object *val = cdr(pair);
    pln(pserial);
    if (consp(val) && symbolp(car(val)) && car(val)->name == LAMBDA) {
      superprint(cons(symbol(DEFUN), cons(var, cdr(val))), 0, pserial);
    } else {
      superprint(cons(symbol(DEFVAR),cons(var,cons(cons(symbol(QUOTE),cons(val,NULL))
      ,NULL))), 0, pserial);
    }
    pln(pserial);
    globals = cdr(globals);
  }
  return symbol(NOTHING);
}
