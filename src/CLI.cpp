/*
 * Dargon Programming Language
 * (C) Kyle Morris 2023 - See LICENSE.txt for license information.
 *
 * FILE: CLI.cpp
 *
 * DESCRIPTION: Implementation of CLI.h
 *
 * SINCE: v0.1
 *
 */

#include "../include/CLI.h"
#include "../include/Output.h"

namespace dargon {

        CLI::CLI() {}

        CLI::~CLI() {}

        void CLI::RunFile(const std::string& filePath) {}

        void CLI::RunREPL() {
            // TODO: A better error handeling system!
            out("Type 'quit' to quit.");
            std::string line = "";
            while(true) {
                std::cout << "> ";
                getline(std::cin, line);
                if(line == "" || line == "quit") { break; }
                runLine(line);
            }
            out("Goodbye!");
        }

        void CLI::runLine(const std::string& line) {
            InfoLog("Running: " + line);
            _lexer.Input(line);
            out("LEXER:");
            Token t = _lexer.GetNextToken();
            out("   " + t.ToString());
            while(t.IsValid()) {
                t = _lexer.GetNextToken();
                out("   " + t.ToString());
            }
        }

};
