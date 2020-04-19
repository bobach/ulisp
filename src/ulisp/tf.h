#ifndef TF_H
#define TF_H

#include "../objects.h"

object *tf_progn (object *form, object *env);

object *tf_if (object *args, object *env);

object *tf_cond (object *args, object *env);

object *tf_when (object *args, object *env);

object *tf_unless (object *args, object *env);

object *tf_case (object *args, object *env);

object *tf_and (object *args, object *env);

object *tf_or (object *args, object *env);

#endif
