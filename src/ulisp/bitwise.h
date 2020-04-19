#ifndef ULISP_BITWISE
#define ULISP_BITWISE

#include "arithmetic.h"
#include "../macros.h"
#include "../function.h"
#include "../objects.h"


// Bitwise operators
object *fn_logand  (object *args, object *env);
object *fn_logior  (object *args, object *env);
object *fn_logxor  (object *args, object *env);
object *fn_lognot  (object *args, object *env);
object *fn_ash     (object *args, object *env);
object *fn_logbitp (object *args, object *env);

#endif
