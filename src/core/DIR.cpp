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

    void DIR::_run() {
        std::ostringstream os;

        // Phase I: Lexical analysis
        _lex.Buffer(&_file);
        // Try and get all of the tokens. If there is an
        // invalid token, we probably should not continue.
        Error e = _lex.Work();
        if(e.IsError()) {
            // Build error
            os << e.ToString() << std::endl;
            _file.Goto(e.where);
            os << _file.ShowExactPosition() << std::endl;
            //out(os.str());
            DARGON_LOG_ERROR(os.str());
            return;
        }
        // Else, we're okay
        //out("OK");
    }

}
