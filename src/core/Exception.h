/**
 * Dargon Programming Language
 * (C) Kyle Morris 2023 - See LICENSE.txt for license information.
 *
 * @file Exception.h
 * @author Kyle Morris
 * @since v0.1
 * @section Description
 * Dargon-specific exceptions live here.
 *
 */

#ifndef DARGON_HEADER_EXCEPTION
#define DARGON_HEADER_EXCEPTION

#include <stdexcept>
#include <string>

namespace dargon {

    /// @brief Dargon-specific exception.
    class Exception : public std::exception {
    public:
        Exception(const std::string& msg) : _msg(msg) {}
        virtual const char* what() const noexcept override;
    private:
        const std::string _msg;
    };

    /// @brief Exception thrown during lexical analysis.
    class LexerException : public Exception {
        using Exception::Exception;
    };

    /// @brief Exception thrown during parsing.
    class ParsingException : public Exception {
        using Exception::Exception;
    }

};

#endif
