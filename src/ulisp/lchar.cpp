#include "lchar.h"
#include "../macros.h"
#include "../function.h"
#include "../error.h"
#include "../gstring.h"
#include "../env.h"

// Characters

object *fn_char (object *args, object *env) {
  (void) env;
  object *arg = first(args);
  if (!stringp(arg)) error(CHAR, notastring, arg);
  char c = nthchar(arg, checkinteger(CHAR, second(args)));
  if (c == 0) error2(CHAR, PSTR("index out of range"));
  return character(c);
}

object *fn_charcode (object *args, object *env) {
  (void) env;
  return number(checkchar(CHARCODE, first(args)));
}

object *fn_codechar (object *args, object *env) {
  (void) env;
  return character(checkinteger(CODECHAR, first(args)));
}

object *fn_characterp (object *args, object *env) {
  (void) env;
  return characterp(first(args)) ? tee : nil;
}
