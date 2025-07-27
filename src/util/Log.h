/*****************************************************************
* Dargon Programming Language
* (C) Kyle Morris 2025 - See LICENSE.txt for license information.
*
* @file Log.h
* @author Kyle Morris
* @since v0.1
*
*****************************************************************/

#ifndef DRG_H_LOG
#define DRG_H_LOG

#include <stdarg.h>

/// @brief Standard logging function, includes newline character. Prints "time: INFO : msg\n" to stdout.
/// @param msgFmt Formatted string.
void D_Log(const char* msgFmt, ...);

/// @brief Logging function for warnings, includes newline character. Prints "time: WARN : msg\n" to stdout.
/// @param msgFmt Formatted string.
void D_LogWarning(const char* msgFmt, ...);

/// @brief Logging function for errors, includes newline character. Prints "time: ERROR: msg\n" to stdout.
/// @param msgFmt Formatted string.
void D_LogError(const char* msgFmt, ...);

#endif // DRG_H_LOG
