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

    ASTPrinter::ASTPrinter() : _result() {}

    std::string ASTPrinter::Print(Expr* exp) {
        _result.str("");
        exp->Accept(*this);
        return _result.str();
    }

    Register& ASTPrinter::VisitBinaryExpr(BinaryExpr& binary) {
        _parenthesize(binary.op.GetValue(), { binary.left, binary.right });
        return DARGON_EMPTY_REG;
    }

    Register& ASTPrinter::VisitGroupingExpr(GroupingExpr& grouping) {
        _parenthesize("group ", { grouping.expression });
        return DARGON_EMPTY_REG;
    }

    Register& ASTPrinter::VisitLiteralExpr(LiteralExpr& literal) {
        if(literal.value.size() == 0) {
            _result << "nil";
        }
        else {
            _result << " " << literal.value;
        }
        return DARGON_EMPTY_REG;
    }

    Register& ASTPrinter::VisitUnaryExpr(UnaryExpr& unary) {
        _parenthesize(unary.op.GetValue(), { unary.right });
        return DARGON_EMPTY_REG;
    }

    void ASTPrinter::_parenthesize(const std::string& name, std::initializer_list<Expr*> exprs) {
        _result << "(" << name;
        for(Expr* e : exprs) {
            e->Accept(*this);
        }
        _result << ")";
    }

};
