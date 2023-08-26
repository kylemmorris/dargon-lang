/*
 * Dargon Programming Language
 * (C) Kyle Morris 2023 - See LICENSE.txt for license information.
 *
 * FILE: Token.cpp
 *
 * DESCRIPTION: Implementation of Token.h
 *
 * SINCE: v0.1
 *
 */

#include "../include/Token.h"

namespace dargon {

    Token::Token() : type(TokenType::INVALID), value("INVALID") {}
    Token::Token(const TokenType& type, const std::string& val) : type(type), value(val) {}

    bool Token::IsValid() const {
        return type != TokenType::INVALID && type != TokenType::EOF_TYPE;
    }

    std::string Token::ToString() const {
        return "<" + TypeName(type) + " : " + value + ">";
    }

    TokenType IsKeyword(const std::string& input) {
        TokenType ret = TokenType::INVALID;
        auto t = Keywords.find(input);
        if(t != Keywords.cend()) {
            ret = t->second;
        }
        return ret;
    }
};
