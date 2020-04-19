/* uLisp AVR Version 3.0b - www.ulisp.com
   David Johnson-Davies - www.technoblogy.com - 11th January 2020
   Licensed under the MIT license: https://opensource.org/licenses/MIT
*/

// Lisp Library
// Compile options

// #define checkoverflow
// #define resetautorun
// #define printfreespace
// #define serialmonitor
// #define printgcs
// #define sdcardsupport
// #define lisplibrary


#if defined(__AVR_ATmega4809__) || defined(__AVR_ATtiny3216__)
#define PROGMEM
#define PSTR(s) (s)
#endif

#include <Arduino.h>

#include "objects.h"
#include "io.h"
#include "workspace.h"
#include "env.h"
#include "sleep.h"
#include "eval.h"
#include "image.h"
#include "error.h"
#include "tracing.h"

#define SDCARD_SS_PIN 10

// Print functions
void setup () {
  Serial.begin(230400);

  #if defined(ARDUINO_AVR_NANO_EVERY) || defined(ARDUINO_AVR_ATmega4809)
  delay(2500);
  #else
  int start = millis();
  while ((millis() - start) < 5000) { if (Serial) break; }
  #endif

  initworkspace();
  initenv();
  initsleep();
  
  pfstring(PSTR("uLisp 3.0 "), pserial); pln(pserial);
}

void loop () {
  End = 0xA5;      // Canary to check stack
  if (!setjmp(exception)) {
    #if defined(resetautorun)
    volatile int autorun = 12; // Fudge to keep code size the same
    #else
    volatile int autorun = 13;
    #endif
    if (autorun == 12) autorunimage();
  }
  // Come here after error
  delay(100); while (Serial.available()) Serial.read();
  for (int i=0; i<TRACEMAX; i++) TraceDepth[i] = 0;
  #if defined(sdcardsupport)
  SDpfile.close(); SDgfile.close();
  #endif
  #if defined(lisplibrary)
  if (!tstflag(LIBRARYLOADED)) { setflag(LIBRARYLOADED); loadfromlibrary(NULL); }
  #endif
  repl(NULL);
}
