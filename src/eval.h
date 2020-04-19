#ifndef EVAL_H
#define EVAL_H

#include "objects.h"
#include <stdint.h>


extern char BreakLevel;

extern uint8_t End;

object *eval (object *form, object *env);
object *apply (symbol_t name, object *function, object *args, object *env);


object *closure (int tc, symbol_t name,
		 object *state, object *function,
		 object *args,  object **env);

object **place(symbol_t name, object *args, object *env);

void repl (object *env);
  

#endif
