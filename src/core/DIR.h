/**
 * Dargon Programming Language
 * (C) Kyle Morris 2023 - See LICENSE.txt for license information.
 *
 * @file DIR.h
 * @author Kyle Morris
 * @since v0.1
 * @section Description
 * The Dargon Interpreter, made up of its modules.
 *
 */

#ifndef DARGON_HEADER_DIR
#define DARGON_HEADER_DIR

#include <stack>
#include "Error.h"
#include "IO.h"
#include "File.h"
#include "lex/Lexer.h"
#include "parser/Parser.h"

namespace dargon {

	/// @brief The Dargon Interpreter.
	/// @author Kyle Morris
	/// @since v0.1
	class DIR {
	public:
        void Run(const Path& filePath);
        void Run(const std::string& contents);
	private:
        void _clearErrors();
        void _run();

        std::stack<Error> _errors;

        File _file;
        Lexer _lex;
        Parser _parse;
	};

};

#endif
