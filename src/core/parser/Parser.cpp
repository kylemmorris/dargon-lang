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
        _current = _tokens.begin();
    }

    /// ---- GENERAL PURPOSE FUNCTIONS ----

    bool Parser::_match(std::initializer_list<Token::Kind> kinds) {
        for(Token::Kind t : kinds) {
            if(_check(t)) { _next(); return true; }
        }
        return false;
    }

    bool Parser::_check(const Token::Kind& kind) {
        if(_end()) { return false; }
        return _peek().GetKind() == kind;
    }

    Token Parser::_next() {
        if(!_end()) { _current++; }
        return _prev();
    }

    bool Parser::_end() const {
        return _current == _tokens.end();
    }

    Token Parser::_peek() const {
        return *_current;
    }

    Token Parser::_prev() const {
        return *(_current - 1);
    }

    /// ---- GRAMMAR RULES ----

    /// expression -> equality
    Expr* Parser::_expression() {
        return _equality();
    }

    /// equality -> comparison ( ("!="|"==") comparison )* ;
    Expr* Parser::_equality() {
        Expr* exp = _comparison();

    }

    Expr* Parser::_comparison() {

    }

};
