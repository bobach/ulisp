#ifndef ULISP_PRETTY_PRINT_H
#define ULISP_PRETTY_PRINT_H
#include "../objects.h"
#include "../symbol.h"
object *fn_pprint (object *args, object *env);
object *fn_pprintall (object *args, object *env);

#endif
