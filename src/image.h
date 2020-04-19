#ifndef IMAGE_H
#define IMAGE_H

#include "objects.h"

// Compact image

static void movepointer (object *from, object *to);

char *MakeFilename(object *arg);

int compactimage (object **arg);

// Save-image and load-image

#if defined(sdcardsupport)
void SDWriteInt (File file, int data);
#else
void EEPROMWriteInt (unsigned int *addr, int data);
#endif

unsigned int saveimage (object *arg);

#if defined(sdcardsupport)
int SDReadInt (File file);
#else
int EEPROMReadInt (unsigned int *addr);
#endif

unsigned int loadimage (object *arg);

void autorunimage ();

#endif
