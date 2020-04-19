#ifndef GC_H
#define GC_H

#include "objects.h"

#define mark(x)            (car(x) = (object *)(((uintptr_t)(car(x))) | MARKBIT))
#define unmark(x)          (car(x) = (object *)(((uintptr_t)(car(x))) & ~MARKBIT))
#define marked(x)          ((((uintptr_t)(car(x))) & MARKBIT) != 0)
#define MARKBIT            1


extern object *GCStack;

void markobject(object *obj);

void sweep();

void gc(object *from, object *env);

#endif
