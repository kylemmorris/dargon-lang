/**
 * Dargon Programming Language
 * (C) Kyle Morris 2023 - See LICENSE.txt for license information.
 *
 * @file Token.cpp
 * @author Kyle Morris
 * @since v0.1
 * @section Description
 * A 'token' is what the source program is converted into by the lexer, and
 * it can represent any number of characters in a sequence (identifiers, keywords, etc.).
 *
 */

 #include <sstream>
 #include "Token.h"

 namespace dargon {

    Token::Token()
    : _type(Kind::INVALID), _value(""), _location()
    {}

    Token::Token(const Token::Kind& kind, const FilePosition& pos)
    : _type(kind), _value(""), _location(pos)
    {}

    Token::Token(const Token::Kind& kind, const std::string& value, const FilePosition& pos)
    : _type(kind), _value(value), _location(pos)
    {
        // If it's an ID, check if it's not a keyword.
        if(_type == Kind::ID) {
            auto ret = Keywords.find(_value);
            if(ret != Keywords.cend()) {
                _type = ret->second;
            }
        }
    }

    bool Token::IsValid() const
    {
        return _type != Kind::END_OF_FILE && _type != Kind::INVALID;
    }

    std::string Token::ToString() const
    {
        // Returns [TYPE], [TYPE,value], or [TYPE,value @Line X Col Y]
        std::ostringstream os;
        os << "[" << GetKindName(_type);
        if(_type > Kind::__LITERALS__ || _type == Kind::ID) {
            os << ", " << _value;
        }
        if(_location.Valid()) {
            os << " " << _location.ToString();
        }
        os << "]";
        return os.str();
    }

    std::string Token::GetKindName(const Token::Kind& type)
    {
        switch(type) {
        case Kind::END_OF_FILE: return "EOF";
        case Kind::INVALID: return "(!?)";
        case Kind::NEWLINE: return "NEWLINE";
        case Kind::ID: return "ID";
        case Kind::COLON: return "COLON";
        case Kind::CONST_MUT: return "const";
        case Kind::VAR_MUT: return "var";
        case Kind::ASSIGNMENT: return "ASSIGN";
        case Kind::NUMBER_LIT: return "NUMBER LITERAL";
        case Kind::FRACTIONAL_LIT: return "FRACTIONAL LITERAL";
        case Kind::BOOL_T_LIT: return "true";
        case Kind::BOOL_F_LIT: return "false";
        case Kind::STRING_LIT: return "STRING LITERAL";
        default:
            std::string err = "Unhandled Kind in Token::GetKindName(): ";
            err += std::to_string((int)type);
            throw new Exception(err);
        }
    }

 };
