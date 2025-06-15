/*****************************************************************
* Dargon Programming Language
* (C) Kyle Morris 2025 - See LICENSE.txt for license information.
*
* @file drgVM.h
* @author Kyle Morris
* @since v0.1
* @section Description
* The implementation of the stack-based virtual machine (VM).
*
*****************************************************************/

#ifndef DRG_H_VM
#define DRG_H_VM

#include "drgNugget.h"

/// @brief Result of the VM running
typedef enum {
    DRG_VMRES_OK = 0x00,
    DRG_VMRES_COMPILE_ERROR = 0x10,
    DRG_VMRES_RUNTIME_ERROR = 0x20
} drgVMResult;

void drgInitVM(void);
void drgFreeVM(void);
drgVMResult drgVMRun(drgNugget* nugget);


/// @brief Disassembles each instruction within the nugget, printing its contents to stdout.
/// @param nugget 
/// @param name 
void drgDisassembleNugget(drgNugget* nugget, const char* name);

/// @brief Disassembles a single instruction.
/// @param nugget 
/// @param offset 
/// @return 
int drgDisassembleInstruction(drgNugget* nugget, int offset);

/// @brief Prints the current status of the stack.
/// @param  
void drgPrintStack(void);

#endif // DRG_H_VM
