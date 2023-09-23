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

#include <map>
#include "../Exception.h"
#include "../FilePosition.h"

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
		OP_EQ, OP_NEQ,			// '==' and '~='
		RANGE,					// '..'
		TILDE,                  // '~'
		ESCAPE,					// '\'
		ASSIGN,					// '='
		FLOW_L, FLOW_R,         // '<-' and '->'
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
     * @brief Returns a string representation
     * of each type.
    */
    static std::string TypeName(const TokenType& type) {
        switch(type) {
            case TokenType::EOF_TYPE: return "EOF";
            case TokenType::INVALID: return "INVALID";
            case TokenType::COMMA: return "COMMA";
            case TokenType::STMT_END: return "STMT_END";
            case TokenType::PERIOD: return "PERIOD";
            case TokenType::LPAREN: return "LPAREN";
            case TokenType::RPAREN: return "RPAREN";
            case TokenType::LBRACK: return "LBRACK";
            case TokenType::RBRACK: return "RBRACK";
            case TokenType::LBLOCK: return "LBLOCK";
            case TokenType::RBLOCK: return "RBLOCK";
            case TokenType::GT: return "GT";
            case TokenType::LT: return "LT";
            case TokenType::GTE: return "GTE";
            case TokenType::LTE: return "LTE";
            case TokenType::OP_PLUS: return "OP_PLUS";
            case TokenType::OP_MINUS: return "OP_MINUS";
            case TokenType::OP_MULT: return "OP_MULT";
            case TokenType::OP_DIV: return "OP_DIV";
            case TokenType::OP_EQ: return "OP_EQ";
            case TokenType::OP_NEQ: return "OP_NEW";
            case TokenType::RANGE: return "RANGE";
            case TokenType::TILDE: return "TILDE";
            case TokenType::ESCAPE: return "ESCAPE";
            case TokenType::ASSIGN: return "ASSIGN";
            case TokenType::FLOW_L: return "FLOW_L";
            case TokenType::FLOW_R: return "FLOW_R";
            case TokenType::IDENTIFIER: return "IDENTIFIER";
            case TokenType::STR_LITERAL: return "STRING LITERAL";
            case TokenType::INT_LITERAL: return "INT LITERAL";
            case TokenType::REAL_LITERAL: return "REAL LITERAL";
            case TokenType::BOOL_LIT_T: return "BOOL LITERAL TRUE";
            case TokenType::BOOL_LIT_F: return "BOOL LITERAL FALSE";
            case TokenType::FUNCTION_DEF: return "FUNCTION DEF";
            case TokenType::IF: return "IF";
            case TokenType::ELSE: return "ELSE";
            case TokenType::LOOP: return "LOOP";
            case TokenType::AND: return "AND";
            case TokenType::OR: return "OR";
            case TokenType::NOT: return "NOT";
            default: break;
        };
        throw new Exception("Unsupported token type!");
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
        /**
        * @brief The invalid token constructor.
        */
        Token();
        /**
        * @brief The token constructor without metadata.
        */
        Token(const TokenType& type, const std::string& val);
        /**
        * @brief The normal token constructor.
        */
        Token(const TokenType& type, const std::string& val, const FilePosition& pos);


        /**
        * @brief Returns if this is a valid token.
        */
        bool IsValid() const;
        /**
        * @brief Returns the token as "<TYPE : VALUE>"
        */
        std::string ToString() const;

        TokenType type;
        std::string value;
        FilePosition location;
	};

};

#endif
