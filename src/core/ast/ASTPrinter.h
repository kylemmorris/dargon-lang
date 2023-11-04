/*
 * Dargon Programming Language
 * (C) Kyle Morris 2023 - See LICENSE.txt for license information.
 *
 * FILE: ASTPrinter.h
 *
 * DESCRIPTION: A simple pretty printer visitor for the Abstract Syntax Tree (AST).
 *
 * SINCE: v0.1
 *
 */

#ifndef DARGON_ASTPRINTER_H
#define DARGON_ASTPRINTER_H

#include <iostream>
#include <initializer_list>
#include <sstream>
#include "Expr.h"

namespace dargon {

	/**
     * @brief Simple pretty printer visitor for the AST. Prints
     * to std::cout.
     * @author Kyle Morris
     * @since v0.1
    */
	class ASTPrinter : public IVisitor {
	public:
        ASTPrinter();
        /**
        * @brief Returns the expression
        * in polish notation.
        */
        std::string Print(Expr* exp);
        virtual void VisitBinaryExpr(BinaryExpr& binary) override;
		virtual void VisitGroupingExpr(GroupingExpr& grouping) override;
		virtual void VisitLiteralExpr(LiteralExpr& literal) override;
		virtual void VisitUnaryExpr(UnaryExpr& unary) override;
	private:
        /**
        * @brief The result of the print.
        */
        std::ostringstream _result;

        /**
        * @brief Helper function, equivalent to: std::cout << "(" << name << foreach(expr) { exprs->Accept(this); } << ")";
        */
        void _parenthesize(const std::string& name, std::initializer_list<Expr*> exprs);
	};

};

#endif
