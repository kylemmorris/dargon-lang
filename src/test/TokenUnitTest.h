/*
 * Dargon Programming Language
 * (C) Kyle Morris 2023 - See LICENSE.txt for license information.
 *
 * FILE: TokenUnitTest.h
 *
 * DESCRIPTION: A unit test class for token-related functionality.
 *
 * SINCE: v0.1
 *
 */

#ifndef DARGON_TOKEN_UTEST_H
#define DARGON_TOKEN_UTEST_H

#include "../core/lex/Token.h"
#include "TestResult.h"

namespace dargon {
namespace test {

    DARGON_UNIT_TEST TokenUnitTest() {

        DARGON_UNIT_TEST_BEGIN("Checking Token code...")

        Token t = Token();

        DARGON_UNIT_TEST_ASSERT(!t.IsValid(), "Default Token constructor should be invalid.")

        Token t1 = Token(TokenType::AND, "AND");
        Token t2 = Token(TokenType::OR, "OR");

        DARGON_UNIT_TEST_ASSERT(t1.type != t2.type, "Something went wrong with token comparison.")

        DARGON_UNIT_TEST_END

    }


}}; // dargon::test

#endif
