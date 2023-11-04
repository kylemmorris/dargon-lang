/*
 * Dargon Programming Language
 * (C) Kyle Morris 2023 - See LICENSE.txt for license information.
 *
 * FILE: ASTTests.h
 *
 * DESCRIPTION: Defines the AST unit tests.
 *
 * SINCE: v0.1
 *
 */

#ifndef DARGON_AST_TESTS_H
#define DARGON_AST_TESTS_H

#include "TestingMacros.h"
#include "../core/ast/ASTPrinter.h"

namespace dargon {

    DARGON_UNIT_TEST(ASTSimpleExpressions) {

        // (* (- 123) (group 45.67))
        LiteralExpr l1("123");
        LiteralExpr l2("45.67");
        UnaryExpr neg(Token(TokenType::OP_MINUS,"-"), &l1);
        GroupingExpr g(&l2);
        BinaryExpr exp(&neg, Token(TokenType::OP_MULT, "*"), &g);
        ASTPrinter printer;

        std::string result = printer.Print(&exp);
        DARGON_TEST_ASSERT(result == "(* (- 123) (group 45.67))");
    }};

};

#endif
