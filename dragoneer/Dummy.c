#include "Utils.h"
#include "ImplIList.h"

static TUnitPtrSize *CDummy_GetLength ( TVoidPtr self_, const float *a, float *b ) {
    IListPtr self = ( IListPtr ) self_;
}

TUnitPtrSize CDummy_GetLength2 () {
}

struct IList_Vft vft_IList = Implement_IList( CDummy );