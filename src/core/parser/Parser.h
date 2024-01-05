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
#include "../Log.h"

namespace dargon {

	/// @brief LL(1) Recursive Descent Parser
	/// @author Kyle Morris
	/// @since v0.1
	class Parser {
	public:
        /// @brief Constructor
        Parser();

        /// @brief Destructor
        ~Parser();

        /// @brief Buffers the parser with a sequential list of tokens.
        void Buffer(const TokenList& tokens);

        /// @brief Parses the token stream and returns the heap-allocated expression.
        /// @return Heap-allocated expression. Make sure to call 'delete'!
        Expr* Parse();
	private:
        /// The input of the Parser.
        TokenList _tokens;
        /// Iterator to the current token.
        TokenList::iterator _current;

        /// @brief Matches a token with an expected list of tokens, and consumes it.
        inline bool match(std::initializer_list<Token::Kind> kinds);
        /// @brief Checks if a token is of the kind shown. Does not consume.
        inline bool check(const Token::Kind& kind);
        /// @brief Consumes a token.
        inline Token next();
        /// @brief Returns true if there are no more tokens to consume.
        inline bool atEnd() const;
        /// @brief Returns the current token without consuming.
        inline Token peek() const;
        /// @brief Returns the last-consumed token.
        inline Token prev() const;
        /// @brief Tries to consume a token, and will throw a parsing exception if it's not expected.
        /// @throw ParsingException
        inline Token consume(const Token::Kind& type, const std::string& msg);
        /// @brief After an error is thrown, this method is used to synchronize
        /// the Parser back to a stable state.
        inline void synchronize();

        // ---- GRAMMER RULE DEFINITIONS ----

        /// @brief The starting expression rule.
        /// Maps to: expression = equality
        Expr* expression();

        /// @brief equality = comparison ( ("!="|"==") comparison )* ;
        /// This essentially handles equality of any order.
        /// e.g. a == b, a == b == c, etc.
        Expr* equality();

        /// @brief comparison = term ( (">"|">="|"<"|"<=") term)* ;
        /// Handles value comparison of any order.
        Expr* comparison();

        /// @brief term = factor ( ("-" | "+") factor)* ;
        Expr* term();

        /// @brief factor = unary ( ("/" | "*") factor)* ;
        Expr* factor();

        /// @brief unary = ("!" | "-") unary | primary ;
        Expr* unary();

        /// @brief primary = NUMBER | STRING | "true" | "false" | "(" expression ")" ;
        Expr* primary();

	};

};

#endif
