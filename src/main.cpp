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
#include <set>
#include <unistd.h>
#include <sstream>
#include <cstring>
#include <chrono>

#include "core/io/Log.h"
#include "core/ast/ASTPrinter.h"
#include "core/DIR.h"
#include "vm/Nugget.h"
#include "vm/VirtualMachine.h"
#include "../lib/CLI11/CLI11.hpp"

/// @brief Displays version information (and logs).
void dispVer(int i=0) {
    using namespace dargon;
    std::string v = VersionString();
    out(true, v.c_str());
    out(true, Copyright);
    out(true, "");
}

/// @brief A basic REPL implementation.
void runBasicREPL(dargon::DIR& dir) {
    using namespace dargon;

    // Starting up
    dispVer();
    out(true, "Welcome to the Dargon Interpreter (DIR)! For help, type 'help', to exit type 'quit'.");
    out(true, "");
    std::string line = "";
    std::ostringstream os;
    while(true) {
        in(line);
        if(line == "quit") { break; }
        if(line == "memory") { continue; }
        if(line == "help") {
            out(true, "");
            out(true, "**********");
            out(true, "This is the Dargon Interpreter (DIR).");
            out(true, "Type any Dargon code to have it be interpreted.");
            out(true, "");
            out(true, "The following is a list of commands:");
            out(true, "quit          - Exits the interpreter.");
            out(true, "help          - Displays this dialogue.");
            out(true, "memory        - Displays the items currently in memory.");
            out(true, "**********");
            out(true, "");
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

/// @brief Temporary function for testing VM-related stuff.
/// @return Return code for program.
int testVM() {
    using namespace dargon;
    vm::VirtualMachine dvm;
    vm::Nugget nugget = vm::Nugget("Testing \"1.2 + 2.5\"");
    int ind1 = nugget.AddConst(1.2);
    int ind2 = nugget.AddConst(2.5);
    nugget.Add(DARGON_OPCODE_BYTE(vm::OPCODE::CONSTANT));
    nugget.Add(ind1);
    nugget.Add(DARGON_OPCODE_BYTE(vm::OPCODE::CONSTANT));
    nugget.Add(ind2);
    nugget.Add(DARGON_OPCODE_BYTE(vm::OPCODE::ADD));
    nugget.Add(DARGON_OPCODE_BYTE(vm::OPCODE::RETURN));

    dvm.Interpret(&nugget);

    return 0;
}

/// @brief Entry point.
int main(int argc, char* argv[]) {
	
    CLI::App dargonCLI { 
        dargon::VersionString() + "\n" + dargon::Copyright + "\n"
    };
    argv = dargonCLI.ensure_utf8(argv);
    dargonCLI.footer("Running dargon without any arguments will begin the interpreter (DIR).\n");
    dargonCLI.failure_message(CLI::FailureMessage::help);

    //dargonCLI.add_subcommand("init", "Initializes this directory with a simple Dargon environment.");

    dargonCLI.add_flag_function("-v,--version", dispVer, "Display version info.");
    dargonCLI.add_flag("-t,--time", dargon::flags::TimeExecution, "Tracks Dargon's execution time and prints out after completion.");
    dargonCLI.add_flag("--todo", dargon::flags::GenerateTodoReport, "Dargon will analyze the code for all \'To-Do\'-type comments and generate a report.");
    dargonCLI.add_option("-l,--log", dargon::flags::LogSetting, "Sets the log type. Options are: 0 (normal, default), 1 (verbose), 2 (error only), and 3 (none).");
    dargonCLI.add_option("-c,--comp-only", dargon::flags::CompileOnlyNoExecute, "Dargon will compile the input file(s) but will not execute it.");

    std::vector<std::string> files;
    dargonCLI.add_option("files", files, "Files to be ingested by Dargon.");

    CLI11_PARSE(dargonCLI, argc, argv); 

    // Timing
    std::chrono::_V2::steady_clock::time_point start;
    if(dargon::flags::TimeExecution) {
        start = std::chrono::steady_clock::now();
    }

    // Here it is - the interpreter
    dargon::DIR dir;

    if(files.size() > 0) {
        dispVer();
        std::vector<dargon::Path> paths;
        for(std::string s : files) {
            //dargon::out(true, "File: %s", s.c_str())
            paths.push_back(dargon::Path(s));
            //dir.Run()
        }
    }
    else {
        runBasicREPL(dir);
    }

    // Timing
    if(dargon::flags::TimeExecution) {
        auto end = std::chrono::steady_clock::now();
        std::chrono::nanoseconds diff = end - start;
        std::chrono::milliseconds diffMs = std::chrono::duration_cast<std::chrono::milliseconds>(diff);
        std::chrono::seconds diffS = std::chrono::duration_cast<std::chrono::seconds>(diff);
        DARGON_LOG_INFO("Took %ds (%dms)", diffS.count(), diffMs.count());
        //dargon::out(true, "Took %dms", diffMs.count());
    }

    return EXIT_SUCCESS;
}
