/**
 * Dargon Programming Language
 * (C) Kyle Morris 2023 - See LICENSE.txt for license information.
 *
 * @file Parser.h
 * @author Kyle Morris
 * @since v0.1
 * @section Description
 * This contains the description of the LL(1)
 * Recursive Descent Parser.
 *
 */

#ifndef DARGON_HEADER_PARSER
#define DARGON_HEADER_PARSER

#include "../ast/Expr.h"

namespace dargon {

	/// @brief LL(1) Recursive Descent Parser
	/// @author Kyle Morris
	/// @since v0.1
	class Parser {
	public:
        /// @brief Constructor. Accepts a
        /// list of Tokens.
        Parser(const TokenList& tokens);
	private:
        /// The input of the Parser.
        TokenList _tokens;
        /// Iterator to the current token.
        TokenList::iterator _current;

        inline bool _match(std::initializer_list<Token::Kind> kinds);
        inline bool _check(const Token::Kind& kind);
        inline Token _next();
        inline bool _end() const;
        inline Token _peek() const;
        inline Token _prev() const;

        // ---- GRAMMER RULE DEFINITIONS ----

        Expr* _expression();
        Expr* _equality();
        Expr* _comparison();

	};

};

#endif
