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

#include "Bytecode.h"

void D_NewChunk(D_Chunk* chunk) {
	chunk->count = 0;
	chunk->capacity = 0;
	chunk->code = NULL;
	// init val array
}

void D_FreeChunk(D_Chunk* chunk) {
	// free val array
}