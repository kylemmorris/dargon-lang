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

#include "Expr.h"

namespace dargon {

	/**
     * @brief Simple pretty printer visitor for the AST.
     * @author Kyle Morris
     * @since v0.1
    */
	class ASTPrinter : public IVisitor {
	public:
        std::string Print(Expr* expr);
        virtual std::string VisitBinaryExpr(BinaryExpr* binary) override;
		virtual std::string VisitGroupingExpr(GroupingExpr* grouping) override;
		virtual std::string  VisitLiteralExpr(LiteralExpr* literal) override;
		virtual std::string  VisitUnaryExpr(UnaryExpr* unary) override;
	private:
        std::string _parenthesize(const std::string& name, Expr* expr);
	};

};

#endif
