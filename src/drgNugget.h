/*****************************************************************
* Dargon Programming Language
* (C) Kyle Morris 2025 - See LICENSE.txt for license information.
*
* @file drgNugget.h
* @author Kyle Morris
* @since v0.1
* @section Description
* In Dargon terminology, a Nugget is a group of bytecode.
*
*****************************************************************/

#ifndef DRG_H_NUGGET
#define DRG_H_NUGGET

#include <stdint.h>

#include <drgValue.h>

/// @brief Operational code (Opcode)
/// definitions for the Dargon virtual machine.
typedef enum {
    DRG_OC_RETURN = 0
} drgOpcode;

/// @brief A "Nugget" is a dynamic array of
/// bytecode.
typedef struct {
    int count;
    int capacity;
    uint8_t* bytecode;
    drgValArray constants;
} drgNugget;

// Initializes a nugget (bytecode chunk).
void drgNuggetInit(drgNugget* nugget);
// Adds a new byte to a nugget.
void drgNuggetAdd(drgNugget* nugget, uint8_t byte);
/// @brief Adds a new constant to a nugget.
/// @return The index where the constant was appended to.
int drgNuggetAddConstant(drgNugget* nugget, drgVal constant);
// Frees a nugget's dynamic memory.
void drgNuggetFree(drgNugget* nugget);

#endif // DRG_H_NUGGET
