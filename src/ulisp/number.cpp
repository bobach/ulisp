#include "number.h"
#include "../macros.h"
#include "../env.h"

// Number functions

object *fn_integerp (object *args, object *env) {
  (void) env;
  return integerp(first(args)) ? tee : nil;
}

object *fn_numberp (object *args, object *env) {
  (void) env;
  return integerp(first(args)) ? tee : nil;
}

