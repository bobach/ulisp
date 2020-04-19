#ifndef ULISP_STRING_H
#define ULISP_STRING_H
#include "../objects.h"

object *fn_stringp (object *args, object *env);

bool stringcompare (symbol_t name, object *args, bool lt, bool gt, bool eq);

object *fn_stringeq (object *args, object *env);

object *fn_stringless (object *args, object *env);

object *fn_stringgreater (object *args, object *env);

object *fn_sort (object *args, object *env);

object *fn_stringfn (object *args, object *env);

object *fn_concatenate (object *args, object *env);

object *fn_subseq (object *args, object *env);

object *fn_princtostring (object *args, object *env);

object *fn_prin1tostring (object *args, object *env);

object *fn_readfromstring (object *args, object *env);
#endif
