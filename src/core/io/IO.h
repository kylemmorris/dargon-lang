/**
 * Dargon Programming Language
 * (C) Kyle Morris 2023 - See LICENSE.txt for license information.
 *
 * @file Output.h
 * @author Kyle Morris
 * @since v0.1
 * @section Description
 * Contains functions related to outputting.
 *
 */

#ifndef DARGON_HEADER_OUTPUT
#define DARGON_HEADER_OUTPUT

#include <iostream>
#include <string>
#include <stdarg.h>
//#include "Log.h"

namespace dargon {

    /// @brief The input stream used.
    #define DARGON_IN std::cin

    /// @brief The output stream used.
    #define DARGON_OUT std::cerr

    #define DARGON_OUTF stderr

    /// @brief Prints to DARGON_OUTF and includes formatting.
    inline void out(bool include_endl, const char* msg, ...) noexcept {
        va_list args;
        va_start(args, msg);
        vfprintf(DARGON_OUTF, msg, args);
        if(include_endl) {
            fprintf(DARGON_OUTF, "\n");
        }
        va_end(args);
    }

    /// @brief Prints to the standard output (string overload).
    /* inline void out(bool include_endl, const std::string& msg) noexcept {
        out(include_endl, msg.c_str());
    } */

    /// @brief Reads the input from the user.
    inline void in(std::string& lineOut) noexcept {
        out(false, "DIR> ");
        getline(DARGON_IN, lineOut);
    }

};

#endif
