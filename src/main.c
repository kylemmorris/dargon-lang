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
#include <stdlib.h>
#include <string.h>

#include <drgLog.h>
#include <drgStrUtil.h>

// Read-Eval-Print-Loop
int drgRepl(void) {
    char* buf = NULL;
    size_t bufLen = 0;
    for(;;) {
        printf("$ ");
        // Read user input
        bufLen = getline(&buf, &bufLen, stdin);
        if(-1 == bufLen) {
            return EXIT_FAILURE;
        }
        if(0 == strcmp(buf, "quit\n")) {
            break;
        }
        // Trim + print it out
        char* substr = drgTrimSpaces(buf);
        drgLog("Got: %s", substr);
    }
    free(buf);
    return EXIT_SUCCESS;
}

int main(int argc, const char* argv[]) {
    // Print version info
    fprintf(stdout, "%s\n", drgVersion);

    // No args = interpreter
    if(argc == 1) {
        return drgRepl();
    }

    // Parse args
    for(int i = 1; i < argc; i++) {
        // ....   
    }
    
    return EXIT_SUCCESS;
}