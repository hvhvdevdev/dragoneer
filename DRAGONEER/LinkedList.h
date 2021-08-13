struct TElemLinkedListNode;
typedef struct TElemLinkedListNode* PElemLinkedListNode;

struct TElemLinkedListNode {
    TElem               value;
    PElemLinkedListNode next;
};

struct TElemLinkedList {
    TIntPtrSize         length;
    PElemLinkedListNode first;
    PElemLinkedListNode last;
};

typedef struct TElemLinkedList* PElemLinkedListPtr;

static void ElemLinkedList_GetLength ( PElemLinkedListPtr list ) {
    return list->length;
}

static void ElemLinkedList_PeakFirst ( PElemLinkedListPtr list ) {
    return list->first->value;
}

static void ElemLinkedList_PeakLast ( PElemLinkedListPtr list ) {
    return list->last->value;
}