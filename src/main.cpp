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
#include "core/io/Log.h"
#include "core/ast/ASTPrinter.h"
#include "core/DIR.h"
#include "vm/Nugget.h"
#include "vm/VirtualMachine.h"

/// @brief Displays version information (and logs).
void dispVer() {
    using namespace dargon;
    out(VersionString());
    out(Copyright);
    out("");
}

/// @brief Displays the help dialogue.
void help() {
    using namespace dargon;
    // Starting up
    dispVer();
    out("Usage:");
    out("    dargon help    (-h)   - Displays this dialogue.");
    out("    dargon version (-v)   - Version information.");
    out("    dargon gui     (-g)   - Opens the Dargon GUI.");
    out("    dargon test    (-t)   - Runs Dargon unit tests.");
    out("    dargon <path>         - Runs a Dargon file (*.dargon or *.snoot) at the path provided.");
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

    vm::Nugget chunk = vm::Nugget("TEST OF {-((1.2 + 3.4) /  5.6)}");
    vm::value val_a = 1.2;
    vm::value val_b = 3.4;
    vm::value val_c = 5.6;

    chunk.Write((vm::byte)vm::OPCODE::CONSTANT);
    chunk.Write(chunk.AddConst(val_a));
    chunk.Write((vm::byte)vm::OPCODE::CONSTANT);
    chunk.Write(chunk.AddConst(val_b));

    chunk.Write((vm::byte)vm::OPCODE::ADD);

    chunk.Write((vm::byte)vm::OPCODE::CONSTANT);
    chunk.Write(chunk.AddConst(val_c));

    chunk.Write((vm::byte)vm::OPCODE::DIVIDE);

    chunk.Write((vm::byte)vm::OPCODE::NEGATE);
    chunk.Write((vm::byte)vm::OPCODE::RETURN);

    vm::VirtualMachine vm;
    vm.Interpret(&chunk);

    return 0;

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

    if(inputs[0] == "help" || inputs[0] == "-h") {
        help();
    }
    else if(inputs[0] == "version" || inputs[0] == "-v") {
        out(VersionString());
        out(Copyright);
    }
    else if(inputs[0] == "gui" || inputs[0] == "-g") {
        out("Not implemented yet...");
    }
    else if(inputs[0] == "test" || inputs[0] == "-t") {
        out("Not implemented yet...");
    }
    else {
        // It's a file path
        Path p = Path(inputs[0]);
        dispVer();
        dir.Run(p);
    }
    return 0;
}
