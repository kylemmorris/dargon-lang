/*****************************************************************
* Dargon Programming Language
* (C) Kyle Morris 2025 - See LICENSE.txt for license information.
*
* @file Toolbox.h
* @author Kyle Morris
* @since v0.1
* @section Description
* Contains stand-alone utility functions that are used
* throughout the codebase.
*****************************************************************/

#ifndef DRG_H_TOOLBOX
#define DRG_H_TOOLBOX

#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include <stddef.h>
#include <stdbool.h>

#include "Log.h"

/// @brief Safer version of std free().
/// @param ptr 
void D_Free(void* ptr) {
    if(ptr) {
        free(ptr);
        ptr = NULL;
    }
}

/// @brief Trims leading + trailing spaces from the string.
/// @param str The input string.
/// @return Pointer to a substring of the input, including
/// an additional null character at the end.
/// NOTE:
/// If the given string was malloc'd, you MUST NOT
/// overwrite the original ptr with this return value.
/// NOTE: 
/// The return value must NOT be free'd.
char* D_TrimString(char* str) {
    char* end;
    // Trim leading whitespace
    while(isspace((unsigned char)*str)) {
        str++;
    }
    // All spaces?
    if(0 == *str) {
        return str;
    }
    // Trim trailing spaces
    end = str + strlen(str) - 1;
    while(end > str && isspace((unsigned char)*end)) {
        end--;
    }
    // Write a new null terminator character
    end[1] = '\0';
    return str;
}

#endif // DRG_H_TOOLBOX
