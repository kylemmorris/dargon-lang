/**
 * Dargon Programming Language
 * (C) Kyle Morris 2023 - See LICENSE.txt for license information.
 *
 * @file LexerTests.h
 * @author Kyle Morris
 * @since v0.1
 * @section Description
 * Contains all of the unit tests for the lexer part of the interpreter.
 *
 */

#ifndef DARGON_HEADER_LEXER_TESTS
#define DARGON_HEADER_LEXER_TESTS

#include "TestingMacros.h"
#include "../core/lex/Lexer.h"

namespace dargon {

    /// @brief Test tokens for validity.
    DARGON_UNIT_TEST(ValidTokens,

        Token c1 = Token();
        Token c2 = Token(Token::Kind::ASSIGNMENT, FilePosition(2,2));
        Token c3 = Token(Token::Kind::ID, "test", FilePosition(12, 1));

        DARGON_TEST_ASSERT(!c1.IsValid());
        DARGON_TEST_ASSERT(c2.IsValid());
        DARGON_TEST_ASSERT(c3.IsValid());

    )

    /// @brief Test token keywords.
    DARGON_UNIT_TEST(KeywordTokens,

        Token c1 = Token(Token::Kind::CONST_MUT);
        Token c2 = Token(Token::Kind::VAR_MUT);

        DARGON_TEST_ASSERT(c1.GetKind() > Token::Kind::__KEYWORDS__ && c2.GetKind() > Token::Kind::__KEYWORDS__);

    )

    /// @brief Tests Token::ToString.
    DARGON_UNIT_TEST(TokenToString,

        Token c1 = Token();
        Token c2 = Token(Token::Kind::CONST_MUT, FilePosition(1,1));
        Token c3 = Token(Token::Kind::ID, "test", FilePosition(31,4));

        DARGON_TEST_ASSERT(c1.ToString() == "[(!?) @ Line 1 Col 1]");
        DARGON_TEST_ASSERT(c1.ToString() == "[const @ Line 1 Col 1]");
        DARGON_TEST_ASSERT(c1.ToString() == "[ID, test @ Line 31 Col 4]");

    )

};

#endif

