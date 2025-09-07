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

void D_Repl(void);
void D_ReplHelp(void);
void D_Help(void);
char* D_ReadFile(const char* path);

int main(int argc, const char* argv[]) {
    // Initialize the virtual machine
    D_InitVirtualMachine();

    // Print version info
    D_ClearConsole();
    printf("%s\n", D_SoftwareVersion);

    // No args -> interpreter
    if(argc == 1) { 
        D_Repl();
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
                D_Repl();
            }
            else {
                const char* runInput = argv[2];
                char* source = D_ReadFile(runInput);
                if(NULL != source) {
                    D_Result result = D_Interpret(source);
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
    
    D_FreeVirtualMachine();
    return EXIT_SUCCESS;
}

/*****************************************************************
* REPL State Machine
*****************************************************************/

typedef enum {
    D_ReplState_READLINE, // Waiting for input
    D_ReplState_CHECK,    // Check for special keywords
    D_ReplState_INTERP,   // Interpret
    D_ReplState_STOP      // Stop
} D_ReplState;

// Read-Eval-Print-Loop
void D_Repl(void) {
    D_ReplState state = D_ReplState_READLINE;
    char buf[1024];
    printf("*** Type 'help for help.\n");
    while(state != D_ReplState_STOP) {
        switch(state) {
            case D_ReplState_READLINE: {
                printf("@: ");
                // Read user input
                if(!fgets(buf, sizeof(buf), stdin)) {
                    D_LogError("Well, that's an unexpected error from reading your input!");
                    state = D_ReplState_STOP;
                    break;
                }
                // If there's no newline character, only a partial line was read.
                if(!strchr(buf, '\n')) {
                    D_LogError("Lines longer than 1024 characters just aren't my thing...");
                    state = D_ReplState_STOP;
                    break;
                }
                state = D_ReplState_CHECK;
                break;
            }
            case D_ReplState_CHECK: {
                if(0 == strcmp(buf, "help\n")) {
                    D_ReplHelp();
                    state = D_ReplState_READLINE;
                }
                else if(0 == strcmp(buf, "exit\n")) {
                    state = D_ReplState_STOP;
                }
                else if(0 == strcmp(buf, "clear\n")) {
                    D_ClearConsole();
                    state = D_ReplState_READLINE;
                }
                else {
                    // TODO: Line continuation!
                    state = D_ReplState_INTERP;
                }
                break;
            }
            case D_ReplState_INTERP: {
                // Trim and run it
                char* source = D_TrimString(buf);
                D_Result result = D_Interpret(source);
                // TODO: Do something with result
                state = D_ReplState_READLINE;
                break;
            }
            default:
                state = D_ReplState_STOP;
                break;
        }
    }
}

void D_ReplHelp(void) {
    printf("*** Type 'clear' to clear the console.\n");
    printf("*** Type 'exit' to exit this session.\n");
}

/*****************************************************************
* Util Functions
*****************************************************************/

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

/// @brief Reads a file at the location 'path' and returns its
/// including null-termination. This should be free'd after use.
/// @param path  
/// @return Malloc'd contents, NULL on error.
char* D_ReadFile(const char* path) {
    // Try to open file
    FILE* file = fopen(path, "rb");
    if(NULL == file) {
        D_LogError("Could not open file \"%s\".\n", path);
        return NULL;
    }
    
    // Get size of file
    fseek(file, 0L, SEEK_END);
    size_t fileSize = ftell(file);
    rewind(file);

    // Allocate buffer (null-terminate it)
    char* fileOut = (char*)malloc(fileSize+1);
    if(!fileOut) {
        D_LogError("D_ReadFile: malloc() failed!");
        exit(EXIT_FAILURE); // nothing we can do
    }
    size_t bytesRead = fread(fileOut, sizeof(char), fileSize, file);
    fileOut[bytesRead] = '\0';

    fclose(file);
    return fileOut;
}