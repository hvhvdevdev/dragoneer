#include <Utils.h>
#include <LinkedList.h>
#include <stdio.h>

int main () {
    ITFloatList myList = TFloatLinkedList_Create()->asList;
    ITFloatList_Append( &myList, 0.2f );
    ITFloatList_Append( &myList, 0.3f );
    ITFloatList_Append( &myList, 0.4f );
    ITFloatList_Prepend( &myList, 0.1f );
    ITFloatList_DelLast( &myList );
    ITFloatList_InsertAt( &myList, 0, -0.0001f );
    printf( "%i %f", ITFloatList_GetLength( &myList ), ITFloatList_GetNth( &myList, 3 ));
}