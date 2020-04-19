#ifndef STREAMS_H
#define STREAMS_H

#include "objects.h"
#include "io.h"

enum stream { SERIALSTREAM, I2CSTREAM, SPISTREAM, SDSTREAM};

void serialbegin (int address, int baud);

void serialend (int address);

gfun_t gstreamfun (object *args);

int isstream (object *obj);

inline void spiwrite (char c);
#if defined(__AVR_ATmega1284P__)
inline void serial1write (char c);
#elif defined(__AVR_ATmega2560__)
inline void serial1write (char c);
inline void serial2write (char c);
inline void serial3write (char c);
#endif

#if defined(sdcardsupport)
inline void SDwrite (char c);
#endif

pfun_t pstreamfun (object *args);

#endif
