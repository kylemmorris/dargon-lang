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
#include "ASTPrinter.h"

namespace dargon {

    std::string ASTPrinter::Print(Expr* expr) {
        return expr->Accept(this);
    }

    std::string ASTPrinter::VisitBinaryExpr(BinaryExpr* binary) {
        return _parenthesize(binary->op.ToString(), binary->left);
    }

    std::string ASTPrinter::VisitGroupingExpr(GroupingExpr* grouping) {
        return _parenthesize("group", grouping->expression);
    }

    std::string ASTPrinter::VisitLiteralExpr(LiteralExpr* literal) {
        if(!literal->value.has_value()) {
            return "nil";
        }
        return std::any_cast<std::string>(literal->value);
    }

    std::string ASTPrinter::VisitUnaryExpr(UnaryExpr* unary) {
        return _parenthesize(unary->op.ToString(), unary->right);
    }

    std::string ASTPrinter::_parenthesize(const std::string& name, Expr* expr) {
        std::ostringstream os;
        os << "(" << name;
        os << " " << expr->Accept(this);
        os << ")";
        return os.str();
    }

};
