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

#include <stdio.h>

#include "VM.h"

void D_InitVirtualMachine(D_VM* const vm) {
    
}

D_Result D_Interpret(D_VM* const vm, const char* const source) {
    // -- Initialize scanner
    vm->scanner.start = source;
    vm->scanner.current = source;
    vm->scanner.line = 1;
    vm->scanner.column = 1;

    // -- Temporary code to drive a "compiler"
    int line = -1;
    for(;;) {
        D_Token token = D_GetNextToken(&vm->scanner);
        if(token.line != line) {
            printf("%4d ", token.line);
            line = token.line;
        }
        else {
            printf("   | ");
        }
        // For now just print the token
        printf("%2d '%.*s'\n", token.type, token.length, token.start);
        if(token.type == D_TokenType_EOF) {
            break;
        }
    }
}

void D_FreeVirtualMachine(D_VM* const vm) {

}







// TODO: Dynamically modify stack
#define DRG_STACK_MAX 256

/// @brief The Dargon Virtual Machine (VM)
typedef struct {
    drgNugget* nugget; // The nugget being interpreted
    drgByte* ip; // Instruction Pointer to the instr ABOUT to be executed
    drgVal stack[DRG_STACK_MAX];
    drgVal* stackTop;
} drgVM;

static drgVM vm; // The single VM instance.

// -----------------------

static int drgSimpleInst(const char* name, drgByte inst, int offset) {
    printf("%-16s (0x%02X)\n", name, inst);
    return offset + 1;
}

static int drgLitInst(const char* name, drgByte inst, drgNugget* nug, int offset) {
    drgByte lit = nug->bytecode[offset + 1];
    printf("%-16s (0x%02X) %2d' ", name, inst, lit);
    drgPrintVal(nug->constantPool.values[lit]);
    printf("'\n");
    return offset + 2; // Consumes 2 spaces
}

static void drgResetStack(void) {
    vm.stackTop = vm.stack;
}

static void drgPushStack(drgVal val) {
    // TODO: Make sure pushing would not
    // go over the max!
    *vm.stackTop = val;
    vm.stackTop++;
}

static drgVal drgPopStack(void) {
    vm.stackTop--;
    return *vm.stackTop;
}

static char* drgReadFile(const char* path) {
    FILE* file = fopen(path, "rb");
    if(NULL == file) {
        perror("Could not open file!");
        exit(EXIT_FAILURE); // nothing more we can do
    }

    fseek(file, 0L, SEEK_END);
    size_t fileSize = ftell(file);
    rewind(file);

    char* buffer = malloc(fileSize + 1); // remember null terminator
    if(NULL == buffer) {
        perror("Could not allocate enough memory to read file!");
        exit(EXIT_FAILURE);
    }

    size_t bytesRead = fread(buffer, sizeof(char), fileSize, file);
    if(bytesRead < fileSize) {
        perror("Could not read the entire file!");
        exit(EXIT_FAILURE);
    }

    buffer[bytesRead] = '\0';
    
    fclose(file);
    return buffer;
}

static drgVMResult drgInterpret(const char* source) {

}

// -----------------------

void drgInitVM(void) {
    vm.nugget = NULL;
    vm.ip = NULL;
    drgResetStack();
}

void drgFreeVM(void) {
    drgNuggetFree(vm.nugget);
    drgInitVM();
}

void drgVMRunFile(const char* path) {
    char* source = drgReadFile(path);
    drgVMResult result = drgInterpret(source);
    DRG_MEM_FREE(source);
    
    switch(result) {
        case DRG_VMRES_COMPILE_ERROR: exit(DRG_VMRES_COMPILE_ERROR); break;
        case DRG_VMRES_RUNTIME_ERROR: exit(DRG_VMRES_RUNTIME_ERROR); break;
        default: break;
    }
}

void drgVMRunLine(const char* line) {
    drgVMResult result = drgInterpret(line);
    
    switch(result) {
        case DRG_VMRES_COMPILE_ERROR: exit(DRG_VMRES_COMPILE_ERROR); break;
        case DRG_VMRES_RUNTIME_ERROR: exit(DRG_VMRES_RUNTIME_ERROR); break;
        default: break;
    }
}

drgVMResult drgVMRun(drgNugget* nugget) {
    #define DRG_READ_BYTE() (*vm.ip++)
    #define DRG_READ_LIT() (vm.nugget->constantPool.values[DRG_READ_BYTE()])
    #define DRG_BINARY_OP(op) \
        do {\
            double b = drgPopStack();\
            double a = drgPopStack();\
            drgPushStack(a op b);\
        } while(0)

    vm.nugget = nugget;
    vm.ip = vm.nugget->bytecode;
    drgByte instruction;

    for(;;) {
        // If we are in debug mode, print the stack
        // as well as the chunk being interpreted.
        #ifdef DRG_DEBUG
        drgPrintStack();
        drgDisassembleInstruction(vm.nugget,
            (int)(vm.ip - vm.nugget->bytecode));
        #endif

        // Read an instruction (byte) and
        // do something depending on what it is
        switch(instruction = DRG_READ_BYTE()) {
            case DRG_OC_NUM_LIT:
                drgVal lit = DRG_READ_LIT();
                drgPushStack(lit);
                break;
            case DRG_OC_NEGATE: drgPushStack(-drgPopStack()); break;
            case DRG_OC_ADD:  DRG_BINARY_OP(+); break;
            case DRG_OC_SUB:  DRG_BINARY_OP(-); break;
            case DRG_OC_MULT: DRG_BINARY_OP(*); break;
            case DRG_OC_DIV:  DRG_BINARY_OP(/); break;
            case DRG_OC_RETURN:
                drgPrintVal(drgPopStack());
                printf("\n");
                return DRG_VMRES_OK;
        }
    }

    #undef DRG_READ_BYTE
    #undef DRG_READ_LIT
    #undef DRG_BINARY_OP
}

void drgDisassembleNugget(drgNugget* nugget, const char* name) {
    printf("[%s]\n", name);
    for(int offset = 0; offset < nugget->count;) {
        offset = drgDisassembleInstruction(nugget, offset);
    }
}

int drgDisassembleInstruction(drgNugget* nugget, int offset) {
    drgByte inst = nugget->bytecode[offset];
    printf("%04d: ", offset);
    switch(inst) {
        case DRG_OC_RETURN: return drgSimpleInst("DRG_OC_RETURN", inst, offset);
        case DRG_OC_NEGATE: return drgSimpleInst("DRG_OC_NEGATE", inst, offset);
        case DRG_OC_ADD: return drgSimpleInst("DRG_OC_ADD", inst, offset);
        case DRG_OC_SUB: return drgSimpleInst("DRG_OC_SUB", inst, offset);
        case DRG_OC_MULT: return drgSimpleInst("DRG_OC_MULT", inst, offset);
        case DRG_OC_DIV: return drgSimpleInst("DRG_OC_DIV", inst, offset);
        case DRG_OC_NUM_LIT: return drgLitInst("DRG_OC_LIT_NUM", inst, nugget, offset);
        default:
            printf("!! Unknown opcode %d\n", inst);
            return offset + 1;
    }
    return offset + 1; // shouldn't get hit but put it here anyway
}

void drgPrintStack(void) {
    printf("          ");
    // Iterate through the stack
    for(drgVal* s = vm.stack; s < vm.stackTop; s++) {
        printf("[ ");
        drgPrintVal(*s);
        printf(" ]");
    }
    printf("\n");
}