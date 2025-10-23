/*****************************************************************
* Dargon Programming Language
* (C) Kyle Morris 2025 - See LICENSE.txt for license information.
*
* @file Bytecode.h
* @author Kyle Morris
* @since v0.1
* @section Description
* Bytecode is what the Dargon Virtual Machine (VM) runs.
*
*****************************************************************/

#ifndef DRG_H_BYTECODE
#define DRG_H_BYTECODE

#include <stdint.h>

typedef uint8_t D_Byte;

typedef enum {
	D_Opcode_RETURN,
	// -- Literals
	D_Opcode_LIT_NUM,
	// -- Unary operators
	D_Opcode_UO_NEGATE,
	// -- Binary operators
	D_Opcode_BO_ADD,
	D_Opcode_BO_SUB,
	D_Opcode_BO_MULT,
	D_Opcode_BO_DIV
} D_Opcode;

typedef struct {
	int count;
	int capacity;
	D_Byte* code;
	//D_ValueList constPool;
} D_Chunk;

void D_NewChunk(D_Chunk* chunk);
void D_FreeChunk(D_Chunk* chunk);

#endif // DRG_H_BYTECODE
