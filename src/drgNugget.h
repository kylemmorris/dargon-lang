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

/// @brief Byte typedef.
typedef uint8_t drgByte;

/// @brief Operational code (Opcode)
/// definitions for the Dargon virtual machine.
typedef enum {
    DRG_OC_RETURN,
    // Literals
    DRG_OC_NUM_LIT,
    // Unary operators
    DRG_OC_NEGATE,
    // Binary operators
    DRG_OC_ADD,
    DRG_OC_SUB,
    DRG_OC_MULT,
    DRG_OC_DIV
} drgOpcode;

/// @brief A "Nugget" is a dynamic array of
/// bytecode.
typedef struct {
    int count;
    int capacity;
    drgByte* bytecode;
    drgValArray constantPool;
} drgNugget;

// Initializes a nugget (bytecode chunk).
void drgNuggetInit(drgNugget* nugget);

// Adds a new byte to a nugget.
void drgNuggetAdd(drgNugget* nugget, drgByte byte);

/// @brief Adds a new constant to a nugget.
/// @return The index where the constant was appended to.
int drgNuggetAddLiteral(drgNugget* nugget, drgVal constant);

// Frees a nugget's dynamic memory.
void drgNuggetFree(drgNugget* nugget);

#endif // DRG_H_NUGGET
