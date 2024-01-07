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
#include <sstream>
#include "core/Log.h"
#include "core/ast/ASTPrinter.h"
#include "core/DIR.h"

/// @brief Displays version information (and logs).
void dispVer() {
    using namespace dargon;
    DARGON_LOG_INFO(VersionString());
    DARGON_LOG_INFO(Copyright);
    out("");
}

/// @brief Displays the help dialogue.
void help() {
    using namespace dargon;
    // Starting up
    dispVer();
    out("Usage:");
    out("    dargon help             - Displays this dialogue.");
    out("    dargon version          - Version information.");
    out("    dargon gui              - Opens the Dargon GUI.");
    out("    dargon test             - Runs Dargon unit tests.");
    out("    dargon <path>           - Runs a Dargon file (*.dargon or *.snoot) at the path provided.");
    out("");
    out("Running dargon without any arguments will begin the interpreter (DIR).");
    out("");
}

/// @brief A basic REPL implementation.
void runBasicREPL(dargon::DIR& dir) {
    using namespace dargon;

    // Starting up
    dispVer();
    out("Welcome to the Dargon Interpreter (DIR)! For help, type 'help', to exit type 'quit'.");
    out("");
    std::string line = "";
    std::ostringstream os;
    while(true) {
        in(line);
        if(line == "quit") { break; }
        if(line == "memory") { continue; }
        if(line == "help") {
            out("");
            out("**********");
            out("This is the Dargon Interpreter (DIR).");
            out("Type any Dargon code to have it be interpreted.");
            out("");
            out("The following is a list of commands:");
            out("quit          - Exits the interpreter.");
            out("help          - Displays this dialogue.");
            out("memory        - Displays the items currently in memory.");
            out("**********");
            out("");
            continue;
        }
        // Edge-case: If the user only inputted whitespace and newline, don't continue
        std::string test = line;
        RemoveFromString(test, ' ');
        RemoveFromString(test, '\t');
        RemoveFromString(test, '\n');
        if(test.empty()) { continue; }

        // Begin interpreter
        line = line + "\n"; // Newline added here
        dir.Run(line);
    }
}

/// @brief Entry point.
int main(int argc, char* argv[]) {
    using namespace dargon;

    // This is the Dargon Interpreter (DIR)
    DIR dir;

    // If no inputs were provided, begin REPL
    if(argc == 1) {
        runBasicREPL(dir);
        return 0;
    }
    // Otherwise, collect inputs
    std::vector<std::string> inputs;
    for(int i = 1; i < argc; i++) {
        inputs.push_back(std::string(argv[i]));
    }

    if(inputs[0] == "help") {
        help();
    }
    else if(inputs[0] == "version") {
        out(VersionString());
        //out(Copyright);
    }
    else if(inputs[0] == "gui") {
        //out("Not implemented yet...");
    }
    else if(inputs[0] == "test") {
        //out("Not implemented yet...");
    }
    else {
        // It's a file path
        Path p = Path(inputs[0]);
        dispVer();
        dir.Run(p);
    }
    return 0;
}
