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
#include <cstdio>
#include <stdarg.h>
#include "../Version.h"
#include "../lex/Token.h"
#include "IO.h"

namespace dargon {
namespace hidden {

    /// @brief The log file name.
    constexpr const char* LogFileName = "dargon.log";
    /// @brief The log file used throughout.
    static FILE* LogFilef;
    static bool firstCall = true;
    static std::ofstream LogFile;
    /// @brief The mutex used.
    static std::mutex LogFileMutex;

    /// @brief Kinds of log messages
    enum class LogType {
        INFO,
        WARN,
        ERROR,
        DEBUG
    };

    /// @brief Underlying log function. Use macros instead.
    void Log(const LogType& type, const std::string& msg, int lineNum = 0, const char* fileName = "", bool includeLoc = false, bool isVerbose = false) noexcept;

    /// @brief Underlying, formattable log function. Use macros instead.
    void LogFormat(const LogType& type, int lineNum, const char* fileName, bool includeLoc , bool isVerbose, const char* fmt, ...) noexcept;

    // Below technically works BUT templates create multiple functions, and I feel it would become
    // bloated as the codebase grew, since logging is such a crucial part of programming.
    //template<typename... Args>
    //void LogFormat(const LogType& type, int ln, const char* fn, bool loc, bool verb, const char* fmt, Args... args) noexcept {

}

};

// MACRO JUSTIFICATION: The utility of the dynamic macros '__FILE__' and '__LINE__'.

/// @brief Prints "Time - [INFO]: msg" to the log file (ONLY if its in verbose logging mode) Verbose is by definition INFO.
#define DARGON_LOG_VERBOSE(...) dargon::hidden::LogFormat(dargon::hidden::LogType::INFO, __LINE__, __FILE__, false, true, __VA_ARGS__)
/// @brief Prints "Time - [INFO]: msg" to the log file.
#define DARGON_LOG_INFO(...) dargon::hidden::LogFormat(dargon::hidden::LogType::INFO, __LINE__, __FILE__, false, false, __VA_ARGS__)
/// @brief Prints "Time - [WARN]: msg (at FILE line LINENUM)" to the log file.
#define DARGON_LOG_WARN(...) dargon::hidden::LogFormat(dargon::hidden::LogType::WARN, __LINE__, __FILE__, true, false, __VA_ARGS__)
/// @brief Prints "Time - [ERROR]: msg (at FILE line LINENUM)" to the log file.
#define DARGON_LOG_ERROR(...) dargon::hidden::LogFormat(dargon::hidden::LogType::ERROR, __LINE__, __FILE__, true, false, __VA_ARGS__)

#ifdef DARGON_VERSION_DEBUG
/// @brief Prints "Time - [DEBUG]: msg (at FILE line LINENUM)" to the log file but ONLY in debug mode.
#define DARGON_LOG_DEBUG(...) dargon::hidden::LogFormat(dargon::hidden::LogType::DEBUG, __LINE__, __FILE__, true, false, __VA_ARGS__)
#else
/// @brief Prints "Time - [DEBUG]: msg (at FILE line LINENUM)" to the log file but ONLY in debug mode.
#define DARGON_LOG_DEBUG(msg)
#endif // DARGON_DEBUG

#endif
