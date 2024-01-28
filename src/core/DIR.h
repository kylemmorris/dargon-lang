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
#include "ast/Visitor.h"
#include "runtime/Register.h"

namespace dargon {

	/// @brief The Dargon Interpreter.
	/// @author Kyle Morris
	/// @since v0.1
	class DIR : public IVisitor {
	public:
        void Run(Path& filePath);
        void Run(std::string& contents);

        virtual Register& VisitBinaryExpr(BinaryExpr& binary) override;
		virtual Register& VisitGroupingExpr(GroupingExpr& grouping) override;
		virtual Register& VisitLiteralExpr(LiteralExpr& literal) override;
		virtual Register& VisitUnaryExpr(UnaryExpr& unary) override;
	private:
        Register& _evaluate(Expr* expression);
        void _buildError(const Exception* err);
        void _run();

        File _file;
        Lexer _lex;
        Parser _parse;
	};

};

#endif
