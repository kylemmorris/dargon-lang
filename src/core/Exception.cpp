/*
 * Dargon Programming Language
 * (C) Kyle Morris 2023 - See LICENSE.txt for license information.
 *
 * FILE: Exception.cpp
 *
 * DESCRIPTION: Implementation of Exception.h
 *
 * SINCE: v0.1
 *
 */

 #include <sstream>
#include "Exception.h"
#include "io/Log.h"

namespace dargon {

    Exception::Exception(const ErrorCode& code, const std::string& msg)
        : _code(code), _msg(msg), _where()
    {}

    Exception::Exception(const ErrorCode& code, const std::string& msg, const FilePosition& where)
        : _code(code), _msg(msg), _where(where)
    {}

    const char* Exception::what() const noexcept {
        return BuildFullMessage().c_str();
    }

    std::string Exception::BuildFullMessage() const {
        std::ostringstream os;
        os << "(DIR" << (int)_code << ") ";
        if(_where.Valid()) {
            os << _where.ToString();
        }
        os << " : " << _msg;
        //DARGON_LOG_ERROR(os.str());
        return os.str();
    }

    ErrorCode Exception::GetCode() const { return _code; }

    std::string Exception::GetMessage() const { return _msg; }

    FilePosition Exception::GetPosition() const { return _where; }

};

