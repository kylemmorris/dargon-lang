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

typedef enum {
    D_Result_OK,
    D_Result_COMPILER_ERROR,
    D_Result_RUNTIME_ERROR
} D_Result;

void D_InitVirtualMachine(void);
D_Result D_Interpret(const char* const source);
void D_FreeVirtualMachine(void);

#endif // DRG_H_VM
