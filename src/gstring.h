#ifndef GSTRING_H
#define GSTRING_H

#include "objects.h"
#include "alloc.h"
#include "function.h"
#include "io.h"


extern object *GlobalString;
extern int GlobalStringIndex;

extern char LastChar;
extern char LastPrint;

object *value (symbol_t n, object *env);

void indent (int spaces, pfun_t pfun);

void buildstring (char ch, int *chars, object **head);

object *readstring (char delim, gfun_t gfun);

int stringlength (object *form);

char nthchar (object *string, int n);

int gstr ();

void pstr (char c);

#endif
