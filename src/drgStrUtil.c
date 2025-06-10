/*****************************************************************
* Dargon Programming Language
* (C) Kyle Morris 2025 - See LICENSE.txt for license information.
*
* @file drgStrUtil.c
* @author Kyle Morris
* @since v0.1
* @section Description
* Various string utility functions.
*
*****************************************************************/

#include <ctype.h>
#include <string.h>

#include "drgStrUtil.h"

char* drgTrimSpaces(char* str) {
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
