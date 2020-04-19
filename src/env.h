#ifndef ENV_H
#define ENV_H

#include "objects.h"

extern object *GlobalEnv;
extern object *tee;

void initenv ();

#endif
