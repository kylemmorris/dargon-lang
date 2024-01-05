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
        _clearErrors();
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
        _clearErrors();
        _file.BufferRawData(contents);
        _run();
    }

    void DIR::_clearErrors() {
        while(!_errors.empty()) { _errors.pop(); }
    }

    void DIR::_buildError(const Error& err) {
        std::ostringstream os;
        // Build error
        os << err.ToString() << std::endl;
        _file.Goto(err.where);
        os << _file.ShowExactPosition() << std::endl;
        //out(os.str());
        DARGON_LOG_ERROR(os.str());
    }

    void DIR::_run() {
        // Phase I: Lexical analysis
        _lex.Buffer(&_file);
        // Try and get all of the tokens. If there is an
        // invalid token, we probably should not continue.
        Error e = _lex.Work();
        if(e.IsError()) {
            _buildError(e);
            return;
        }
        // Phase II: Parser
        _parse.Buffer(_lex.GetAllTokens());
        e = _parse.Work();
        if(e.IsError()) {
            _buildError(e);
            return;
        }
        ASTPrinter printer;
        out(printer.Print(_parse.GetOutput()));
    }

}
