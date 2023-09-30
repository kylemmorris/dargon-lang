/*
 * Dargon Programming Language
 * (C) Kyle Morris 2023 - See LICENSE.txt for license information.
 *
 * FILE: ASTPrinter.cpp
 *
 * DESCRIPTION: Implementation of ASTPrinter.
 *
 * SINCE: v0.1
 *
 */

#include <sstream>
#include <cstdarg>
#include "ASTPrinter.h"

namespace dargon {

    ASTPrinter::ASTPrinter() {}

    void ASTPrinter::Print(Expr* exp) {
        exp->Accept(*this);
    }

    void ASTPrinter::VisitBinaryExpr(BinaryExpr& binary) {
        _parenthesize(binary.op.value, binary.left);
    }

    void ASTPrinter::VisitGroupingExpr(GroupingExpr& grouping) {
        _parenthesize("group", grouping.expression);
    }

    void ASTPrinter::VisitLiteralExpr(LiteralExpr& literal) {
        if(literal.value.size() == 0) {
            std::cout << "nil";
        }
        else {
            std::cout << literal.value;
        }
    }

    void ASTPrinter::VisitUnaryExpr(UnaryExpr& unary) {
        _parenthesize(unary.op.value, unary.right);
    }

    void ASTPrinter::_parenthesize(const std::string& name, Expr* expr...) {
        std::ostringstream os;
        os << "(" << name;
        //va_list args;
        //va_start(args, expr);

        expr->Accept(*this);
        os << ")";
        std::cout << os.str();
    }

};
