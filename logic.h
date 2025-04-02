#ifndef LOGIC_H
#define LOGIC_H

#include "appcontext.h"
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <math.h>

typedef enum {
    NotBin,
    NotDec,
    NotHex,
    TooLong,
    Ok,
} Errors;

Errors doTransmission(AppContext* context);
void updateNewNumberSystem(AppContext* context, int newNumberSystem);
void updateCurrentNumberSystem(AppContext* context, int currentNumberSystem);
void initialize(AppContext* context);
void update(AppContext* context, int newValue);
void updateCurrentNumber(AppContext* context, char* newValue);
void hexToDec(AppContext* context);
void binToDec(AppContext* context);
void binToHex(AppContext* context);
void decToBin(AppContext* context);
Errors checkConditions(AppContext* context);
int checkBinNumber(AppContext* context, int length);
int checkDecNumber(AppContext* context, int length);
int checkHexNumber(AppContext* context, int length);
void swapNumbers(AppContext* context);

#endif // LOGIC_H
