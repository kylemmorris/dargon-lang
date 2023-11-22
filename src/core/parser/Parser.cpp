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

    Token Parser::_consume(const Token::Kind& type, const std::string& msg) {
        if(_check(type)) {
            return _next();
        }

    }

    ParsingException Parser::error(const Token& token, const std::string& msg) {
        ReportError(token, msg);
        return ParsingException(msg);
    }

    /// ---- GRAMMAR RULES ----

    /// expression = equality
    Expr* Parser::_expression() {
        return _equality();
    }

    /// equality = comparison ( ("!="|"==") comparison )* ;
    Expr* Parser::_equality() {
        Expr* comp = _comparison();
        while(_match({Token::Kind::EQUALITY, Token::Kind::NEQUALITY})) {
            Token op = _prev();
            Expr* right = _comparison();
            comp = new BinaryExpr(comp, op, right);
        }
        return comp;
    }

    /// comparison = term ( (">" | ">=" | "<" | "<=" ) term)* ;
    Expr* Parser::_comparison() {
        Expr* term = _term();
        while(_match({Token::Kind::LT, Token::Kind::GT, Token::Kind::LTE, Token::Kind::GTE})) {
            Token op = _prev();
            Expr* right = _term();
            term = new BinaryExpr(term, op, right);
        }
        return term;
    }

    /// term = factor ( ("-" | "+") factor)* ;
    Expr* Parser::_term() {
        Expr* fac = _factor();
        while(_match({Token::Kind::MINUS, Token::Kind::PLUS})) {
            Token op = _prev();
            Expr* right = _factor();
            fac = new BinaryExpr(fac, op, right);
        }
        return fac;
    }

    /// factor = unary ( ("/" | "*") unary)* ;
    Expr* Parser::_factor() {
        Expr* fac = _unary();
        while(_match({Token::Kind::SLASH, Token::Kind::STAR})) {
            Token op = _prev();
            Expr* right = _unary();
            fac = new BinaryExpr(fac, op, right);
        }
        return fac;
    }

    /// unary = ("not" | "-") unary | primary ;
    Expr* Parser::_unary() {
        if(_match({Token::Kind::NOT, Token::Kind::MINUS})) {
            Token op = _prev();
            Expr* right = _unary();
            return new UnaryExpr(op, right);
        }
        return _primary();
    }

    /// primary = NUMBER | STRING | "true" | "false" | "(" expression ")" ;
    Expr* Parser::_primary() {
        // We just use switch instead of if(_match() {} if(_match()) {} ...
        const Token t = _peek();
        switch(t.GetKind()) {
            case Token::Kind::BOOL_F_LIT:
            case Token::Kind::BOOL_T_LIT:
            case Token::Kind::NUMBER_LIT:
            case Token::Kind::STRING_LIT:
                _next();
                return new LiteralExpr(t.GetValue());
            case Token::Kind::PAREN_OPEN:
                _next();
                Expr* exp = _expression();
                _consume(Token::Kind::PAREN_CLOSE, "Expected ')' after expression");
                return new GroupingExpr(exp);
            default:
                return nullptr;
        }
    }

};
