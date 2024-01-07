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

    std::vector<std::string> SegmentString(std::string str, char c) noexcept {
        size_t pos = str.find(c);
        std::vector<std::string> ret;
        while(pos != std::string::npos) {
            ret.push_back(str.substr(0, pos));
            str.erase(0, pos+1);
            pos = str.find(c);
        }
        return ret;
    }

    void RemoveFromString(std::string& str, char c) noexcept {
        size_t pos = str.find(c);
        while(pos != std::string::npos) {
            str.erase(pos, 1);
            pos = str.find(c);
        }
    }

};
