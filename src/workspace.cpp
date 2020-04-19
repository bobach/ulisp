#include "workspace.h"
#include "macros.h"
#include "gc.h"
#include "alloc.h"

object Workspace[WORKSPACESIZE] WORDALIGNED;

// Set up workspace
void initworkspace () {
  Freelist = NULL;
  for (int i=WORKSPACESIZE-1; i>=0; i--) {
    object *obj = &Workspace[i];
    car(obj) = NULL;
    cdr(obj) = Freelist;
    Freelist = obj;
    Freespace++;
  }
}
