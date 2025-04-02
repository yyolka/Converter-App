#ifndef APPCONTEXT_H
#define APPCONTEXT_H

#define MAX_LENGTH 33
#define DEFAULT_SYSTEM 2
#define DEFAULT_VALUE "0"
#define DEC_MAX 2 ** 32 - 1
#define HEX_MAX "7FFFFFFF"

typedef struct {
    char currentValue[MAX_LENGTH];
    char newValue[MAX_LENGTH];
    int currentNumberSystem;
    int newNumberSystem;
} AppContext;

#endif // APPCONTEXT_H
