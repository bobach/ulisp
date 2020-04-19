#ifndef SLEEP_H
#define SLEEP_H

#include "objects.h"
#include <Arduino.h>
// Sleep

void initsleep ();

object *fn_sleep (object *args, object *env);

void sleep (int secs);

#endif
