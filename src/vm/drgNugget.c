/*****************************************************************
* Dargon Programming Language
* (C) Kyle Morris 2025 - See LICENSE.txt for license information.
*
* @file drgNugget.c
* @author Kyle Morris
* @since v0.1
* @section Description
* In Dargon terminology, a Nugget is a group of bytecode.
*
*****************************************************************/

/* #include "drgNugget.h"
#include "drgMemUtil.h"

void drgNuggetInit(drgNugget* nugget) {
    nugget->count = 0;
    nugget->capacity = 0;
    nugget->bytecode = NULL;
    drgValArrayInit(&nugget->constantPool);
}

void drgNuggetAdd(drgNugget* nugget, drgByte byte) {
    if(nugget->capacity < nugget->count + 1) {
        int prevCapacity = nugget->capacity;
        nugget->capacity = DRG_MEM_GROW_CAPACITY(prevCapacity);
        nugget->bytecode = DRG_MEM_GROW_ARRAY(drgByte, nugget->bytecode, prevCapacity, nugget->capacity);
    }
    nugget->bytecode[nugget->count] = byte;
    nugget->count++;
}

int drgNuggetAddLiteral(drgNugget* nugget, drgVal constant) {
    drgValArrayAdd(&nugget->constantPool, constant);
    return nugget->constantPool.count - 1;
}

void drgNuggetFree(drgNugget* nugget) {
    DRG_MEM_FREE_ARRAY(drgByte, nugget->bytecode, nugget->capacity);
    drgValArrayFree(&nugget->constantPool);
    drgNuggetInit(nugget);
} */