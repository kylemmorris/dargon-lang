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

#include "DIR.h"
#include "IO.h"
#include "Log.h"

namespace dargon {

    void DIR::Run(const Path& filePath) {
        _clearErrors();
        if(!File::Exists(filePath)) {
            DARGON_LOG_ERROR("File not found: " + filePath.GetFull());
            return;
        }
        // The following will depend on file
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

    void DIR::Run(const std::string& contents) {
        _clearErrors();
        _file.BufferRawData(contents);
        _run();
    }

    void DIR::_clearErrors() {
        while(!_errors.empty()) { _errors.pop(); }
    }

    void DIR::_run() {
        // Phase I: Lexical analysis
        _lex.Buffer(&_file);
        // Try and get all of the tokens. If there is an invalid token, we probably
        // should not continue.
        try {
            TokenList tokens = _lex.GetAllTokens();
        }
        catch(LexerException* e) {
            out(e->what());
            delete e;
        }

        out("OK");
    }

}
