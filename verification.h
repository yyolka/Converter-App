#ifndef VERIFICATION_H
#define VERIFICATION_H

#include "entrypoint.h"

enum Errors {
    NotBin,
    NotDec,
    NotHex,
    TooLong,
    Ok
};

enum Errors checkConditions(AppContext* context);
int checkBinNumber(AppContext* context, int length);
int checkDecNumber(AppContext* context, int length);
int checkHexNumber(AppContext* context, int length);
int checkLen(AppContext* context, int length);

#endif // VERIFICATION_H
