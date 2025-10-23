/*****************************************************************
* Dargon Programming Language
* (C) Kyle Morris 2025 - See LICENSE.txt for license information.
*
* @file Compiler.h
* @author Kyle Morris
* @since v0.1
* @section Description
* The compiler converts source code into bytecode for the VM.
*
*****************************************************************/

#ifndef DRG_H_COMPILER
#define DRG_H_COMPILER

#include <stdbool.h>

#include "../vm/Bytecode.h"

bool D_Compile(const char* source, D_Chunk* chunk);

#endif // DRG_H_COMPILER
