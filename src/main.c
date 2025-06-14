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

#include <drgLog.h>
#include <drgStrUtil.h>
#include <drgMemUtil.h>

void drgUsage(void) {
    printf("Usage: dargon <command> <input>\n\n");
    printf("Commands:\n");
    printf("* (no arguments):Runs an interactive interpreter.\n");
    printf("* init:          Initializes a Dargon project in this directory.\n");
    printf("* run:           Runs a Dargon file or project.\n");
    printf("* export:        Exports a Dargon project to a module.\n");
    printf("* help:          Prints this dialogue.\n");
}

// Read-Eval-Print-Loop
int drgRepl(void) {
    char* buf = NULL;
    size_t bufLen = 0;
    for(;;) {
        printf("@ ");
        // Read user input
        bufLen = getline(&buf, &bufLen, stdin);
        if(-1 == bufLen) {
            perror("getline() returned an error!");
            DRG_MEM_FREE(buf);
            return EXIT_FAILURE;
        }
        if(0 == strcmp(buf, "quit\n")) {
            break;
        }
        // Trim + print it out
        char* substr = drgStrTrimSpaces(buf);
        drgLog("Got: %s", substr);
        printf("\n");
    }
    DRG_MEM_FREE(buf);
    return EXIT_SUCCESS;
}

int main(int argc, const char* argv[]) {
    // Print version info
    printf("%s\n", drgVersion);

    // No args = interpreter
    if(argc == 1) {
        return drgRepl();
    }

    // Parse args
    // Syntax: dargon <command> <input>
    // First one must be a command
    const char* commandIn = argv[1];
    if(0 == strcmp(commandIn, "init")) {
        drgLog("init is not implemented.");
    }
    else if(0 == strcmp(commandIn, "run")) {
        // Get the next input
        if(argc < 3) {
            drgLogWarning("No input given to 'run' command! Running interpreter.");
            return drgRepl();
        }
        const char* runInput = argv[2];
        drgLog("File: %s", runInput);
    }
    else if(0 == strcmp(commandIn, "export")) {
        drgLog("export is not implemented.");
    }
    else if(0 == strcmp(commandIn, "help")) {
        drgUsage();
    }
    else {
        drgLogError("Unknown command: %s\n", commandIn);
        drgUsage();
    }
    
    return EXIT_SUCCESS;
}