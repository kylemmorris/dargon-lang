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
#include "core/Output.h"
#include "core/Log.h"
#include "core/lex/Lexer.h"
#include "core/parser/Parser.h"
#include "core/ast/ASTPrinter.h"
#include "core/File.h"

/// @brief Displays the help dialogue.
void help() {
    using namespace dargon;
    out("   Usage:");
    out("       dargon help             - Displays this dialogue.");
    out("       dargon go               - Begins the Dargon interactive interpreter.");
    out("       dargon test             - Runs Dargon unit tests.");
    out("       dargon <path>           - Runs a Dargon file (*.dargon or *.dargconf) at the path provided.");
    out("");
}

/// @brief A basic REPL implementation.
void runBasicREPL() {
    using namespace dargon;
    Lexer lex;
    Parser parser;
    out("Welcome! For help, type 'help'");
    out("");
    std::string line = "";
    std::ostringstream os;
    while(true) {
        out("DIR> ",false);
        // Read line
        getline(std::cin, line);
        if(line == "quit") { break; }
        if(line == "help") {
            out("");
            out("**********");
            out("This is the Dargon Interpreter (DIR).");
            out("Type any code to have it be interpreted.");
            out("");
            out("The following is a list of commands:");
            out("quit          - Exits the interpreter.");
            out("help          - Displays this dialogue.");
            out("memory        - Displays the items currently in memory.");
            out("**********");
            out("");
            continue;
        }
        // Begin interpreter
        out("");
        lex.Buffer(line);
        out("INPUT: " + line);
        TokenList toks = lex.GetAllTokens();
        if(lex.ErrorOccured()) {
            continue;
        }
        DARGON_LOG_INFO("LEXER:");
        for(Token t : toks) {
            os << "    " << t.ToString() << std::endl;
        }
        DARGON_LOG_INFO(os.str());
        os.str("");
        out("");
        DARGON_LOG_INFO("PARSER: ");
        os.str("");
        parser.Buffer(toks);
        Expr* expression = parser.Parse();
        // If it was valid
        if(expression != nullptr) {
            ASTPrinter printer;
            DARGON_LOG_INFO("   " + printer.Print(expression));
            delete expression;
        }
        out("");
        out("");
    }
}

/// @brief Entry point.
int main(int argc, char* argv[]) {
    using namespace dargon;

    // Starting up
    DARGON_LOG_INFO(VersionString());
    DARGON_LOG_INFO("(C) Kyle Morris 2023 - See LICENSE.txt for license information.");
    out("");

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
    else if(inputs[0] == "gui") {
        out("Not implemented yet...");
    }
    else if(inputs[0] == "test") {
        out("Not implemented yet...");
    }
    else {
        // It's a file path
        Path p = Path(inputs[0]);
        if(!File::Exists(p)) {
            DARGON_LOG_ERROR("File not found: " + p.GetFull());
            return 1;
        }
        // The following will depend on file
        Script s;
        Lexer l;
        switch(p.GetFileExtension()) {
            case Path::Extension::DARGON:
                if(s.OpenAbsolute(p)) {
                    DARGON_LOG_INFO(s.PrintAllContents());
                    // Try to run the lexer on this file
                }
                else {
                    DARGON_LOG_ERROR("Could not open file: " + inputs[0]);
                }
                break;
            case Path::Extension::DARGON_CONFIG:
                DARGON_LOG_INFO("Not currently implemented!");
                break;
            default:
                DARGON_LOG_ERROR("Unsupported file type: " + inputs[0]);
                break;
        };
    }

    return 0;
}
