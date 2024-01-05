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
#include "FilePosition.h"

namespace dargon {

    /// @brief The error codes used throughout the program.
	/// @author Kyle Morris
	/// @since v0.1
    enum class ErrorCode : int32_t {
        NO_ERROR = 0x0,
        INTERNAL_ERROR = 0xD00,
        INVALID_TOKEN = 0xD01,
        EXPECTED_EXPRESSION = 0xD02
    };

    /// @brief Dargon-specific exception.
    /// @author Kyle Morris
    /// @since v0.1
    class Exception : public std::exception {
    public:
        Exception(const ErrorCode& code, const std::string& msg);
        Exception(const ErrorCode& code, const std::string& msg, const FilePosition& where);
        virtual const char* what() const noexcept override;
        ErrorCode GetCode() const;
        std::string GetMessage() const;
        FilePosition GetPosition() const;
        std::string BuildFullMessage() const;
    protected:
        const ErrorCode _code;
        const std::string _msg;
        const FilePosition _where;
    };

    /// @brief Exception thrown during lexical analysis.
    /// @author Kyle Morris
    /// @since v0.1
    class LexerException : public Exception {
        using Exception::Exception;
    };

    /// @brief Exception thrown during parsing.
    /// @author Kyle Morris
    /// @since v0.1
    class ParsingException : public Exception {
        using Exception::Exception;
    };

};

#endif
