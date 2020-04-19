#ifndef WORKSPACE_H
#define WORKSPACE_H

#define WORDALIGNED __attribute__((aligned (2)))

#include "objects.h"

extern object Workspace[WORKSPACESIZE] WORDALIGNED;

void initworkspace ();

#endif
