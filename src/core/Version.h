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

        /// @brief If true, will time the execution of DIR and print to output.
        extern bool TimeExecution;

    };

    /// @brief The version of Dargon.
    /// Follows this scheme:
    /// version X.Y = release
    /// version X.Yb = beta
    /// version X.Y-DEBUG = Debug version
    constexpr const char* VersionNum = "version 0.1";

    /// @brief The ASCII-art banner displayed in the CLI.
    /// Credits:
    ///   Site: http://patorjk.com/software/taag/#p=author&f=Banner3-D&t=Dargon
    ///   Font: banner3-D by Merlin Greywolf merlin@brahms.udel.edu August 9, 1994
    constexpr const char* Banner =
        " ########:::::'###::::'########:::'######::::'#######::'##::: ##:\n"
        " ##.... ##:::'## ##::: ##.... ##:'##... ##::'##.... ##: ###:: ##:\n"
        " ##:::: ##::'##:. ##:: ##:::: ##: ##:::..::: ##:::: ##: ####: ##:\n"
        " ##:::: ##:'##:::. ##: ########:: ##::'####: ##:::: ##: ## ## ##:\n"
        " ##:::: ##: #########: ##.. ##::: ##::: ##:: ##:::: ##: ##. ####:\n"
        " ##:::: ##: ##.... ##: ##::. ##:: ##::: ##:: ##:::: ##: ##:. ###:\n"
        " ########:: ##:::: ##: ##:::. ##:. ######:::. #######:: ##::. ##:\n"
        "........:::..:::::..::..:::::..:::......:::::.......:::..::::..::\n";

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
        //os << "Dargon Interpreter " << VersionNum;
        os << Banner << VersionNum;
        #ifdef DARGON_VERSION_DEBUG
        os << "-DEBUG ";
        #endif
        os << "(" << GetOSName() << ") - " << __DATE__ << ", " << __TIME__;
        return os.str();
    }

};

#endif
