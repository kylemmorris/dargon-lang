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
#include "core/Output.h"
#include "core/Log.h"
#include "core/CLI.h"

int main(int argc, char* argv[]) {
    using namespace dargon;

    // Starting up
    out(VersionString());
    out("(C) Kyle Morris 2023 - See LICENSE.txt for license information.\n");
    InfoLog(VersionString() + " starting.");

    // Collect inputs
    std::vector<std::string> inputs;
    for(int i = 1; i < argc; i++) {
        inputs.push_back(std::string(argv[i]));
    }

    // The Command-Line Interface. To be built upon as we go.
    CLI cli = CLI(inputs);

    return cli.Run();
}
