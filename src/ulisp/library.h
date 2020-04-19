#ifndef ULISP_LIBRARY_H
#define ULISP_LIBRARY_H

#include "../objects.h"
#include "../env.h"

object *fn_require (object *args, object *env);

object *fn_listlibrary (object *args, object *env);


#endif
