#ifndef ULISP_LIBRARY_H
#define ULISP_LIBRARY_H

#include "../objects.h"
#include "../macros.h"
#include "../env.h"
//#include "symbol.h"
//#include "../ulisp.h"

object *fn_require (object *args, object *env);

object *fn_listlibrary (object *args, object *env);


#endif
