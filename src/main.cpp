/**
 * Dargon Programming Language
 * (C) Kyle Morris 2023 - See LICENSE.txt for license information.
 *
 * @file main.cpp
 * @author Kyle Morris
 * @since v0.1
 * @section Description
 * The main file. Parses the command-line arguments and dispatches.
 *
 */

#include <vector>
#include "core/Output.h"
#include "core/Log.h"

/// @brief Displays the help dialogue.
void help() {
    out("   Usage:");
    out("       dargon help             - Displays this dialogue.");
    out("       dargon go               - Begins the Dargon interactive interpreter.");
    out("       dargon test             - Runs Dargon unit tests.");
    out("       dargon <path>           - Runs a Dargon file (*.dargon or *.dargconf) at the path provided.");
    out("");
}

/// @brief A basic REPL implementation.
void runBasicREPL() {
    out("Welcome! For help, type 'help'");
    std::string line = "";
    while(true) {
        std::cout << "DIR> ";
        // Read line
        getline(std::cin, line);
        if(line == "quit") { break; }
        if(line == "commands") {
            out("**********");
            out("help          - Displays the help dialogue.");
            out("commands      - Displays this dialogue.");
            out("memory        - Displays the items currently in memory.");
            out("**********");
            continue;
        }
        if(line == "help") {
            out("**********");
            out("This is the Dargon Interpreter (DIR).");
            out("Type any Dargon code to have it interpreted for you.");
            out("");
            out("To view a list of DIR commands, type \'commands\'");
            out("**********");
            continue;
        }
        // TODO
    }
}

/// @brief Entry point.
int main(int argc, char* argv[]) {
    using namespace dargon;

    // Starting up
    out(VersionString());
    out("(C) Kyle Morris 2023 - See LICENSE.txt for license information.\n");
    DARGON_LOG_INFO(VersionString() + " starting.");

    // If no inputs were provided, display help
    if(argc == 1) {
        help();
        return 0;
    }

    // Collect inputs
    std::vector<std::string> inputs;
    for(int i = 1; i < argc; i++) {
        inputs.push_back(std::string(argv[i]));
    }

    if(inputs[0] == "help") {
        help();
    }
    else if(inputs[0] == "go") {
        runBasicREPL();
    }
    else if(inputs[0] == "test") {
        out("Not implemented yet...");
    }
    else {
        // It's a file path... TODO
        out("Not implemented yet...");
    }

    return 0;
}
