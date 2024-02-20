/**
 * Dargon Programming Language
 * (C) Kyle Morris 2023 - See LICENSE.txt for license information.
 *
 * @file DIR.cpp
 * @author Kyle Morris
 * @since v0.1
 * @section Description
 * Implementation of DIR.h
 *
 */

#include <sstream>
#include "DIR.h"
#include "IO.h"
#include "Log.h"
#include "ast/ASTPrinter.h"

namespace dargon {

    void DIR::Run(Path& filePath) {
        if(!File::Exists(filePath)) {
            DARGON_LOG_ERROR("File not found: " + filePath.GetFull());
            return;
        }
        // The following will depend on file
        if(!_file.OpenAbsolute(filePath)) {
            DARGON_LOG_ERROR("Could not open file: " + filePath.GetFull());
            return;
        }
        switch(filePath.GetFileExtension()) {
            case Path::Extension::DARGON:
                _run();
                break;
            case Path::Extension::DARGON_CONFIG:
                DARGON_LOG_ERROR("Not currently implemented!");
                break;
            default:
                DARGON_LOG_ERROR("Unsupported file type: " + filePath.GetFileName());
                break;
        };
    }

    void DIR::Run(std::string& contents) {
        _file.BufferRawData(contents);
        _run();
    }

    void DIR::_buildError(const Exception* err) {
        std::ostringstream os;
        // Build error
        os << err->BuildFullMessage() << std::endl << std::endl;
        if(_file.Goto(err->GetPosition())) {
            os << _file.ShowExactPosition() << std::endl;
        }
        //out(os.str());
        DARGON_LOG_ERROR(os.str());
    }

    void DIR::_run() {
        // Phase I: Lexical analysis
        _lex.Buffer(&_file);
        TokenList tokens;
        try {
            tokens = _lex.GetAllTokens();
        }
        catch(LexerException* e) {
            _buildError(e);
            delete e;
            return;
        }
        // Edge-case - if the only token is EOF, don't continue
        if(tokens.size() == 1 && tokens.at(0).IsEOF()) {
            return;
        }
        // Phase II: Parser
        _parse.Buffer(tokens);
        try {
            ASTPrinter printer;
            Expr* output = _parse.Parse();
            DARGON_LOG_DEBUG(printer.Print(output));
            delete output;
        }
        catch(ParsingException* e) {
            _buildError(e);
            delete e;
        }
    }

    ValueBase& DIR::_evaluate(Expr* expression) {
        return expression->Accept(*this);
    }

    ValueBase& DIR::_isEqual(const ValueBase& left, const ValueBase& right) {
        // Guarenteed to be same type
        Boolean b;
        switch(left.GetType()) {
            case ValueBase::Type::INT:
                b.Set(static_cast<const Int*>(&left)->Get() ==  static_cast<const Int*>(&right)->Get());
                break;
            case ValueBase::Type::REAL:
                b.Set(static_cast<const Real*>(&left)->Get() ==  static_cast<const Real*>(&right)->Get());
                break;
            case ValueBase::Type::STRING:
                b.Set(static_cast<const String*>(&left)->Get() ==  static_cast<const String*>(&right)->Get());
                break;
            case ValueBase::Type::BOOL:
                b.Set(static_cast<const Boolean*>(&left)->Get() ==  static_cast<const Boolean*>(&right)->Get());
                break;
            default:
                DARGON_LOG_DEBUG("_isEqual - a type was not handled.");
                break;
        }
        return b;
    }

    ValueBase& DIR::VisitLiteralExpr(LiteralExpr& literal) {
        return literal.value;
    }

