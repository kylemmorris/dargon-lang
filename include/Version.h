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

    // MACRO JUSTIFICATION: For its usage in Log.h

    // The debug flag.
    #define DARGON_DEBUG

    inline std::string Version() {
        std::string r = "Dargon Interpreter ";
        #ifdef DARGON_DEBUG
        return r +"[DEBUG]" + " v0.1 (" + GetDateTimeString() + ")";
        #else
        return r + " v0.1 (" + GetDateTimeString() + ")";
        #endif
    }

};

#endif
