/*
 * Dargon Programming Language
 * (C) Kyle Morris 2023 - See LICENSE.txt for license information.
 *
 * FILE: Output.h
 *
 * DESCRIPTION: Provides standard utilities for outputting to std::cout.
 *
 * SINCE: v0.1
 *
 */

#ifndef DARGON_OUT_H
#define DARGON_OUT_H

#include <iostream>
#include <string>
//#include "Log.h"

namespace dargon {

    /**
     * @brief Prints to the standard output. Also logs to the log file.
    */
    inline void out(const char* msg) noexcept {
        std::cout << msg << std::endl;
        //InfoLog(msg);
    }

    /**
     * @brief Prints to the standard output (string overload).
    */
    inline void out(const std::string& msg) noexcept {
        out(msg.c_str());
    }

};

#endif
