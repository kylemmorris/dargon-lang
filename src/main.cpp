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

/// @brief Displays version information (and logs).
void dispVer() {
    using namespace dargon;
    std::string v = VersionString();
    out(true, v.c_str());
    out(true, Copyright);
    out(true, "");
}

/// @brief Displays the help dialogue.
void help() {
    using namespace dargon;
    // Starting up
    dispVer();
    DARGON_OUT << "Usage: ." << Path::Slash << "dargon {FILE} {OPTIONS}\n\n"; 
    out(true, "FILE (optional):");
    out(true, "                    A Dargon source file to run (*.dargon).");
    out(true, "OPTIONS (optional):");
    out(true, "   -h:              Displays this dialogue.");
    out(true, "   -v:              Displays version and copyright information.");
    out(true, "   -t:              Tracks Dargon's execution time and prints out after completion.");
    out(true, "   -c:              Dargon will compile the input file but will not execute it.");
    out(true, "   -r:              Dargon will analyze the code for all \'To-Do\'-type comments and generate a report.");
    out(true, "   -s:              Creates a sample Dargon environment in the current, empty directory.");
    out(true, "   -g:              Opens the Dargon GUI (Dargui).");
    out(true, "   -n:              Runs the Dargon unit test suite and creates a report.");
    out(true, "   -x:              Clears the Dargon cache.");
    out(true, "   -l [option]:     Sets the log type. Options are: 'verbose', 'normal' (default), 'error-only', and 'none'.");
    out(true, "");
    out(true, "Running dargon without any arguments will begin the interpreter (DIR).");
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
    using namespace dargon;

    // This is the Dargon Interpreter (DIR)
    DIR dir;

    // If no inputs were provided, begin REPL
    if(argc == 1) {
        runBasicREPL(dir);
        return EXIT_SUCCESS;
    }

    // Parse CLI using 'getopt'
    int opt = 0;
    const char* options = "hvtcrsgnxl:";
    char* logType = NULL;
    while((opt = getopt(argc, argv, options)) != -1) {
        switch(opt) {
            case 'h': help(); opt = -1; break;
            case 'v': dispVer(); opt = -1; break;
            case 't': flags::TimeExecution = true; break;
            case 'c': flags::CompileOnlyNoExecute = true; break;
            case 'r': flags::GenerateTodoReport = true; break;
            case 'l': {
                logType = optarg;
                if(std::strcmp(logType, "verbose") == 0) {
                    flags::LogSetting = flags::LogSeverity::VERBOSE;
                }
                else if(std::strcmp(logType, "normal") == 0)  {
                    flags::LogSetting = flags::LogSeverity::NORMAL;
                }
                else if(std::strcmp(logType, "error-only") == 0) {
                    flags::LogSetting = flags::LogSeverity::ERROR_ONLY;
                }
                else if(std::strcmp(logType, "none") == 0)  {
                    flags::LogSetting = flags::LogSeverity::NONE;
                }
                else {
                    DARGON_OUT << "Invalid log type: " << logType << "\n";
                    exit(EXIT_FAILURE);
                }
                break;
            }
            case 's': out(true, "'-s' not implemented yet..."); break; // setup
            case 'g': out(true, "'-g' not implemented yet..."); break; // gui
            case 'n': out(true, "'-n' not implemented yet..."); break; // test
            case 'x': out(true, "'-x' not implemented yet..."); break; // clean
            default: abort();
        }
    }

    // Multiple files...?
    /* for(int i = optind; i < argc; i++) {
        out(argv[i]);
    } */

    /*
    Use FILE*, stderr, and fprintf() combination for this:

    DARGON_LOG_INFO("Total Execution Time: %d s", 10.0);
    (this prints to dargon.log and ALSO to the output):
    Total Execution Time: 10 s
    (log)
    time [INFO]: Total Execution Time: 10 s

    */

    std::chrono::_V2::steady_clock::time_point start;
    if(flags::TimeExecution) {
        start = std::chrono::steady_clock::now();
    }

    // Run the inputted file
    if(optind < argc) {
        Path p = Path(argv[optind]);
        dispVer();
        dir.Run(p);
    }

    if(flags::TimeExecution) {
        auto end = std::chrono::steady_clock::now();
        auto diff = end - start;
    }

    //fprintf(stderr, "Test");

    return EXIT_SUCCESS;
}
