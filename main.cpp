/*
 * Dargon Programming Language
 * (C) Kyle Morris 2023 - See LICENSE.txt for license information.
 *
 * FILE: main.cpp
 *
 * DESCRIPTION: Main file.
 *
 * SINCE: v0.1
 */

#include <vector>
#include "include/Output.h"
#include "include/Log.h"
#include "include/CLI.h"

int main(int argc, char* argv[]) {
    using namespace dargon;

    // Starting up
    out(VersionString());
    out("(C) Kyle Morris 2023 - See LICENSE.txt for license information.\n");
    InfoLog(VersionString() + " starting.");

    // The Command-Line Interface. To be built upon as we go.
    CLI cli;

    // Number of arguments
    std::string path = "";
    switch(argc) {
    case 1:
        // REPL
        InfoLog("Starting REPL...");
        cli.RunREPL();
        break;
    case 2:
        // Input file
        path = argv[1];
        InfoLog("Parsing file: " + path);
        cli.RunFile(path);
        break;
    default:
        out("Usage: dargon [input file]");
        break;
    }

    return 0;
}
