/*****************************************************************
* Dargon Programming Language
* (C) Kyle Morris 2025 - See LICENSE.txt for license information.
*
* @file main.c
* @author Kyle Morris
* @since v0.1
* @section Description
* The main file. Parses the command-line arguments and dispatches.
*
*****************************************************************/

#include <stdio.h>
#include <string.h>

#include "util/Log.h"
#include "util/Toolbox.h"
#include "util/Version.h"
#include "vm/VM.h"

void D_Help(void);
void D_REPL(D_VM* const vm);
bool D_ReadFile(const char* path, char* fileOut);

int main(int argc, const char* argv[]) {
    // Initialize the virtual machine
    D_VM vm;
    D_InitVirtualMachine(&vm);

    // Print version info
    printf("%s\n", D_SoftwareVersion);

    // No args -> interpreter
    if(argc == 1) { 
        D_REPL(&vm);
    }
    else {
        // Parse args
        // Syntax: dargon <command> <input>
        // First one must be a command
        const char* commandIn = argv[1];
        if(0 == strcmp(commandIn, "init")) {
            D_Log("init is not implemented.");
        }
        else if(0 == strcmp(commandIn, "run")) {
            // Get the next input
            if(argc < 3) {
                D_LogWarning("No input given to 'run' command! Running interpreter.");
                D_REPL(&vm);
            }
            else {
                const char* runInput = argv[2];
                char* source;
                if(D_ReadFile(runInput, source)) {
                    D_Result result = D_Interpret(&vm, source);
                    // TODO: Do something with result
                    D_Free(source);
                }
                else {
                    // TODO: Handle
                }
            }
        }
        else if(0 == strcmp(commandIn, "export")) {
            D_Log("export is not implemented.");
        }
        else if(0 == strcmp(commandIn, "help")) {
            D_Help();
        }
        else {
            D_LogError("Unknown command: %s", commandIn);
            D_Help();
        }
    }
    
    D_FreeVirtualMachine(&vm);
    return EXIT_SUCCESS;
}

// Print help info to console
void D_Help(void) {
    printf("Usage: dargon <command> <input>\n\n");
    printf("Commands:\n");
    printf("* (no arguments): Runs an interactive interpreter.\n");
    printf("*           init: Initializes a Dargon project in this directory.\n");
    printf("*            run: Runs a Dargon file or project.\n");
    printf("*         export: Exports a Dargon project to a module.\n");
    printf("*           help: Prints this dialogue.\n");
}

// Read-Eval-Print-Loop
void D_REPL(D_VM* const vm) {
    char buf[1024];
    for(;;) {
        printf("@: ");
        // Read user input
        if(!fgets(buf, sizeof(buf), stdin)) {
            D_LogError("drgrepl: fgets() failed!");
            exit(EXIT_FAILURE);
        }

        // If there's no newline character, it only a partial
        // line was read.
        if(!strchr(buf, '\n')) {
            D_LogError("Cannot handle multiple lines just yet!");
            return;
        }

        // If they typed 'quit', quit REPL.
        if(0 == strcmp(buf, "quit\n")) {
            break;
        }
        // TODO: Line continuation!

        // Trim and run it
        char* source = D_TrimString(buf);
        D_Result result = D_Interpret(vm, source);
        // TODO: Do something with result
    }
}

/// @brief Reads a file at the location 'path' and outputs it
/// to the contents of 'fileOut', including null-termination. 
/// This should be free'd after use.
/// @param path 
/// @param fileOut 
/// @return True on success, false on error.
bool D_ReadFile(const char* path, char* fileOut) {
    // Try to open file
    FILE* file = fopen(path, "rb");
    if(NULL == file) {
        D_LogError("Could not open file \"%s\".\n", path);
        return false;
    }

    // Get size of file
    fseek(file, 0L, SEEK_END);
    size_t fileSize = ftell(file);
    rewind(file);

    // Allocate buffer (null-terminate it)
    fileOut = (char*)malloc(fileSize+1);
    if(!fileOut) {
        D_LogError("D_ReadFile: malloc() failed!");
        exit(EXIT_FAILURE); // nothing we can do
    }
    size_t bytesRead = fread(fileOut, sizeof(char), fileSize, file);
    fileOut[bytesRead] = '\0';

    fclose(file);
    return true;
}