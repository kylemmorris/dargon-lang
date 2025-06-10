/*****************************************************************
* Dargon Programming Language
* (C) Kyle Morris 2025 - See LICENSE.txt for license information.
*
* @file drgLog.h
* @author Kyle Morris
* @since v0.1
* @section Description
* Logging utility.
*
*****************************************************************/

#ifndef DRG_H_LOG
#define DRG_H_LOG

#include <stdarg.h>

#include <drgVersion.h>

#ifdef DRG_DEBUG
void _drgLog(
    int lineNum,
    const char* fileName,
    const char* msgFmt, ...);
void _drgLogWarning(
    int lineNum,
    const char* fileName,
    const char* msgFmt, ...);
void _drgLogError(
    int lineNum,
    const char* fileName,
    const char* msgFmt, ...);

    /// @brief Standard logging function. Prints "time: INFO : msg\n" to stdout.
    /// Includes location + file (DEBUG).
    /// @param msgFmt Formatted string.
    #define drgLog(...) _drgLog(__LINE__, __FILE__, __VA_ARGS__)
    /// @brief Logging function for warnings. Prints "time: WARN : msg\n" to stdout.
    /// Includes location + file (DEBUG).
    /// @param msgFmt Formatted string.
    #define drgLogWarning(...) _drgLogWarning(__LINE__, __FILE__, __VA_ARGS__)
    /// @brief Logging function for errors. Prints "time: ERROR: msg\n" to stdout.
    /// Includes location + file (DEBUG).
    /// @param msgFmt Formatted string.
    #define drgLogError(...) _drgLogError(__LINE__, __FILE__, __VA_ARGS__)
#else
/// @brief Standard logging function. Prints "time: INFO : msg\n" to stdout.
/// @param msgFmt Formatted string.
void drgLog(const char* msgFmt, ...);
/// @brief Logging function for warnings. Prints "time: WARN : msg\n" to stdout.
/// @param msgFmt Formatted string.
void drgLogWarning(const char* msgFmt, ...);
/// @brief Logging function for errors. Prints "time: ERROR: msg\n" to stdout.
/// @param msgFmt Formatted string.
void drgLogError(const char* msgFmt, ...);
#endif

#endif // DRG_H_LOG
