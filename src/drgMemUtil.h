/*****************************************************************
* Dargon Programming Language
* (C) Kyle Morris 2025 - See LICENSE.txt for license information.
*
* @file drgMemUtil.h
* @author Kyle Morris
* @since v0.1
* @section Description
* Multi-purpose memory utilities.
*
*****************************************************************/

#ifndef DRG_H_MEM_UTIL
#define DRG_H_MEM_UTIL

// Convenience function for freeing memory
// allocated via malloc().
#define DRG_MEM_FREE(ptr) \
    if(ptr) { \
        free(ptr);\
        ptr = NULL;\
    }

#endif // DRG_H_MEM_UTIL
