#ifndef ALLOC_H
#define ALLOC_H

#include <stddef.h>
#include "objects.h"
#include "symbol.h"
#include "error.h"

extern unsigned int Freespace;
extern object *Freelist;

object *myalloc();

inline void myfree (object *obj) {
  car(obj) = NULL;
  cdr(obj) = Freelist;
  Freelist = obj;
  Freespace++;
}

#endif
