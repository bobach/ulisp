#ifndef ARDUINOPROC_H
#define ARDUINOPROC_H

#include "../objects.h"

#if defined(__AVR_ATmega328P__) || defined(__AVR_ATmega2560__) || defined(__AVR_ATmega1284P__)
typedef int PinMode;
#endif


void checkanalogwrite(int pin);

void checkanalogread (int pin);

object *fn_pinmode (object *args, object *env);

object *fn_digitalread (object *args, object *env);

object *fn_digitalwrite (object *args, object *env);

object *fn_analogread (object *args, object *env);
 
object *fn_analogwrite (object *args, object *env);

object *fn_delay (object *args, object *env);

object *fn_millis (object *args, object *env);

object *fn_sleep (object *args, object *env);

#endif
