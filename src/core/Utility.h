/**
 * Dargon Programming Language
 * (C) Kyle Morris 2023 - See LICENSE.txt for license information.
 *
 * @file Utility.h
 * @author Kyle Morris
 * @since v0.1
 * @section Description
 * A place for general-purpose utility functions.
 *
 */

#ifndef DARGON_HEADER_UTIL
#define DARGON_HEADER_UTIL

#include <string>

namespace dargon {

    /// @brief Returns the current date and time in YEAR-MONTH-DAY.TIME form.
    const std::string GetDateTimeString();

};

#endif
