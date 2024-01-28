 /**
 * Dargon Programming Language
 * (C) Kyle Morris 2023 - See LICENSE.txt for license information.
 *
 * @file
 * @author Kyle Morris
 * @since v0.1
 * @section Description
 *
 *
 */

#ifndef DARGON_HEADER_VISITOR
#define DARGON_HEADER_VISITOR

#include "../runtime/Register.h"

namespace dargon {

    //Forward declaration:
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
        virtual Register& Accept(IVisitor& visitor) = 0;
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
		virtual Register& VisitBinaryExpr(BinaryExpr& binary) = 0;
		virtual Register& VisitGroupingExpr(GroupingExpr& grouping) = 0;
		virtual Register& VisitLiteralExpr(LiteralExpr& literal) = 0;
		virtual Register& VisitUnaryExpr(UnaryExpr& unary) = 0;
	};

};

#endif
