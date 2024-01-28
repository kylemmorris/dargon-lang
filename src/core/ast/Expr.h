/*
 * Dargon Programming Language
 * (C) Kyle Morris 2023 - See LICENSE.txt for license information
 *
 * FILE: Expr.h
 *
 * DESCRIPTION: Includes all the expression classes.
 *
 * SINCE: v0.1
 *
 */
#ifndef DARGON_HEADER_EXPR
#define DARGON_HEADER_EXPR
#include <string>
#include "../lex/Token.h"
#include "Visitor.h"

namespace dargon {

	/**
	 * @brief The base class of all Expressions.
	 *
	*/
	class Expr : public IVisitee {
	public:
        using IVisitee::Accept;
        virtual ~Expr() {}
	};

	// ************************

	class BinaryExpr : public Expr {
	public:
		Expr* left;
		Token op;
		Expr* right;
		BinaryExpr(Expr* left, Token op, Expr* right)
		: left(left), op(op), right(right) {}
		virtual Register& Accept(IVisitor& visitor) override {
			return visitor.VisitBinaryExpr(*this);
		}
	};
	class GroupingExpr : public Expr {
	public:
		Expr* expression;
		GroupingExpr(Expr* expression)
		: expression(expression) {}
		virtual Register& Accept(IVisitor& visitor) override {
			return visitor.VisitGroupingExpr(*this);
		}
	};
	class LiteralExpr : public Expr {
	public:
		std::string value;
		LiteralExpr(std::string value)
		: value(value) {}
		virtual Register& Accept(IVisitor& visitor) override {
			return visitor.VisitLiteralExpr(*this);
		}
	};
	class UnaryExpr : public Expr {
	public:
		Token op;
		Expr* right;
		UnaryExpr(Token op, Expr* right)
		: op(op), right(right) {}
		virtual Register& Accept(IVisitor& visitor) override {
			return visitor.VisitUnaryExpr(*this);
		}
	};
};
#endif
