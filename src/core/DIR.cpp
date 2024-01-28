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
        _file.Goto(err->GetPosition());
        os << _file.ShowExactPosition() << std::endl;
        //out(os.str());
        DARGON_LOG_ERROR(os.str());
    }

    void DIR::_run() {
        // Phase I: Lexical analysis
        _lex.Buffer(&_file);
        TokenList tokens;
        try {
            tokens = _lex.GetAllTokens();
            #ifdef DARGON_VERSION_DEBUG
            for(Token token : tokens) {
                DARGON_LOG_DEBUG(token.ToString());
            }
            #endif // DARGON_VERSION_DEBUG
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

    Register& DIR::_evaluate(Expr* expression) {
        return expression->Accept(*this);
    }

    Register& DIR::VisitLiteralExpr(LiteralExpr& literal) {
        return DARGON_EMPTY_REG;
    }

    Register& DIR::VisitBinaryExpr(BinaryExpr& binary) {
        return DARGON_EMPTY_REG;
    }

    Register& DIR::VisitGroupingExpr(GroupingExpr& grouping) {
        return _evaluate(grouping.expression);
    }

    Register& DIR::VisitUnaryExpr(UnaryExpr& unary) {
        return DARGON_EMPTY_REG;
        #if 0
        Register right = _evaluate(unary.right);
        switch(unary.op.GetKind()) {
            Token::Kind::MINUS:
                double d = std::stod(right->VALUE);
                return -d;
        };
        return nullptr;
        #endif
    }
}
