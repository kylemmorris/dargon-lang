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

#include <string>
#include "Lexer.h"

namespace dargon {

	/**
     * @brief Command-Line Interface for DIR.
    */
	class CLI {
	public:
        /**
         * @brief Constructor.
        */
        CLI();

        /**
         * @brief Destructor.
        */
        ~CLI();

        /**
         * @brief Interprets an input file.
        */
        void RunFile(const std::string& filePath);

        /**
         * @brief Runs the Read-Eval-Print Loop (REPL).
        */
        void RunREPL();
	private:
        /**
         * @brief Sends a line down the pipeline.
        */
        void runLine(const std::string& line);

        Lexer _lexer;
	};

};

#endif
