/**
 * Dargon Programming Language
 * (C) Kyle Morris 2023 - See LICENSE.txt for license information.
 *
 * @file Utility.cpp
 * @author Kyle Morris
 * @since v0.1
 * @section Description
 * A place for general-purpose utility functions.
 *
 */

#include <chrono>
#include <ctime>
#include <time.h>
#include "Utility.h"
#include "Exception.h"

namespace dargon {

    const std::string GetDateTimeString() {
        time_t     now = time(0);
        struct tm  tstruct;
        char       buf[80];
        tstruct = *localtime(&now);
        // "%Y-%m-%d.%X"
        strftime(buf, sizeof(buf), "%m.%d.%Y %X", &tstruct);
        return buf;
    }

};
