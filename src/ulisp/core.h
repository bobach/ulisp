#ifndef CORE_H
#define CORE_H

#include "../objects.h"

// Core functions
object *fn_not (object *args, object *env);

object *fn_cons (object *args, object *env);

object *fn_atom (object *args, object *env);

object *fn_listp (object *args, object *env);

object *fn_consp (object *args, object *env);

object *fn_symbolp (object *args, object *env);

object *fn_streamp (object *args, object *env);

object *fn_eq (object *args, object *env);

#endif
