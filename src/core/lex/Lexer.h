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
#include "../Module.h"

namespace dargon {

    /// @brief The first phase of the interpreter. Provides an API for converting an input into a Token stream.
    /// @author Kyle Morris
    /// @since v0.1
    class Lexer : public Module {
    public:
        /// @brief Constructor.
        Lexer();

        /// @brief Destructor.
        ~Lexer();

        /// @brief Expects an input file to draw information from.
        /// @param file The input file.
        void Buffer(File* file);

        /// @brief Override from Module.
        virtual Error Work() override;

        /// @brief Provides the next token from the input data.
        /// @returns A Token object.
        Token Next();

        /// @brief Provides all the tokens from the input.
        /// @returns The token stream.
        TokenList GetAllTokens() const { return _output; }
    private:
        File* _data;        ///< The data.
        char _curr;         ///< The current character.
        TokenList _output;  ///< The output from the Lexer.

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
