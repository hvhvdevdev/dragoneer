#ifndef DRAGONEER_UTILS_H
#define DRAGONEER_UTILS_H

#include <stdint.h>
#include <stdlib.h>
#include <stdbool.h>

#define DgnAssert( expr )  if (expr) {} else {puts("Failed: " #expr "\n");exit(EXIT_FAILURE);}

typedef float TFloat;

typedef intptr_t TIntPtrSize;
typedef int32_t  TInt32;
typedef int16_t  TInt16;
typedef int8_t   TInt8;

typedef uintptr_t TUintPtrSize;
typedef uint32_t  TUint32;
typedef uint16_t  TUint16;
typedef uint8_t   TUint8;
typedef bool      TBool;

typedef void *TVoidPtr;

typedef const uint8_t *TCStrPtr;

#endif //DRAGONEER_UTILS_H
