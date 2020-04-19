#ifndef SYMBOL_H
#define SYMBOL_H
#include "sizes.h"

typedef unsigned int symbol_t;

extern char SymbolTable[SYMBOLTABLESIZE];
extern char *SymbolTop;

int toradix40 (char ch);
int fromradix40 (int n);
int pack40 (char *buffer);
bool valid40 (char *buffer);


char *symbolname (symbol_t x);

int longsymbol (char *buffer);

char *lookupsymbol (symbol_t name);

void deletesymbol (symbol_t name);



#endif
