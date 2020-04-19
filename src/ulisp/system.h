#ifndef ULISP_SYSTEM_H
#define ULISP_SYSTEM_H

#include "../objects.h"

// System functions
object *fn_eval (object *args, object *env);

object *fn_globals (object *args, object *env);
object *fn_locals (object *args, object *env);

object *fn_makunbound (object *args, object *env);

object *fn_break (object *args, object *env);

object *fn_read (object *args, object *env);

object *fn_prin1 (object *args, object *env);
object *fn_print (object *args, object *env);

object *fn_princ (object *args, object *env);
object *fn_terpri (object *args, object *env);

object *fn_readbyte (object *args, object *env);
object *fn_readline (object *args, object *env);

object *fn_writebyte (object *args, object *env);
object *fn_writestring (object *args, object *env);
object *fn_writeline (object *args, object *env);

//really?
object *fn_restarti2c (object *args, object *env);

object *fn_gc (object *obj, object *env);
object *fn_room (object *args, object *env);

object *fn_saveimage (object *args, object *env);
object *fn_loadimage (object *args, object *env);
object *fn_cls (object *args, object *env);

#endif
