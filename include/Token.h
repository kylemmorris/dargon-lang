/*
 * Dargon Programming Language
 * (C) Kyle Morris 2023 - See LICENSE.txt for license information.
 *
 * FILE: Token.h
 *
 * DESCRIPTION: A 'token' is what the source program is converted into by the lexer, and
 *              it can represent any number of characters in a sequence (identifiers, keywords, etc.).
 *
 * SINCE: v0.1
 *
 */

#ifndef DARGON_TOKEN_H
#define DARGON_TOKEN_H

#include <string>
#include <map>

namespace dargon {

    /**
     * @brief Enumeration of the types of tokens.
    */
    enum class TokenType {
		EOF_TYPE, 				// End-Of-File
		INVALID,				// An invalid token
		COMMA,					// ','
		STMT_END,				// ';'
		PERIOD,					// '.'
		LPAREN, RPAREN,			// ( and )
		LBRACK, RBRACK,			// [ and ]
		LBLOCK, RBLOCK,         // { and }
		GT, LT, GTE, LTE,		// >, <, >=, <=
		OP_PLUS,				// '+'
		OP_MINUS,				// '-'
		OP_MULT,				// '*'
		OP_DIV,					// '/'
		OP_EQ, OP_NEQ,			// '=' and '/='
		RANGE,					// '..'
		ESCAPE,					// '\'
		ASSIGN,					// ':='
		IDENTIFIER,				// Any non-keyword identifier.
		STR_LITERAL,			// String literal
		INT_LITERAL,			// Int literal
		REAL_LITERAL,			// Real literal
		RESERVED,				// Anything below this is a reserved word
		BOOL_LIT_T,             // 'true'
		BOOL_LIT_F,             // 'false'
		FUNCTION_DEF,			// 'fun'
		IF,						// 'if'
		ELSE,					// 'else'
		LOOP,					// 'loop'
		AND, OR, NOT            // 'and', 'or', and 'not'.
    };

    /**
     * @brief The set of all keywords.
    */
    static const std::map<std::string, TokenType> Keywords = {
        {"fun", TokenType::FUNCTION_DEF},
        {"if", TokenType::IF},
        {"else", TokenType::ELSE},
        {"loop", TokenType::LOOP},
        {"and", TokenType::AND},
        {"or", TokenType::OR},
        {"not", TokenType::NOT}
    };

    /**
     * @brief String representations for each type.
    */
    static const std::string TypeNames[] = {
        "EOF", 				// End-Of-File
        "INVALID",				// An invalid token
        "COMMA",					// ','
        "STMT_END",				// ';'
        "PERIOD",					// '.'
        "LPAREN", "RPAREN",			// ( and )
        "LBRACK", "RBRACK",			// [ and ]
        "LBLOCK," "RBLOCK",         // { and }
        "GT", "LT", "GTE", "LTE",		// >, <, >=, <=
        "OP_PLUS",				// '+'
        "OP_MINUS",				// '-'
        "OP_MULT",				// '*'
        "OP_DIV",					// '/'
        "OP_EQ", "OP_NEQ",			// '=' and '/='
        "RANGE",					// '..'
        "ESCAPE",					// '\'
        "ASSIGN",					// ':='
        "IDENTIFIER",				// Any non-keyword identifier.
        "STR_LITERAL",			// String literal
        "INT_LITERAL",			// Int literal
        "REAL_LITERAL",			// Real literal
        "RESERVED",				// Anything below this is a reserved word
        "BOOL_LIT_T",             // 'true'
        "BOOL_LIT_F",             // 'false'
        "FUNCTION_DEF",			// 'fun'
        "IF",						// 'if'
        "ELSE",					// 'else'
        "LOOP"					// 'loop'
        "AND", "OR", "NOT"            // 'and', 'or', and 'not'.
    };

    /**
	 * Returns if the inputted text is a keyword or not.
	 * Will return TokenType::INVALID if it is not, and the
	 * appropriate type otherwise.
	 */
    TokenType IsKeyword(const std::string& input);

	/**
     * @brief A lexical token.
    */
	struct Token final {
	public:
        Token();
        Token(const TokenType& type);
        Token(const TokenType& type, const std::string& val);

        bool IsValid() const;
        std::string ToString() const;

        TokenType type;
        std::string value;
	};

};

#endif
