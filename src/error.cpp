
#include "error.h"

#include "printers.h"
#include "symbol.h"
#include "io.h"
#include "gc.h"
#include "macros.h"

jmp_buf exception;

const char notanumber[]   PROGMEM = "argument is not a number";
const char notastring[]   PROGMEM = "argument is not a string";
const char notalist[]     PROGMEM = "argument is not a list";
const char notproper[]    PROGMEM = "argument is not a proper list";
const char noargument[]   PROGMEM = "missing argument";
const char nostream[]     PROGMEM = "missing stream argument";
const char overflow[]     PROGMEM = "arithmetic overflow";
const char invalidpin[]   PROGMEM = "invalid pin";
const char resultproper[] PROGMEM = "result is not a proper list";

void errorsub (symbol_t fname, PGM_P string) {
  pfl(pserial); pfstring(PSTR("Error: "), pserial);
  if (fname) {
    pserial('\''); 
    pstring(symbolname(fname), pserial);
    pfstring(PSTR("' "), pserial);
  }
  pfstring(string, pserial);
}

void error (symbol_t fname, PGM_P string, object *symbol) {
  errorsub(fname, string);
  pfstring(PSTR(": "), pserial); printobject(symbol, pserial);
  pln(pserial);
  GCStack = NULL;
  longjmp(exception, 1);
}

void error2 (symbol_t fname, PGM_P string) {
  errorsub(fname, string);
  pln(pserial);
  GCStack = NULL;
  longjmp(exception, 1);
}
