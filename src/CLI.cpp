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
            out("Type 'help' for help, or 'quit' to quit.");
            std::string line = "";
            std::string cont = "";
            bool inBlock = false;
            while(true) {
                std::cout << "DIR> ";
                // Read the line
                getline(std::cin, line);
                if(line == "quit") { break; }
                if(line == "help") {
                    displayHelp();
                    continue;
                }
                // If it doesn't end in ';' or '}', likely means the line continues.
                if(line.find_last_of('{') != std::string ::npos) {
                    inBlock = true;
                }
                if(inBlock) {
                    while(line.find_last_of('}') == std::string::npos) {
                        std::cout << ".    ";
                        getline(std::cin, cont);
                        line += cont;
                    }
                    inBlock = false;
                }
                else {
                    while(line.find_last_of(';') == std::string::npos) {
                        std::cout << ".    ";
                        getline(std::cin, cont);
                        line += cont;
                    }
                }
                if(line == "") { break; }
                runLine(line);
            }
            out("Goodbye!");
        }

        void CLI::displayHelp() {
            out("**********");
            out("This is the Dargon Interpreter (DIR).");
            out("Type any Dargon code to have it interpreted for you.");
            out("Note that what you type must be either full statements (ending in a semicolon ';')");
            out("or full block definitions (starting with '{' and ending in '}').");
            out("**********");
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
