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

#include "drgNugget.h"
#include "drgMemUtil.h"

void drgNuggetInit(drgNugget* nugget) {
    nugget->count = 0;
    nugget->capacity = 0;
    nugget->bytecode = NULL;
    drgValArrayInit(&nugget->constants);
}

void drgNuggetAdd(drgNugget* nugget, uint8_t byte) {
    if(nugget->capacity < nugget->count + 1) {
        int prevCapacity = nugget->capacity;
        nugget->capacity = DRG_MEM_GROW_CAPACITY(prevCapacity);
        nugget->bytecode = DRG_MEM_GROW_ARRAY(uint8_t, nugget->bytecode, prevCapacity, nugget->capacity);
    }
    nugget->bytecode[nugget->count] = byte;
    nugget->count++;
}

int drgNuggetAddConstant(drgNugget* nugget, drgVal constant) {
    drgValArrayAdd(&nugget->constants, constant);
    return nugget->constants.count - 1;
}

void drgNuggetFree(drgNugget* nugget) {
    DRG_MEM_FREE_ARRAY(uint8_t, nugget->bytecode, nugget->capacity);
    drgValArrayFree(&nugget->constants);
    drgNuggetInit(nugget);
}