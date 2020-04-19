#include "alloc.h"

unsigned int Freespace = 0;
object *Freelist;

object *myalloc () {
  if (Freespace == 0) error2(0, PSTR("no room"));
  object *temp = Freelist;
  Freelist = cdr(Freelist);
  Freespace--;
  return temp;
}


