#include "Utils.h"

struct SElemLinkedListNode;
typedef struct SElemLinkedListNode* TElemLinkedListNodePtr;

struct SElemLinkedListNode {
    TElem                  value;
    TElemLinkedListNodePtr next;
};

struct SElemLinkedList {
    TIntPtrSize            length;
    TElemLinkedListNodePtr first;
    TElemLinkedListNodePtr last;
};

typedef struct SElemLinkedList* TElemLinkedListPtr;

static inline void ElemLinkedList_GetLength ( TElemLinkedListPtr list ) {
    return list->length;
}

static inline void ElemLinkedList_PeakFirst ( TElemLinkedListPtr list ) {
    return list->first->value;
}

static inline void ElemLinkedList_PeakLast ( TElemLinkedListPtr list ) {
    return list->last->value;
}