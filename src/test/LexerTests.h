/*
 * Dargon Programming Language
 * (C) Kyle Morris 2023 - See LICENSE.txt for license information.
 *
 * FILE: LexerTests.h
 *
 * DESCRIPTION: Contains unit tests for the lexical analysis portion of DIR.
 *
 * SINCE: v0.1
 *
 */

#ifndef DARGON_LEXER_TESTS_H
#define DARGON_LEXER_TESTS_H

#include "TestingMacros.h"
#include "../core/lex/Lexer.h"

namespace dargon {

    /**
    * @brief Tests token validity
    */
    DARGON_UNIT_TEST(ValidTokens) {

        Token c1 = Token();
        Token c2 = Token(TokenType::AND, "AND");
        Token c3 = Token(TokenType::ASSIGN, "=", FilePosition(2,2));

        DARGON_TEST_ASSERT(!c1.IsValid());
        DARGON_TEST_ASSERT(c2.IsValid());
        DARGON_TEST_ASSERT(c3.IsValid());

    }};

    /**
    * @brief Tests token keywords
    */
    DARGON_UNIT_TEST(KeywordTokens) {

        Token c1 = Token(TokenType::IF, "if");
        Token c2 = Token(TokenType::ELSE, "else");
        Token c3 = Token(TokenType::GT, ">");

        DARGON_TEST_ASSERT(IsKeyword(c1.type) != TokenType::INVALID);
        DARGON_TEST_ASSERT(IsKeyword(c2.type) != TokenType::INVALID);
        DARGON_TEST_ASSERT(IsKeyword(c3.type) == TokenType::INVALID);

    }};


    /**
    * @brief Tests token ToString() function
    */
    DARGON_UNIT_TEST(TokenToString) {

        Token c1 = Token();
        Token c2 = Token(TokenType::OP_DIV, "/");
        Token c3 = Token(TokenType::IDENTIFIER, "dargon");

        DARGON_TEST_ASSERT(c1.ToString() == "<INVALID:>");
        DARGON_TEST_ASSERT(c2.ToString() == "<OP_DIV:/>");
        DARGON_TEST_ASSERT(c3.ToString() == "<IDENTIFIER:dargon>");

    }};

};

#endif

