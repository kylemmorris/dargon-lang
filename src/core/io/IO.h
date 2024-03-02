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
//#include "Log.h"

namespace dargon {

    /// @brief The input stream used.
    #define DARGON_IN std::cin

    /// @brief The output stream used.
    #define DARGON_OUT std::cerr

    /// @brief Prints to the standard output.
    inline void out(const char* msg, bool include_endl = true) noexcept {
        if(include_endl) {
            DARGON_OUT << msg << "\n";
        }
        else {
            DARGON_OUT << msg;
        }

        //InfoLog(msg);
    }

    /// @brief Prints to the standard output (string overload).
    inline void out(const std::string& msg, bool include_endl = true) noexcept {
        out(msg.c_str(), include_endl);
    }

    /// @brief Reads the input from the user.
    inline void in(std::string& lineOut) noexcept {
        out("DIR> ", false);
        getline(DARGON_IN, lineOut);
    }

};

#endif
