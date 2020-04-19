#ifndef SIZES_H
#define SIZES_H

#define BUFFERSIZE 18

#if defined(__AVR_ATmega328P__)
#define WORKSPACESIZE 315-SDSIZE        /* Objects (4*bytes) */
#define EEPROMSIZE 1024                 /* Bytes */
#define SYMBOLTABLESIZE BUFFERSIZE      /* Bytes - no long symbols */

#elif defined(__AVR_ATmega2560__)
#define WORKSPACESIZE 1214-SDSIZE       /* Objects (4*bytes) */
#define EEPROMSIZE 4096                 /* Bytes */
#define SYMBOLTABLESIZE 512             /* Bytes */

#elif defined(__AVR_ATmega1284P__)
#define WORKSPACESIZE (2816-SDSIZE)       /* Objects (4*bytes) */
#define EEPROMSIZE 4096                 /* Bytes */
#define SYMBOLTABLESIZE 512             /* Bytes */

#elif defined(ARDUINO_AVR_NANO_EVERY)
#define WORKSPACESIZE 1068-SDSIZE       /* Objects (4*bytes) */
#define EEPROMSIZE 256                  /* Bytes */
#define SYMBOLTABLESIZE BUFFERSIZE      /* Bytes - no long symbols */

#elif defined(ARDUINO_AVR_ATmega4809)   /* Curiosity Nano using MegaCoreX */
#define Serial Serial3
#define WORKSPACESIZE 1068-SDSIZE       /* Objects (4*bytes) */
#define EEPROMSIZE 256                  /* Bytes */
#define SYMBOLTABLESIZE BUFFERSIZE      /* Bytes - no long symbols */

#elif defined(__AVR_ATmega4809__)
#define WORKSPACESIZE 1068-SDSIZE       /* Objects (4*bytes) */
#define EEPROMSIZE 256                  /* Bytes */
#define SYMBOLTABLESIZE BUFFERSIZE      /* Bytes - no long symbols */

#elif defined(__AVR_ATtiny3216__)
#define WORKSPACESIZE 306-SDSIZE        /* Objects (4*bytes) */
#define EEPROMSIZE 256                  /* Bytes */
#define SYMBOLTABLESIZE BUFFERSIZE      /* Bytes - no long symbols */
#endif

  
#if defined(sdcardsupport)
#include <SD.h>
#define SDSIZE 172
#else
#define SDSIZE 0
#endif


  
#endif
