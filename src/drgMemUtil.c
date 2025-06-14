/*****************************************************************
* Dargon Programming Language
* (C) Kyle Morris 2025 - See LICENSE.txt for license information.
*
* @file drgMemUtil.c
* @author Kyle Morris
* @since v0.1
* @section Description
* Low-level memory utilities.
*
*****************************************************************/

//#include <stdio.h>
#include "drgMemUtil.h"

void* drgMemReallocate(void* ptr, size_t prevSize, size_t newSize) {
    if(0 == newSize) {
        free(ptr);
        return NULL;
    }
    void* result = realloc(ptr, newSize);
    if(result == NULL) {
        //perror("drgMemReallocate: realloc() returned null!");
        exit(1);
    }
    return result;
}