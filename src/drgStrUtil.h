/*****************************************************************
* Dargon Programming Language
* (C) Kyle Morris 2025 - See LICENSE.txt for license information.
*
* @file drgStrUtil.h
* @author Kyle Morris
* @since v0.1
* @section Description
* Various string utility functions.
*
*****************************************************************/

#ifndef DRG_H_STR_UTIL
#define DRG_H_STR_UTIL

/// @brief Trims leading + trailing spaces from the string.
/// @param str The input string.
/// @return Pointer to a substring of the input, including
/// an additional null character. 
/// NOTE:
/// If the given string was malloc'd, you MUST NOT
/// overwrite the original ptr with this return value.
/// NOTE: 
/// The return value must NOT be free'd.
char* drgStrTrimSpaces(char* str);

#endif // DRG_H_STR_UTIL
