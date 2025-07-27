/*****************************************************************
* Dargon Programming Language
* (C) Kyle Morris 2025 - See LICENSE.txt for license information.
*
* @file drgMemUtil.h
* @author Kyle Morris
* @since v0.1
* @section Description
* Low-level memory utilities.
*
*****************************************************************/

#ifndef DRG_H_MEM_UTIL
#define DRG_H_MEM_UTIL

#include <stdint.h>
#include <stdlib.h>

// Convenience macro for freeing memory
// allocated via malloc().
#define DRG_MEM_FREE(ptr) \
    do { \
    if(ptr) { \
        free(ptr);\
        ptr = NULL;\
    }}\
    while(0)

// Wrapper around std realloc() that handles
// cases where new size is 0 (freeing data), as
// well as error handling.
void* drgMemReallocate(void* ptr, size_t prevSize, size_t newSize);

// Convenience macro for growing some
// dynamic memory space with an arbitrary
// minimum size (8) and growth rate (2).
// Perhaps this will be more generalized in
// the future.
#define DRG_MEM_GROW_CAPACITY(capacity) \
    (capacity < 8) ? 8 : (capacity * 2)

// Convenience macro for growing a
// dynamic memory space using drgMemReallocate().
#define DRG_MEM_GROW_ARRAY(type, ptr, prevCount, newCount)\
    (type*)drgMemReallocate(ptr, sizeof(type) * prevCount,\
        sizeof(type) * newCount)

// Convenience macro for freeing a
// dynamic memory space using drgMemReallocate().
#define DRG_MEM_FREE_ARRAY(type, ptr, prevCount)\
    drgMemReallocate(ptr, sizeof(type) * prevCount, 0)

#endif // DRG_H_MEM_UTIL
