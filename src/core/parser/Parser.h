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

        /// @brief Matches a token with an expected list of tokens, and consumes it.
        inline bool _match(std::initializer_list<Token::Kind> kinds);
        /// @brief Checks if a token is of the kind shown. Does not consume.
        inline bool _check(const Token::Kind& kind);
        /// @brief Consumes a token.
        inline Token _next();
        /// @brief Returns true if there are no more tokens to consume.
        inline bool _end() const;
        /// @brief Returns the current token without consuming.
        inline Token _peek() const;
        /// @brief Returns the last-consumed token.
        inline Token _prev() const;
        /// @brief Tries to consume a token, and will throw a parsing exception if it's not expected.
        /// @throw ParsingException
        inline Token _consume(const Token::Kind& type, const std::string& msg);
        /// @brief Used in all parts of the parser to throw the ParsingException.
        /// @throw ParsingException
        inline ParsingException error(const Token& token, const std::string& msg);

        // ---- GRAMMER RULE DEFINITIONS ----

        /// @brief The starting expression rule.
        /// Maps to: expression = equality
        Expr* _expression();

        /// @brief equality = comparison ( ("!="|"==") comparison )* ;
        /// This essentially handles equality of any order.
        /// e.g. a == b, a == b == c, etc.
        Expr* _equality();

        /// @brief comparison = term ( (">"|">="|"<"|"<=") term)* ;
        /// Handles value comparison of any order.
        Expr* _comparison();

        /// @brief term = factor ( ("-" | "+") factor)* ;
        Expr* _term();

        /// @brief factor = unary ( ("/" | "*") factor)* ;
        Expr* _factor();

        /// @brief unary = ("!" | "-") unary | primary ;
        Expr* _unary();

        /// @brief primary = NUMBER | STRING | "true" | "false" | "(" expression ")" ;
        Expr* _primary();

	};

};

#endif
