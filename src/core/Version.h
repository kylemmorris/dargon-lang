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

    namespace flags {

        /// @brief The debug flag.
        #define DARGON_VERSION_DEBUG

        /// @brief If true, will time the execution of DIR and print to output (default = false).
        extern bool TimeExecution;

        /// @brief If true, DIR will generate a report of all To-Do-style comments (default = false).
        extern bool GenerateTodoReport;

        /// @brief If true, DIR will compile the source code, but will not execute it (default = false).
        extern bool CompileOnlyNoExecute;

        enum class LogSeverity {
            NORMAL,
            VERBOSE,
            ERROR_ONLY,
            NONE
        };

        /// @brief Specifies when Dargon can log (default = LogSeverity::NORMAL).
        extern LogSeverity LogSetting;

    };

    /// @brief The version of Dargon.
    /// Follows this scheme:
    /// version X.Y = release
    /// version X.Yb = beta
    /// version X.Y-DEBUG = Debug version
    constexpr const char* VersionNum = "version 0.1";

    /// @brief Copyright information.
    constexpr const char* Copyright = "(C) Kyle Morris 2023-2024 | See LICENSE.txt for license information.";

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
        os << "Dargon " << VersionNum;
        #ifdef DARGON_VERSION_DEBUG
        os << "-DEBUG ";
        #endif
        os << "(" << GetOSName() << ") - " << __DATE__ << ", " << __TIME__;
        return os.str();
    }

};

#endif