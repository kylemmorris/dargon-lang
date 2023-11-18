/**
 * Dargon Programming Language
 * (C) Kyle Morris 2023 - See LICENSE.txt for license information.
 *
 * @file Parser.cpp
 * @author Kyle Morris
 * @since v0.1
 * @section Description
 * Implementation of Parser.
 *
 */

#include "Parser.h"

namespace dargon {

    Parser::Parser(const TokenList& tokens)
    : _tokens(tokens)
    {
        _current = _tokens.cbegin();
    }

    bool _match(std::initializer_list<Token::Kind> _tKinds) {

    }

    Expr* Parser::_expression() {
        return _equality();
    }

    Expr* Parser::_equality() {
        Expr* exp = _comparison();

    }

    Expr* Parser::_comparison() {

    }

};
