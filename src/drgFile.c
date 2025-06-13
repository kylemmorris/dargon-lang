/*****************************************************************
* Dargon Programming Language
* (C) Kyle Morris 2025 - See LICENSE.txt for license information.
*
* @file drgFile.c
* @author Kyle Morris
* @since v0.1
* @section Description
* Module for file operations.
*
*****************************************************************/

#include <sys/stat.h>

#include "drgFile.h"

int drgFileExists(const char* filePath) {
    // Check file status
    struct stat status = { 0 };
    return stat(filePath, &status) > 0;
}