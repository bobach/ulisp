#ifndef ARITHMETIC_H
#define ARITHMETIC_H

#include "../objects.h"
#include "../macros.h"
#include "../env.h"


object *fn_add (object *args, object *env);

object *fn_subtract (object *args, object *env);

object *fn_multiply (object *args, object *env);

object *fn_divide (object *args, object *env);

object *fn_mod (object *args, object *env);

object *fn_oneplus (object *args, object *env);

object *fn_oneminus (object *args, object *env);

object *fn_abs (object *args, object *env);
object *fn_random (object *args, object *env);
object *fn_maxfn (object *args, object *env);
object *fn_minfn (object *args, object *env);



object *fn_noteq (object *args, object *env);
object *fn_numeq (object *args, object *env);

object *fn_less (object *args, object *env);

object *fn_lesseq (object *args, object *env);

object *fn_greater (object *args, object *env);

object *fn_greatereq (object *args, object *env);
object *fn_plusp (object *args, object *env);

object *fn_minusp (object *args, object *env);

object *fn_zerop (object *args, object *env);

object *fn_oddp (object *args, object *env);

object *fn_evenp (object *args, object *env);
#endif
