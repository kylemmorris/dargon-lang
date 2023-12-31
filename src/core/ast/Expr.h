/*
 * Dargon Programming Language
 * (C) Kyle Morris 2023 - See LICENSE.txt for license information
 *
 * FILE: Expr.h
 *
 * DESCRIPTION: This file is automatically generated by "tools/GenDargonStmtExpr.py". It includes all the expression classes.
 *
 * SINCE: v0.1
 *
 */
#ifndef DARGON_EXPR_H
#define DARGON_EXPR_H
#include <string>
#include "../lex/Token.h"

namespace dargon {

	//Forward declarations:

	class BinaryExpr;
	class GroupingExpr;
	class LiteralExpr;
	class UnaryExpr;
	class IVisitor;

	/**
	 * @brief Interface for a node being
	 * visited by an object that implements
	 * the "IVisitor" interface.
	 * @author Kyle Morris
	 * @since v0.1
	 * @see IVisitor
	 */
	class IVisitee {
	public:
        /**
        * @brief Abstract function. Accepts a visitor
        * object and calls its appropriate "Visit" function
        * using this object.
        */
        virtual void Accept(IVisitor& visitor) = 0;
	};

	/**
	 * @brief Interface for an object that
	 * visits nodes in a tree.
	 * @author Kyle Morris
	 * @since v0.1
	 * @see IVisitee
	 */
	class IVisitor {
	public:
		virtual void VisitBinaryExpr(BinaryExpr& binary) = 0;
		virtual void VisitGroupingExpr(GroupingExpr& grouping) = 0;
		virtual void VisitLiteralExpr(LiteralExpr& literal) = 0;
		virtual void VisitUnaryExpr(UnaryExpr& unary) = 0;
	};

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
		virtual void Accept(IVisitor& visitor) override {
			visitor.VisitBinaryExpr(*this);
		}
	};
	class GroupingExpr : public Expr {
	public:
		Expr* expression;
		GroupingExpr(Expr* expression)
		: expression(expression) {}
		virtual void Accept(IVisitor& visitor) override {
			visitor.VisitGroupingExpr(*this);
		}
	};
	class LiteralExpr : public Expr {
	public:
		std::string value;
		LiteralExpr(std::string value)
		: value(value) {}
		virtual void Accept(IVisitor& visitor) override {
			visitor.VisitLiteralExpr(*this);
		}
	};
	class UnaryExpr : public Expr {
	public:
		Token op;
		Expr* right;
		UnaryExpr(Token op, Expr* right)
		: op(op), right(right) {}
		virtual void Accept(IVisitor& visitor) override {
			visitor.VisitUnaryExpr(*this);
		}
	};
};
#endif
