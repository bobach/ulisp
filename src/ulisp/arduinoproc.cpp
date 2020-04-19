#include "arduinoproc.h"

#include <Arduino.h>
#include "../macros.h"
#include "arithmetic.h"
#include "../objects.h"
#include "../function.h"
#include "../error.h"
#include "../sleep.h"


void checkanalogread (int pin) {
#if defined(__AVR_ATmega328P__)
  if (!(pin>=0 && pin<=5)) error(ANALOGREAD, invalidpin, number(pin));
#elif defined(__AVR_ATmega2560__)
  if (!(pin>=0 && pin<=15)) error(ANALOGREAD, invalidpin, number(pin));
#elif defined(__AVR_ATmega1284P__)
  if (!(pin>=0 && pin<=7)) error(ANALOGREAD, invalidpin, number(pin));
#elif defined(ARDUINO_AVR_ATmega4809)  /* MegaCoreX core */
  if (!((pin>=22 && pin<=33) || (pin>=36 && pin<=39))) error(ANALOGREAD, invalidpin, number(pin));
#elif defined(__AVR_ATmega4809__)
  if (!(pin>=14 && pin<=21)) error(ANALOGREAD, invalidpin, number(pin));
#elif defined(__AVR_ATtiny3216__)
 if (!((pin>=0 && pin<=5) || pin==8 || pin==9 || (pin>=14 && pin<=17))) error(ANALOGREAD, invalidpin, number(pin));
#endif
}

void checkanalogwrite (int pin) {
#if defined(__AVR_ATmega328P__)
  if (!(pin>=3 && pin<=11 && pin!=4 && pin!=7 && pin!=8)) error(ANALOGWRITE, invalidpin, number(pin));
#elif defined(__AVR_ATmega2560__)
  if (!((pin>=2 && pin<=13) || (pin>=44 && pin <=46))) error(ANALOGWRITE, invalidpin, number(pin));
#elif defined(__AVR_ATmega1284P__)
  if (!(pin==3 || pin==4 || pin==6 || pin==7 || (pin>=12 && pin<=15))) error(ANALOGWRITE, invalidpin, number(pin));
#elif defined(ARDUINO_AVR_ATmega4809)  /* MegaCoreX core */
  if (!((pin>=16 && pin<=19) || (pin>=38 && pin<=39))) error(ANALOGWRITE, invalidpin, number(pin));
#elif defined(__AVR_ATmega4809__)
  if (!(pin==3 || pin==5 || pin==6 || pin==9 || pin==10)) error(ANALOGWRITE, invalidpin, number(pin));
#elif defined(__AVR_ATtiny3216__)
  if (!((pin>=0 && pin<=2) || (pin>=7 && pin<=11) || pin==16)) error(ANALOGWRITE, invalidpin, number(pin));
#endif
}

object *fn_pinmode (object *args, object *env) {
  (void) env;
  int pin = checkinteger(PINMODE, first(args));
  PinMode pm = INPUT;
  object *mode = second(args);
  if (integerp(mode)) {
    int nmode = mode->integer;
    if (nmode == 1) pm = OUTPUT; else if (nmode == 2) pm = INPUT_PULLUP;
    #if defined(INPUT_PULLDOWN)
    else if (nmode == 4) pm = INPUT_PULLDOWN;
    #endif
  } else if (mode != nil) pm = OUTPUT;
  pinMode(pin, pm);
  return nil;
}

object *fn_digitalread (object *args, object *env) {
  (void) env;
  int pin = checkinteger(DIGITALREAD, first(args));
  if (digitalRead(pin) != 0) return tee; else return nil;
}

object *fn_digitalwrite (object *args, object *env) {
  (void) env;
  int pin = checkinteger(DIGITALWRITE, first(args));
  object *mode = second(args);
  if (integerp(mode)) digitalWrite(pin, mode->integer ? HIGH : LOW);
  else digitalWrite(pin, (mode != nil) ? HIGH : LOW);
  return mode;
}

object *fn_analogread (object *args, object *env) {
  (void) env;
  int pin = checkinteger(ANALOGREAD, first(args));
  checkanalogread(pin);
  return number(analogRead(pin));
}
 
object *fn_analogwrite (object *args, object *env) {
  (void) env;
  int pin = checkinteger(ANALOGWRITE, first(args));
  checkanalogwrite(pin);
  object *value = second(args);
  analogWrite(pin, checkinteger(ANALOGWRITE, value));
  return value;
}

object *fn_delay (object *args, object *env) {
  (void) env;
  object *arg1 = first(args);
  delay(checkinteger(DELAY, arg1));
  return arg1;
}

object *fn_millis (object *args, object *env) {
  (void) args, (void) env;
  return number(millis());
}

object *fn_sleep (object *args, object *env) {
  (void) env;
  object *arg1 = first(args);
  sleep(checkinteger(SLEEP, arg1));
  return arg1;
}
