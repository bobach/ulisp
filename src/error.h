#ifndef ERROR_H
#define ERROR_H

#include <setjmp.h>
#include <avr/pgmspace.h>
#include "objects.h"

extern jmp_buf exception;

extern const char notanumber[] PROGMEM;
extern const char notastring[]  PROGMEM;
extern const char notalist[] PROGMEM;
extern const char notproper[] PROGMEM;
extern const char noargument[] PROGMEM;
extern const char nostream[]  PROGMEM;
extern const char overflow[] PROGMEM; 
extern const char invalidpin[]  PROGMEM; 
extern const char resultproper[] PROGMEM; 

void errorsub (symbol_t fname, PGM_P string);

void error (symbol_t fname, PGM_P string, object *symbol);

void error2 (symbol_t fname, PGM_P string);


#endif
