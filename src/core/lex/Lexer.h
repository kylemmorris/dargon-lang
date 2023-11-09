/**
 * Dargon Programming Language
 * (C) Kyle Morris 2023 - See LICENSE.txt for license information.
 *
 * @file Lexer.h
 * @author Kyle Morris
 * @since v0.1
 * @section Description
 * This is the first phase of the interpreter. It takes an input
 * file and outputs a stream of Tokens, which are used in the
 * parsing phase.
 *
 */

#ifndef DARGON_HEADER_LEXER
#define DARGON_HEADER_LEXER

#include <string>
#include "../Log.h"
#include "Token.h"

namespace dargon {

    /// @brief The first phase of the interpreter. Provides an API for converting an input into a Token stream.
    /// @author Kyle Morris
    /// @since v0.1
    /// @throws LexerException
    class Lexer {
    public:
        /// @brief Constructor.
        Lexer();

        /// @brief Destructor.
        ~Lexer();

        /// @brief Sets the input as the data to be converted.
        /// @param data The input data.
        void Buffer(const std::string& data);

        /// @brief Provides the next token from the input data.
        /// @returns A Token object.
        Token Next();
    private:
        std::string _data;          ///< The input data.
        FilePosition _pos;          ///< The current file position.
        int _index;                 ///< Current index into the data.
        int _len;                   ///< Lenght of the input data.
        char _curr;                 ///< The current character.

        /// @brief Consumes a character.
        void consume();

        /// @brief Ignores all whitespace.
        void whitespace();

        /// @brief Ignores a comment line (starting with pound (#)).
        void commentLine();

        /// @brief Ignores a comment block (starting and ending with ##).
        void commentBlock();

        /// @returns A number literal token.
        Token numLit();

        /// @returns A string literal token.
        Token strLit();

        /// @returns An identifier OR keyword token.
        Token identifier();
    };

};

#endif
