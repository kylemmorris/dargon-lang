/*
 * Dargon Programming Language
 * (C) Kyle Morris 2023 - See LICENSE.txt for license information.
 *
 * FILE: Version.h
 *
 * DESCRIPTION: Contains the version information for the software.
 *
 * SINCE: v0.1
 *
 */

#ifndef DARGON_VERSION_H
#define DARGON_VERSION_H

#include <string>
#include "Utility.h"

namespace dargon {

    // The debug flag.
    // MACRO JUSTIFICATION: For its usage in Log.h
    #define DARGON_DEBUG

    constexpr const char* VersionNum = "v0.0 alpha";

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
