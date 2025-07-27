/*****************************************************************
* Dargon Programming Language
* (C) Kyle Morris 2025 - See LICENSE.txt for license information.
*
* @file drgValue.h
* @author Kyle Morris
* @since v0.1
* @section Description
* The virtual machine representation for values.
*
*****************************************************************/

#ifndef DRG_H_VALUE
#define DRG_H_VALUE

/* #include <stddef.h>

#include <drgMemUtil.h>

/// @brief A value within Dargon's virtual machine
typedef double drgVal;

/// @brief Dynamic array of Dargon values.
typedef struct {
    int capacity;
    int count;
    drgVal* values;
} drgValArray;

/// @brief Initializes a value array.
/// @param arr 
void drgValArrayInit(drgValArray* arr);

/// @brief Adds a new value to a value array.
/// @param arr 
/// @param val 
void drgValArrayAdd(drgValArray* arr, drgVal val);

/// @brief Frees the dynamic memory of a value array.
/// @param arr 
void drgValArrayFree(drgValArray* arr);

/// @brief Prints a value to stdout.
/// @param val 
void drgPrintVal(drgVal val); */

#endif // DRG_H_VALUE
