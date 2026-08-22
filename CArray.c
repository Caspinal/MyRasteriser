//
// Created by root on 03/08/25.
//

#include "CArray.h"

#include <stdbool.h>
#include <stddef.h>
#include <stdlib.h>
#include <string.h>

void CArrayInit(CArray *array, size_t itemSize, size_t maxItemCount)
{

    array->maxItemCount = maxItemCount;
    array->size = itemSize * maxItemCount;
    array->itemSize = itemSize;
    array->currentItemCount = 0;
    array->data = malloc(array->size);
}

bool CArrayResize(CArray *array, int maxItemCount)
{
    bool sucess = false;

    size_t newSize = array->itemSize * maxItemCount;

    void *newData = realloc(array->data, newSize);

    if (newData != NULL)
    {
        array->data = newData;
        array->maxItemCount = maxItemCount;
        array->size = newSize;
        sucess = true;
    };

    return sucess;
}

void CArrayDestroy(CArray *array)
{
    free(array->data);
}

void CArrayDeleteIndex(CArray *array, int index)
{
    // if at end?

    // if in between;
    size_t dstOffset = array->itemSize * index;
    size_t srcOffset = array->itemSize * (index + 1);
    size_t moveSize = (array->itemSize * array->maxItemCount) - srcOffset;
    void *dst = array->data + dstOffset;
    void *src = array->data + srcOffset;
    memmove(dst, src, moveSize);
    array->currentItemCount--;
}

void CArrayInsertIndex(CArray *array, int index)
{
    size_t dstOffset = array->itemSize * (index + 1);
    size_t srcOffset = array->itemSize * (index);
    size_t moveSize = (array->itemSize * array->maxItemCount) - srcOffset;
    void *dst = array->data + dstOffset;
    void *src = array->data + srcOffset;
    memmove(dst, src, moveSize);

    array->currentItemCount++;
}

int CArrayAppend(CArray *array)
{
    int last = -1;
    if (array->currentItemCount + 1 <= array->maxItemCount)
    {
        last = array->currentItemCount;
        array->currentItemCount++;
    }
    return last;
}

void CArraySwap(CArray *array, int indexA, int indexB)
{
    size_t AOffset = array->itemSize * (indexA);
    size_t BOffset = array->itemSize * (indexB);
    void *tmp = malloc(array->itemSize);

    void *a = array->data + AOffset;
    void *b = array->data + BOffset;

    memcpy(tmp, a, array->itemSize);
    memcpy(a, b, array->itemSize);
    memcpy(b, tmp, array->itemSize);

    free(tmp);
}