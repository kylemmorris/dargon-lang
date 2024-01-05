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
        }
        catch(LexerException* e) {
            _buildError(e);
            delete e;
        }
        // Phase II: Parser
        _parse.Buffer(_lex.GetAllTokens());
        try {
            ASTPrinter printer;
            Expr* output = _parse.Parse();
            out(printer.Print(output));
            delete output;
        }
        catch(ParsingException* e) {
            _buildError(e);
            delete e;
        }
    }

}
