typedef float Elem; // fix IDE Problems

#include <Utils.h>
#include "LinkedList.h"

Implement_IElemList( ElemLinkedList );

struct ElemLinkedList *ElemLinkedList_Create () {
    ElemLinkedListPtr data = malloc( sizeof( struct ElemLinkedList ));
    data->last   = NULL;
    data->first  = NULL;
    data->length = 0;
    IElemList asList = { .pVft = &ElemLinkedList_IElemList_Vft, .obj =data };
    data->asList = asList;
    return data;
}

TUintPtrSize ElemLinkedList_GetLength ( TVoidPtr self ) {
    return (( ElemLinkedListPtr ) self )->length;
}

TBool ElemLinkedList_Append ( TVoidPtr _self, Elem item ) {
    ElemLinkedListPtr      self     = _self;
    TElemLinkedListNodePtr toInsert = malloc( sizeof( struct ElemLinkedListNode ));
    if ( toInsert == NULL) {
        return false;
    }
    toInsert->value = item;
    toInsert->next  = NULL;
    if ( self->first == NULL) {
        self->first = toInsert;
        self->last  = toInsert;
    } else {
        self->last->next = toInsert;
        self->last       = toInsert;
    }
    self->length += 1;
    return true;
}

Elem ElemLinkedList_GetFirst ( TVoidPtr _self ) {
    ElemLinkedListPtr self = _self;
    if ( self->first == NULL) {
        exit( EXIT_FAILURE );
    }
    return self->first->value;
}

Elem ElemLinkedList_GetLast ( TVoidPtr _self ) {
    ElemLinkedListPtr self = _self;
    if ( self->last == NULL) {
        exit( EXIT_FAILURE );
    }
    return self->last->value;
}

Elem ElemLinkedList_GetNth ( TVoidPtr _self, TUintPtrSize index ) {
    ElemLinkedListPtr      self = _self;
    TElemLinkedListNodePtr ptr  = self->first;
    if ( self->first == NULL) {
        exit( EXIT_FAILURE );
    }
    while ( index > 0 ) {
        if ( ptr->next == NULL) {
            exit( EXIT_FAILURE );
        }
        ptr = ptr->next;
        index--;
    }
    return ptr->value;
}

TBool ElemLinkedList_Prepend ( TVoidPtr _self, Elem item ) {
    ElemLinkedListPtr      self     = _self;
    TElemLinkedListNodePtr toInsert = malloc( sizeof( struct ElemLinkedListNode ));
    if ( toInsert == NULL) {
        return false;
    }
    toInsert->value = item;
    toInsert->next  = NULL;
    if ( self->first == NULL) {
        self->first = toInsert;
        self->last  = toInsert;
    } else {
        toInsert->next = self->first;
        self->first    = toInsert;
    }
    self->length++;
    return true;
}

TBool ElemLinkedList_InsertAt ( TVoidPtr _self, TUintPtrSize index, Elem item ) {
    ElemLinkedListPtr      self     = _self;
    TElemLinkedListNodePtr toInsert = malloc( sizeof( struct ElemLinkedListNode ));
    if ( toInsert == NULL) {
        return false;
    }
    toInsert->value = item;
    toInsert->next  = NULL;
    if ( self->first == NULL) {
        if ( index == 0 ) {
            return ElemLinkedList_Append( self, item );
        } else {
            return false;
        }
    } else {
        TElemLinkedListNodePtr ptr = self->first;
        while ( index > 1 ) {
            if ( ptr->next == NULL) {
                return false;
            }
            ptr = ptr->next;
            index--;
        }
        toInsert->next = ptr->next;
        ptr->next      = toInsert;
        if ( toInsert->next == NULL) {
            self->last = toInsert;
        }
    }
    self->length++;
    return true;
}

TBool ElemLinkedList_DelFirst ( TVoidPtr _self ) {
    ElemLinkedListPtr self = _self;
    if ( self->first == NULL) {
        return false;
    }
    if ( self->first == self->last ) {
        free( self->first );
        self->first  = NULL;
        self->last   = NULL;
        self->length = 0;
        return true;
    }
    TElemLinkedListNodePtr temp = self->first->next;
    free( self->first );
    self->first = temp;
    self->length--;
    return true;
}

TBool ElemLinkedList_DelLast ( TVoidPtr _self ) {
    ElemLinkedListPtr self = _self;
    if ( self->first == NULL) {
        return false;
    }
    if ( self->first == self->last ) {
        free( self->first );
        self->first  = NULL;
        self->last   = NULL;
        self->length = 0;
        return true;
    }
    return ElemLinkedList_DelNth( self, self->length - 1 );
}

TBool ElemLinkedList_DelNth ( TVoidPtr _self, TUintPtrSize index ) {
    ElemLinkedListPtr self = _self;
    if ( index == 0 ) {
        return ElemLinkedList_DelFirst( self );
    }
    TElemLinkedListNodePtr ptr = self->first;
    while ( index > 2 ) {
        if ( ptr->next == NULL) {
            return false;
        }
        ptr = ptr->next;
        index--;
    }
    if ( ptr->next == NULL) {
        return false;
    }
    TElemLinkedListNodePtr temp = ptr->next->next;
    free( ptr->next );
    ptr->next = temp;
    if ( ptr->next == NULL) {
        self->last = ptr;
    }
    self->length--;
    return true;
}