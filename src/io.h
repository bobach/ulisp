#ifndef IO_H
#define IO_H

#include <Arduino.h>
#include "objects.h"

typedef int (*gfun_t)();
typedef void (*pfun_t)(char);


const char ControlCodes[] PROGMEM = "Null\0SOH\0STX\0ETX\0EOT\0ENQ\0ACK\0Bell\0Backspace\0Tab\0Newline\0VT\0"
"Page\0Return\0SO\0SI\0DLE\0DC1\0DC2\0DC3\0DC4\0NAK\0SYN\0ETB\0CAN\0EM\0SUB\0Escape\0FS\0GS\0RS\0US\0Space\0";

enum token { UNUSED, BRA, KET, QUO, DOT };

void testescape ();


inline int maxbuffer (char *buffer) {
  return SYMBOLTABLESIZE-(buffer-SymbolTable)-1;
}

int digitvalue (char d);


// Read functions
int glibrary ();

int gserial ();

object *nextitem (gfun_t gfun);

object *readrest (gfun_t gfun);

object *read (gfun_t gfun);


void pserial (char c);

void pcharacter (char c, pfun_t pfun);

void pstring (char *s, pfun_t pfun);

void printstring (object *form, pfun_t pfun);

void pfstring (PGM_P s, pfun_t pfun);


inline void pln (pfun_t pfun) {
  pfun('\n');
}
void pfl (pfun_t pfun);
void printobject (object *form, pfun_t pfun);

void pint (int i, pfun_t pfun);

#endif
