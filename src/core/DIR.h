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
        void Run(Path& filePath);
        void Run(std::string& contents);
	private:
        void _buildError(const Exception* err);
        void _run();

        File _file;
        Lexer _lex;
        Parser _parse;
	};

};

#endif
