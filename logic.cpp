#include "logic.h"

void updateCurrentNumberSystem(AppContext* context, int currentNumberSystem) {
    context->currentNumberSystem = currentNumberSystem;
}

void updateNewNumberSystem(AppContext* context, int newNumberSystem) {
    context->newNumberSystem = newNumberSystem;
}

void updateCurrentNumber(AppContext* context, char* newValue) {
    strcpy(context->currentValue, newValue);
}

void swapNumbers(AppContext* context) {
    int tempSystem = context->currentNumberSystem;
    context->currentNumberSystem = context->newNumberSystem;
    context->newNumberSystem = tempSystem;
    char* tempNumber = context->currentValue;
    strcpy(context->currentValue, context->newValue);
    strcpy(context->newValue,tempNumber);
}

void initialize(AppContext* context) {
    strcpy(context->currentValue, DEFAULT_VALUE);
    context->currentNumberSystem = 2;
    context->newNumberSystem = 2;
}

void update(AppContext* context, int newValue) {
    sprintf(context->newValue, "%d", newValue);
}

Errors doTransmission(AppContext* context) {
    Errors status = Ok;
    if (checkConditions(context) != Ok)
        status = checkConditions(context);
    else {
        strcpy(context->newValue, context->currentValue);
        if (context->currentNumberSystem == 2 and context->newNumberSystem == 10)
            binToDec(context);
        else if (context->currentNumberSystem == 2 and context->newNumberSystem == 16)
            binToHex(context);
        else if (context->currentNumberSystem == 10 and context->newNumberSystem == 2)
            decToBin(context);
        else if (context->currentNumberSystem == 16 and context->newNumberSystem == 10)
            hexToDec(context);
        else if (context->currentNumberSystem == 16 and context->newNumberSystem == 2) {
            hexToDec(context);
            decToBin(context);
        }
        else if (context->currentNumberSystem == 10 and context->newNumberSystem == 16) {
            decToBin(context);
            binToHex(context);
        }
    }
    return status;
}

void hexToDec(AppContext* context) {
    int decimalValue = 0;
    int length = strlen(context->currentValue);
    for (int i = 0; i < length; i++) {
        char c = context->newValue[i];
        int digit;
        if (c >= '0' && c <= '9')
            digit = c - '0';
        else
            digit = c - 'A' + 10;
        decimalValue = decimalValue * 16 + digit;
    }
    update(context, decimalValue);
}

void binToDec(AppContext* context) {
    int decimalValue = 0;
    for (int i = 0; i < MAX_LENGTH - 1; i++) {
        char c = context->newValue[i];
        decimalValue = decimalValue * 2 + (c - '0');
    }
    update(context, decimalValue);
}

void decToBin(AppContext* context) {
    int temp = atoi(context->newValue);
    bool isNegative = false;
    char* binValue = (char *) malloc (MAX_LENGTH);
    for (int i = 0; i < MAX_LENGTH - 1; i++)
        binValue[i] = '0';
    binValue[MAX_LENGTH - 1] = '\0';
    if (temp < 0) {
        isNegative = true;
        temp = ~(temp) + 1;
    }
    for (int i = MAX_LENGTH - 2; i >= 0; i--) {
        binValue[i] = (temp % 2) + '0';
        temp /= 2;
    }
    if (isNegative) {
        for (int i = 0; i < MAX_LENGTH - 1; i++)
            binValue[i] = (binValue[i] == '1') ? '0' : '1';
        for (int i = MAX_LENGTH - 2; i >= 0; i--) {
            if (binValue[i] == '0') {
                binValue[i] = '1';
                break;
            }
            else
                binValue[i] = '0';
        }
    }
    strcpy(context->newValue, binValue);
    free(binValue);
}

void binToHex(AppContext* context) {
    int hexLen = (MAX_LENGTH + 3) / 4;
    char* hex = (char *) malloc (hexLen + 1);
    for (int i = 0; i < hexLen; i++) {
        hex[i] = '0';
    }
    int hexIndex = hexLen - 1;
    int binaryIndex = MAX_LENGTH - 1;
    while (binaryIndex > 0) {
        int decimalValue = 0;
        for (int i = 0; i < 4 && binaryIndex >= 0; i++) {
            decimalValue += (context->newValue[--binaryIndex] - '0') * (1 << i);
        }
        if (decimalValue < 10) {
            hex[hexIndex--] = decimalValue + '0';
        } else {
            hex[hexIndex--] = decimalValue - 10 + 'A';
        }
    }
    strncpy(context->newValue, hex, hexLen + 1);
    context->newValue[hexLen] = '\0';
    free(hex);
}

Errors checkConditions(AppContext* context) {
    Errors status = Ok;
    int length = strlen(context->currentValue);
    if (context->currentNumberSystem == 2) {
        if (checkBinNumber(context, length))
            status= NotBin;
    }
    else if (context->currentNumberSystem == 16) {
        if (checkHexNumber(context, length))
            status = NotHex;
        if (length > 9)
            status = TooLong;
    }
    else if (context->currentNumberSystem == 10) {
        if (checkDecNumber(context, length))
            status = NotDec;
        if (atoll(context->currentValue) > INT_MAX)
            status = TooLong;
    }
    return status;
}

int checkBinNumber(AppContext* context, int length) {
    int status = 0;
    for (int i = 0; i < length; i++) {
        char c = context->currentValue[i];
        if ((c >= '0' and c <= '1') == 0) {
            status = 1;
            break;
        }
    }
    return status;
}

int checkHexNumber(AppContext* context, int length) {
    int status = 0;
    for (int i = 0; i < length; i++) {
        char c = context->currentValue[i];
        if (((c >= 'A' and c <= 'F') or (c >= '0' and c <= '9')) == 0) {
            status = 1;
            break;
        }
    }
    return status;
}

int checkDecNumber(AppContext* context, int length) {
    int status = 0;
    for (int i = 0; i < length; i++) {
        char c = context->currentValue[i];
        if ((c >= '0' and c <= '9') == 0 ) {
            if (i == 0 and c == '-') {
                continue;
            }
            else {
                status = 1;
                break;
            }
        }
    }
    return status;
}

