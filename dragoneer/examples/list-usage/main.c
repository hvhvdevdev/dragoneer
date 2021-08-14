#include <Utils.h>
#include <LinkedList.h>
#include <stdio.h>

int main () {
    ITFloatList myList = TFloatLinkedList_Create()->asList;
    ITFloatList_Append( &myList, 0.1f );
    ITFloatList_Append( &myList, 0.02f );
    ITFloatList_Append( &myList, 0.03f );
    ITFloatList_Prepend( &myList, 0.06f );
    ITFloatList_InsertAt( &myList, 2, 0.011f );
    printf( "%i %f", ITFloatList_GetLength( &myList ), ITFloatList_GetNth( &myList, 0 ));
}