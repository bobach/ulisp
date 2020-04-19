#ifndef TRACING_H
#define TRACING_H

#include "objects.h"

const int TRACEMAX = 3;
  
extern unsigned int TraceFn[TRACEMAX];
extern unsigned int TraceDepth[TRACEMAX];

bool tracing (symbol_t name);
void trace (symbol_t name);
void untrace (symbol_t name);

#endif
