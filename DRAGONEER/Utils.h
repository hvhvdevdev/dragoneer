#ifndef DRAGONEER_UTILS_H
#define DRAGONEER_UTILS_H

#include <stdint.h>
#include <stdbool.h>

typedef intptr_t TIntPtrSize;
typedef int32_t  TInt32;
typedef int16_t  TInt16;
typedef int8_t   TInt8;

typedef uintptr_t TUnitPtrSize;
typedef uint32_t  TUint32;
typedef uint16_t  TUint16;
typedef uint8_t   TUint8;
typedef bool      TBool;

static const TBool c_true  = 1 == 1;
static const TBool c_false = 1 == 0;

typedef const uint8_t* TCStrPtr;

#endif //DRAGONEER_UTILS_H
