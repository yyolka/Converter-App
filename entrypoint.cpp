#include "entrypoint.h"

Errors doOperation(Operation operation, AppContext* context, AppParams* params) {
    Errors error = Ok;
    switch(operation) {
    case Transfer:
        error = doTransmission(context);
        break;
    case Initialization:
        initialize(context);
        break;
    case UpdateCurrentNumberSystem:
        updateCurrentNumberSystem(context, params->newSystem);
        break;
    case UpdateNewNumberSystem:
        updateNewNumberSystem(context, params->newSystem);
        break;
    case UpdateCurrentNumber:
        updateCurrentNumber(context, params->newValue);
        break;
    case ReverseSystems:
        swapNumbers(context);
        break;
    }

    return error;
}
