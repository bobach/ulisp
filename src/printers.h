#ifndef PRINTERS_H
#define PRINTERS_H

#include <Arduino.h>

#include "objects.h"
#include "function.h"
#include "io.h"

const int PPINDENT = 2;
const int PPWIDTH = 80;
const int ppspecials = 15;

const char ppspecial[ppspecials] PROGMEM = 
  { DOTIMES, DOLIST, IF, SETQ, TEE, LET, LETSTAR, LAMBDA, WHEN, UNLESS, WITHI2C, WITHSERIAL, WITHSPI, WITHSDCARD, FORMILLIS };

void pcount (char c);
int atomwidth (object *obj) ;
bool quoted (object *obj);
int subwidth (object *obj, int w);
int subwidthlist (object *form, int w);
void superprint (object *form, int lm, pfun_t pfun);
void supersub (object *form, int lm, int super, pfun_t pfun);

#endif
