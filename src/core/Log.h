/**
 * Dargon Programming Language
 * (C) Kyle Morris 2023 - See LICENSE.txt for license information.
 *
 * @file Log.h
 * @author Kyle Morris
 * @since v0.1
 * @section Description
 * A place for general-purpose logging utilities.
 *
 */

#ifndef DARGON_LOG_H
#define DARGON_LOG_H

#include <fstream>
#include <mutex>
#include "Version.h"
#include "lex/Token.h"

namespace dargon {
namespace hidden {

    /// @brief The log file name.
    constexpr const char* LogFileName = "dargon.log";
    /// @brief The log file used throughout.
    static std::ofstream LogFile;
    /// @brief The mutex used.
    static std::mutex LogFileMutex;

    /// @brief Underlying log function. Use macros instead.
    void Log(const std::string& type, const std::string& msg, int lineNum = 0, const char* fileName = "", bool includeLoc = false) noexcept;

}

    /// @brief Reports any and all errors to the user.
    /// @param token The token the error occured at.
    /// @param msg The message to display and log.
    void ReportError(const Token& token, const std::string& msg) noexcept;

};

// MACRO JUSTIFICATION: The utility of the dynamic macros '__FILE__' and '__LINE__'.

/// @brief Prints "Time - [INFO]: msg" to the log file.
#define DARGON_LOG_INFO(msg) dargon::hidden::Log("INFO", msg, __LINE__, __FILE__, false)
/// @brief Prints "Time - [WARN]: msg (at FILE line LINENUM)" to the log file.
#define DARGON_LOG_WARN(msg) dargon::hidden::Log("WARN", msg, __LINE__, __FILE__, true)
/// @brief Prints "Time - [ERROR]: msg (at FILE line LINENUM)" to the log file.
#define DARGON_LOG_ERROR(msg) dargon::hidden::Log("ERROR", msg, __LINE__, __FILE__, true)

#ifdef DARGON_VERSION_DEBUG
/// @brief Prints "Time - [DEBUG]: msg (at FILE line LINENUM)" to the log file but ONLY in debug mode.
#define DARGON_LOG_DEBUG(msg) dargon::hidden::Log("DEBUG", msg, __LINE__, __FILE__, true)
#else
/// @brief Prints "Time - [DEBUG]: msg (at FILE line LINENUM)" to the log file but ONLY in debug mode.
#define DARGON_LOG_DEBUG(msg)
#endif // DARGON_DEBUG

#endif
