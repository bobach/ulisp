#ifndef LIST_H
#define LIST_H

#include "../objects.h"

// Checked car and cdr

inline object *carx (object *arg) {
  //if (!listp(arg)) error(0, PSTR("Can't take car"), arg);
  if (arg == nil) return nil;
  return car(arg);
}

inline object *cdrx (object *arg) {
  //if (!listp(arg)) error(0, PSTR("Can't take cdr"), arg);
  if (arg == nil) return nil;
  return cdr(arg);
}

int listlength (symbol_t name, object *list);

object *assoc (object *key, object *list);
object *delassoc (object *key, object **alist);


// List functions

object *fn_car (object *args, object *env);

object *fn_cdr (object *args, object *env);
object *fn_caar (object *args, object *env);

object *fn_cadr (object *args, object *env);
object *fn_cdar (object *args, object *env);

object *fn_cddr (object *args, object *env);

object *fn_caaar (object *args, object *env);

object *fn_caadr (object *args, object *env);

object *fn_cadar (object *args, object *env);
object *fn_caddr (object *args, object *env);
object *fn_cdaar (object *args, object *env);
object *fn_cdadr (object *args, object *env);
object *fn_cddar (object *args, object *env);

object *fn_cdddr (object *args, object *env);

object *fn_length (object *args, object *env);

object *fn_list (object *args, object *env);

object *fn_reverse (object *args, object *env);

object *fn_nth (object *args, object *env);

object *fn_assoc (object *args, object *env);
object *fn_apply (object *args, object *env);
object *fn_append(object *args, object *env);


object *fn_funcall (object *args, object *env);
object *fn_mapc (object *args, object *env);
object *fn_mapcar (object *args, object *env);
object *fn_mapcan (object *args, object *env);
object *fn_member (object *args, object *env);

#endif
