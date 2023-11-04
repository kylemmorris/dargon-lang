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

#include "CLI.h"
#include "Output.h"

namespace dargon {

        CLI::CLI(std::vector<std::string> args) : _args(args) {}

        CLI::~CLI() {}

        int CLI::Run() {
            // 1. If there are no arguments, display help by default
            if(_args.size() == 0 || _args[0] == "help") {
                displayHelp();
                return 0;
            }
            // 2. First argument will either be a command, or just a file path.
            if(_args[0] == "go") {
                // go = run REPL
                runREPL();
                return 0;
            }
            if(_args[0] == "test") {
                // test = Runs all unit tests
                // TODO
            }
            else {
                // otherwise, it's a file path
                // TODO
            }
            return 0;
        }

        void CLI::runFile(const std::string& filePath) {}

        void CLI::runREPL() {
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
                if(line == "commands") {
                    displayREPLCommands();
                    continue;
                }
                if(line == "help") {
                    displayREPLHelp();
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
        }

        void CLI::displayHelp() {
            out("   Usage:");
            out("       dargon help             - Displays this dialogue.");
            out("       dargon go               - Begins the Dargon interactive interpreter.");
            out("       dargon test             - Runs Dargon unit tests.");
            out("       dargon <path>           - Runs a Dargon file (*.dargon or *.dargconf) at the path provided.");
            out("");
        }

        void CLI::displayREPLHelp() {
            out("**********");
            out("This is the Dargon Interpreter (DIR).");
            out("Type any Dargon code to have it interpreted for you.");
            out("Note that what you type must be either full statements (ending in a semicolon ';')");
            out("or full block definitions (starting with '{' and ending in '}').");
            out("");
            out("To view a list of DIR commands, type \'commands\'");
            out("**********");
        }

        void CLI::displayREPLCommands() {
            out("**********");
            out("help          - Displays the help dialogue.");
            out("commands      - Displays this dialogue.");
            out("memory        - Displays the items currently in memory.");
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
