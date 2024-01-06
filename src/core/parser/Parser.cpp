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

    Parser::Parser() {}

    Parser::~Parser() {}

    void Parser::Buffer(const TokenList& tokens) {
        _tokens = tokens;
        _current = _tokens.begin();
    }

    Expr* Parser::Parse() {
        return expression();
    }

    /// ---- GENERAL PURPOSE FUNCTIONS ----

    bool Parser::match(std::initializer_list<Token::Kind> kinds) {
        for(Token::Kind t : kinds) {
            if(check(t)) { next(); return true; }
        }
        return false;
    }

    bool Parser::check(const Token::Kind& kind) {
        if(atEnd()) { return false; }
        return peek().GetKind() == kind;
    }

    Token Parser::next() {
        if(!atEnd()) { _current++; }
        return prev();
    }

    bool Parser::atEnd() const {
        return _current == _tokens.end();
    }

    Token Parser::peek() const {
        return *_current;
    }

    Token Parser::prev() const {
        return *(_current - 1);
    }

    Token Parser::consume(const Token::Kind& type, const std::string& msg) {
        if(check(type)) {
            return next();
        }
        throw new ParsingException(ErrorCode::EXPECTED_EXPRESSION, msg + ": " + peek().ToString());
    }

    void Parser::synchronize() {
        // This method satisfied the following logic:
        // We discard tokens until we're at the beginning of
        // the next statement. After a newline (we don't have semicolons),
        // the statement is finished. Most statements start with keywords.
        // Therefore, when the next token is one of those, we are probably
        // starting a new statement.
        next();
        while(!atEnd()) {
            // TODO: Figure out how to make this more sophisticated
            if(prev().GetKind() == Token::Kind::NEWLINE) {
                return;
            }
            // If we are starting a new statement
            switch(peek().GetKind()) {
                case Token::Kind::CONST_MUT:
                case Token::Kind::VAR_MUT:
                case Token::Kind::FUN_DECL:
                case Token::Kind::TYPE_DECL:
                case Token::Kind::IF:
                case Token::Kind::ELIF:
                case Token::Kind::ELSE:
                case Token::Kind::LOOP:
                case Token::Kind::WHEN:
                    return;
                default:
                    break;
            }
            next();
        }
    }

    /// ---- GRAMMAR RULES ----

    /// expression = equality
    Expr* Parser::expression() {
        return equality();
    }

    /// equality = comparison ( ("!="|"==") comparison )* ;
    Expr* Parser::equality() {
        Expr* comp = comparison();
        while(match({Token::Kind::EQUALITY, Token::Kind::NEQUALITY})) {
            Token op = prev();
            Expr* right = comparison();
            comp = new BinaryExpr(comp, op, right);
        }
        return comp;
    }

    /// comparison = term ( (">" | ">=" | "<" | "<=" ) term)* ;
    Expr* Parser::comparison() {
        Expr* expr = term();
        while(match({Token::Kind::LT, Token::Kind::GT, Token::Kind::LTE, Token::Kind::GTE})) {
            Token op = prev();
            Expr* right = term();
            expr = new BinaryExpr(expr, op, right);
        }
        return expr;
    }

    /// term = factor ( ("-" | "+") factor)* ;
    Expr* Parser::term() {
        Expr* fac = factor();
        while(match({Token::Kind::MINUS, Token::Kind::PLUS})) {
            Token op = prev();
            Expr* right = factor();
            fac = new BinaryExpr(fac, op, right);
        }
        return fac;
    }

    /// factor = unary ( ("/" | "*") unary)* ;
    Expr* Parser::factor() {
        Expr* fac = unary();
        while(match({Token::Kind::SLASH, Token::Kind::STAR})) {
            Token op = prev();
            Expr* right = unary();
            fac = new BinaryExpr(fac, op, right);
        }
        return fac;
    }

    /// unary = ("!" | "-") unary | primary ;
    Expr* Parser::unary() {
        if(match({Token::Kind::BANG, Token::Kind::MINUS})) {
            Token op = prev();
            Expr* right = unary();
            return new UnaryExpr(op, right);
        }
        return primary();
    }

    /// primary = NUMBER | STRING | "true" | "false" | "(" expression ")" ;
    Expr* Parser::primary() {
        // We just use switch instead of if(_match() {} if(_match()) {} ...
        Expr* exp = nullptr;
        const Token t = peek();
        switch(t.GetKind()) {
            case Token::Kind::BOOL_F_LIT:
            case Token::Kind::BOOL_T_LIT:
            case Token::Kind::NUMBER_LIT:
            case Token::Kind::STRING_LIT:
                next();
                return new LiteralExpr(t.GetValue());
            case Token::Kind::PAREN_OPEN:
                next();
                exp = expression();
                consume(Token::Kind::PAREN_CLOSE, "Expected ')' after expression");
                return new GroupingExpr(exp);
            default:
                throw new ParsingException(ErrorCode::EXPECTED_EXPRESSION, "Expected expression, found: " + t.ToString(), t.GetPosition());
                //throw error(peek(), "Expected expression");
        };
    }

};
