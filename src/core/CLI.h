/*
 * Dargon Programming Language
 * (C) Kyle Morris 2023 - See LICENSE.txt for license information.
 *
 * FILE: CLI.h
 *
 * DESCRIPTION: The Command-Line Interface (CLI) for the Dargon Interpreter (DIR).
 *
 * SINCE: v0.1
 *
 */

#ifndef DARGON_CLI_H
#define DARGON_CLI_H

#include <vector>
#include <string>
#include "lex/Lexer.h"

namespace dargon {

	/**
     * @brief Command-Line Interface for DIR.
     * @since v0.1
     * @author Kyle Morris
     *
     * This CLI implementation for the Dargon Interpreter (DIR)
     * includes argument parsing.
    */
	class CLI {
	public:
        /**
         * @brief Constructor.
        */
        CLI(std::vector<std::string> args);

        /**
         * @brief Destructor.
        */
        ~CLI();

        /**
         * @brief Launches Dargon. Returns an appropriate
         * output status code.
         */
        int Run();
	private:
        /**
         * @brief Displays the help dialogue.
        */
        void displayHelp();

        /**
         * @brief Displays in-line help while running the REPL.
         */
        void displayREPLHelp();

        /**
         * @brief Displays the commands for the DIR.
         */
        void displayREPLCommands();

        /**
         * @brief Interprets an input file.
        */
        void runFile(const std::string& filePath);

        /**
         * @brief Runs the Read-Eval-Print Loop (REPL).
        */
        void runREPL();

        /**
         * @brief Sends a line down the pipeline.
        */
        void runLine(const std::string& line);

        /**
         * @brief Arguments.
         */
        std::vector<std::string> _args;

        /**
         * @brief The lexical-analyzer.
         */
        Lexer _lexer;
	};

};

#endif
