#ifndef LINKEDLIST_H_Elem
#define LINKEDLIST_H_Elem

#include "Utils.h"
#include <OOP/ImplIElemList.h>

struct ElemLinkedListNode;
typedef struct ElemLinkedListNode *TElemLinkedListNodePtr;

struct ElemLinkedListNode {
    Elem                   value;
    TElemLinkedListNodePtr next;
};

struct ElemLinkedList {
    TElemLinkedListNodePtr first;
    TElemLinkedListNodePtr last;
    TUintPtrSize           length;
    IElemList              asList;
};

typedef struct ElemLinkedList *ElemLinkedListPtr;

struct ElemLinkedList *ElemLinkedList_Create ();

#endif