    ValueBase& DIR::VisitBinaryExpr(BinaryExpr& binary) {
        ValueBase left = _evaluate(binary.left);
        ValueBase right = _evaluate(binary.right);

        bool lint = left.GetType() == ValueBase::Type::INT;
        bool rint = right.GetType() == ValueBase::Type::INT;

        bool lreal = left.GetType() == ValueBase::Type::REAL;
        bool rreal = right.GetType() == ValueBase::Type::REAL;

        bool lstr = left.GetType() == ValueBase::Type::STRING;
        bool rstr = right.GetType() == ValueBase::Type::STRING;

        bool lbol = left.GetType() == ValueBase::Type::BOOL;
        bool rbol = right.GetType() == ValueBase::Type::BOOL;

        bool same = (lint && rint) || (lreal && rreal) || (lstr && rstr) || (lbol && rbol);

        switch(binary.op.GetKind()) {
            case Token::Kind::PLUS: {
                if(lint && rint) {
                    Int res;
                    res.Set(static_cast<Int*>(&left)->Get() + static_cast<Int*>(&right)->Get());
                    return res;
                }
                else if(lreal && rreal) {
                    Real res;
                    res.Set(static_cast<Real*>(&left)->Get() + static_cast<Real*>(&right)->Get());
                    return res;
                }
                else if(lstr && rstr) {
                    String res;
                    res.Set(static_cast<String*>(&left)->Get() + static_cast<String*>(&right)->Get());
                    return res;
                }
                break;
            }
            case Token::Kind::MINUS: {
                if(lint && rint) {
                    Int res;
                    res.Set(static_cast<Int*>(&left)->Get() - static_cast<Int*>(&right)->Get());
                    return res;
                }
                else if(lreal && rreal) {
                    Real res;
                    res.Set(static_cast<Real*>(&left)->Get() - static_cast<Real*>(&right)->Get());
                    return res;
                }
                break;
            }
            case Token::Kind::STAR: {
                if(lint && rint) {
                    Int res;
                    res.Set(static_cast<Int*>(&left)->Get() * static_cast<Int*>(&right)->Get());
                    return res;
                }
                else if(lreal && rreal) {
                    Real res;
                    res.Set(static_cast<Real*>(&left)->Get() * static_cast<Real*>(&right)->Get());
                    return res;
                }
                break;
            }
            case Token::Kind::SLASH: {
                if(lint && rint) {
                    Int res;
                    res.Set(static_cast<Int*>(&left)->Get() / static_cast<Int*>(&right)->Get());
                    return res;
                }
                else if(lreal && rreal) {
                    Real res;
                    res.Set(static_cast<Real*>(&left)->Get() / static_cast<Real*>(&right)->Get());
                    return res;
                }
                break;
            }
            case Token::Kind::GT: {
                if(lint && rint) {
                    Boolean res;
                    res.Set(static_cast<Int*>(&left)->Get() > static_cast<Int*>(&right)->Get());
                    return res;
                }
                else if(lreal && rreal) {
                    Boolean res;
                    res.Set(static_cast<Real*>(&left)->Get() > static_cast<Real*>(&right)->Get());
                    return res;
                }
                break;
            }
            case Token::Kind::GTE: {
                if(lint && rint) {
                    Boolean res;
                    res.Set(static_cast<Int*>(&left)->Get() >= static_cast<Int*>(&right)->Get());
                    return res;
                }
                else if(lreal && rreal) {
                    Boolean res;
                    res.Set(static_cast<Real*>(&left)->Get() >= static_cast<Real*>(&right)->Get());
                    return res;
                }
                break;
            }
            case Token::Kind::LT: {
                if(lint && rint) {
                    Boolean res;
                    res.Set(static_cast<Int*>(&left)->Get() < static_cast<Int*>(&right)->Get());
                    return res;
                }
                else if(lreal && rreal) {
                    Boolean res;
                    res.Set(static_cast<Real*>(&left)->Get() < static_cast<Real*>(&right)->Get());
                    return res;
                }
                break;
            }
            case Token::Kind::LTE: {
                if(lint && rint) {
                    Boolean res;
                    res.Set(static_cast<Int*>(&left)->Get() <= static_cast<Int*>(&right)->Get());
                    return res;
                }
                else if(lreal && rreal) {
                    Boolean res;
                    res.Set(static_cast<Real*>(&left)->Get() <= static_cast<Real*>(&right)->Get());
                    return res;
                }
                break;
            }
            case Token::Kind::EQUALITY: {
                if(same) {
                    ValueBase b = _isEqual(left, right);
                    return b;
                }
                break;
            }
            case Token::Kind::NEQUALITY: {
                if(same) {
                    ValueBase b = _isEqual(left, right);
                    Boolean* bptr = static_cast<Boolean*>(&b);
                    bptr->Set(!bptr->Get());
                    return b;
                }
                break;
            }
        };
        return NONE_VALUE;
    }

    ValueBase& DIR::VisitGroupingExpr(GroupingExpr& grouping) {
        return _evaluate(grouping.expression);
    }

    ValueBase& DIR::VisitUnaryExpr(UnaryExpr& unary) {
        ValueBase right = _evaluate(unary.right);
        Int* i;
        Real* r;
        Boolean* b;
        switch(unary.op.GetKind()) {
            case Token::Kind::MINUS:
                // Negative operator
                switch(right.GetType()) {
                    case ValueBase::Type::INT:
                        i = static_cast<Int*>(&right);
                        i->Set(-i->Get());
                        return right;
                    case ValueBase::Type::REAL:
                        r = static_cast<Real*>(&right);
                        r->Set(-r->Get());
                        return right;
                };
                break;
            case Token::Kind::BANG:
                // Logical negation - only works on booleans
                if(right.GetType() == ValueBase::Type::BOOL) {
                    b = static_cast<Boolean*>(&right);
                    b->Set(!b->Get());
                    return right;
                }
            default:
                break;
        };
        return NONE_VALUE;
    }
}
