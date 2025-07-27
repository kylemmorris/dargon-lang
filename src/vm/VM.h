/*****************************************************************
* Dargon Programming Language
* (C) Kyle Morris 2025 - See LICENSE.txt for license information.
*
* @file VM.h
* @author Kyle Morris
* @since v0.1
* @section Description
* The implementation of the stack-based virtual machine (VM).
*
*****************************************************************/

#ifndef DRG_H_VM
#define DRG_H_VM

#include "../scanner/Scanner.h"

typedef enum {
    D_Result_OK,
    D_Result_COMPILER_ERROR,
    D_Result_RUNTIME_ERROR
} D_Result;

typedef struct {
    D_Scanner scanner;
} D_VM;

void D_InitVirtualMachine(D_VM* const vm);
D_Result D_Interpret(D_VM* const vm, const char* const source);
void D_FreeVirtualMachine(D_VM* const vm);

#endif // DRG_H_VM
