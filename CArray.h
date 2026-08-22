//
// Created by root on 03/08/25.
//

#include <stdbool.h>
#include <stddef.h>

typedef struct CArray CArray;

struct CArray
{
    void *data;
    size_t size;
    size_t itemSize;
    int maxItemCount;
    int currentItemCount;
    int index;
};

void CArrayInit(CArray *array, size_t itemSize, size_t count);
void CArrayDestroy(CArray *array);
bool CArrayResize(CArray *array, int count);
void CArrayDeleteIndex(CArray *array, int index);
void CArrayInsertIndex(CArray *array, int index);
void CArraySwap(CArray *array, int indexA, int indexB);

int CArrayAppend(CArray *array);