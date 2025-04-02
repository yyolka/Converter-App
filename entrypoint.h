#ifndef ENTRYPOINT_H
#define ENTRYPOINT_H

#include "logic.h"

typedef enum {
    Initialization,
    UpdateCurrentNumberSystem,
    UpdateNewNumberSystem,
    Transfer,
    UpdateCurrentNumber,
    ReverseSystems
} Operation;

typedef struct {
    int newSystem;
    char newValue[MAX_LENGTH];
} AppParams;

Errors doOperation(Operation operation, AppContext* context, AppParams* params);

#endif // ENTRYPOINT_H
