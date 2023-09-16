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

#include "Exception.h"
#include "Log.h"

namespace dargon {

    const char* Exception::what() const noexcept {
            ErroLog(_msg);
            return _msg.c_str();
    }

};

