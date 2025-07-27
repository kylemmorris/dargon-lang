/*****************************************************************
* Dargon Programming Language
* (C) Kyle Morris 2025 - See LICENSE.txt for license information.
*
* @file drgValue.c
* @author Kyle Morris
* @since v0.1
* @section Description
* The virtual machine representation for values.
*
*****************************************************************/

#include <stdio.h>

#include "drgValue.h"

void drgValArrayInit(drgValArray* arr) {
    arr->capacity = 0;
    arr->count = 0;
    arr->values = NULL;
}

void drgValArrayAdd(drgValArray* arr, drgVal val) {
    if(arr->capacity < arr->count + 1) {
        int prevCapacity = arr->capacity;
        arr->capacity = DRG_MEM_GROW_CAPACITY(prevCapacity);
        arr->values = DRG_MEM_GROW_ARRAY(drgVal, arr->values, prevCapacity, arr->capacity);
    }
    arr->values[arr->count] = val;
    arr->count++;
}

void drgValArrayFree(drgValArray* arr) {
    DRG_MEM_FREE_ARRAY(drgVal, arr->values, arr->capacity);
    drgValArrayInit(arr);
}

void drgPrintVal(drgVal val) {
    printf("%g", val);
}