#ifndef DRAGONEER_ILIST_H
#define DRAGONEER_ILIST_H

struct Vft_ElemIList;
typedef struct Vft_IList TVft_IListPtr;

struct Vft_ElemIList {
    TUnitPtrSize DgnMethod (* GetLength) ( TVft_IListPtr* list );
    TUnitPtrSize DgnMethod (* GetLength2) ( TVft_IListPtr* list );
};

#endif