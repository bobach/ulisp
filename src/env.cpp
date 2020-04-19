#include "env.h"
#include "symbol.h"
#include "function.h"


object *GlobalEnv;
object *tee;

void initenv () {
  GlobalEnv = nullptr;
  tee = symbol(TEE);
}


