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

    /// @brief Prints to the standard output.
    inline void out(const char* msg) noexcept {
        std::cout << msg << std::endl;
        //InfoLog(msg);
    }

    /// @brief Prints to the standard output (string overload).
    inline void out(const std::string& msg) noexcept {
        out(msg.c_str());
    }

};

#endif
