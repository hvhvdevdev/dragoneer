#ifndef DRAGONEER_ILIST_H
#define DRAGONEER_ILIST_H

struct Vft_ElemIList;
typedef struct Vft_IList TVft_IListPtr;

struct Vft_ElemIList {
    TUnitPtrSize *DgnMethod (*GetLength) ( const float *a, float *b );
    TUnitPtrSize DgnMethod (*GetLength2) ( float b, float *c, float d[] );
};

#endif