/*
 * Dargon Programming Language
 * (C) Kyle Morris 2023 - See LICENSE.txt for license information.
 *
 * FILE: Lexer.h
 *
 * DESCRIPTION: The first phase of the interpreter takes as input a string
 *              representing the file, and produces a stream of tokens to
 *              the parser.
 *
 * SINCE: v0.1
 *
 */

#ifndef DARGON_LEXER_H
#define DARGON_LEXER_H

#include <string>
#include "../Log.h"
#include "Token.h"

namespace dargon {

	/**
     * @brief The first phase of the interpreter - turns an input
     * into a stream of tokens.
    */
	class Lexer {
	public:
        /**
         * @brief Constructor.
        */
        Lexer();
        /**
         * @brief Initializes the lexer with an input sequence.
        */
        void Input(const std::string& data);
        /**
         * @brief Provides the next token.
        */
        Token GetNextToken();
	private:
        // The buffered input. TODO What about large files?
        std::string  _input;
        // The length of the input, so we know when to stop.
        int  _inputLen;
        // The current index of the lexer in the char stream.
        int  _index;
        // The current character.
        char _char;
        // The position in the file, to be passed to each token as metadata.
        FilePosition _pos;

        /**
	    * "Consumes" the character, i.e., advances the index.
	    */
        void _consume();
        /**
	    * Ignore any and all whitespace.
	    */
        void _whitespace();
        /**
         * A line comment. Consumes until a newline is read.
         * Starts with '#'.
         */
        void _lineComment();
        /**
         * A block comment: ## block comment ##
         */
        void _blockComment();
        /**
         * Number literal.
        */
        Token _numLit();
        /**
         * String literal "string"
        */
        Token _strLit();
        /**
         * Returns if it's an actual identifier. Can begin with
         * '_' and can contain letters, numbers, and '?'.
         */
        Token _identifier();
	};

};

#endif
