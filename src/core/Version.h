/**
 * Dargon Programming Language
 * (C) Kyle Morris 2023 - See LICENSE.txt for license information.
 *
 * @file Version.h
 * @author Kyle Morris
 * @since v0.1
 * @section Description
 * A place for version information and flags.
 *
 */

#ifndef DARGON_HEADER_VERSION
#define DARGON_HEADER_VERSION

#include <string>
#include "Utility.h"

namespace dargon {

    /// @brief The debug flag.
    #define DARGON_DEBUG

    /// @brief The version of Dargon.
    constexpr const char* VersionNum = "v0.0 alpha";

    /// @brief Returns the version in a more complete string form.
    inline std::string VersionString() {
        std::string r = "Dargon Interpreter ";
        #ifdef DARGON_DEBUG
        return r + "[DEBUG] " + VersionNum + " (" + GetDateTimeString() + ")";
        #else
        return r + VersionNum + " (" + GetDateTimeString() + ")";
        #endif
    }

};

#endif
