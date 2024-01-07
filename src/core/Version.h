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
#include <sstream>
#include "Utility.h"

namespace dargon {

    /// @brief The debug flag.
    #define DARGON_VERSION_DEBUG

    /// @brief The version of Dargon.
    /// Follows this scheme:
    /// vX.Y = release
    /// vX.Ya = Alpha
    /// vX.Yb = Beta
    /// vX.Y-DEBUG = Debug version
    constexpr const char* VersionNum = "v0.0a";

    /// @brief Returns the name of this operating system.
    inline std::string GetOSName() {
        #ifdef _WIN32
        return "Windows 32-bit";
        #elif _WIN64
        return "Windows 64-bit";
        #elif __APPLE__ || __MACH__
        return "Mac OSX";
        #elif __linux__
        return "Linux";
        #elif __FreeBSD__
        return "FreeBSD";
        #elif __unix || __unix__
        return "Unix";
        #else
        return "Unknown OS";
        #endif
    }

    /// @brief Returns the version in a more complete string form.
    inline std::string VersionString() {
        std::ostringstream os;
        os << "Dargon Interpreter " << VersionNum;
        #ifdef DARGON_VERSION_DEBUG
        os << "-DEBUG ";
        #endif
        os << "(" << GetOSName() << ") - " << __DATE__ << "-" << __TIME__;
        return os.str();
    }

};

#endif
