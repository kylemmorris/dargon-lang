/*
 * Dargon Programming Language
 * (C) Kyle Morris 2023 - See LICENSE.txt for license information.
 *
 * FILE: Log.h
 *
 * DESCRIPTION: General-purpose logging utilities.
 *              Contains the preferred macros.
 *
 * SINCE: v0.1
 *
 */

#ifndef DARGON_LOG_H
#define DARGON_LOG_H

#include <fstream>
#include <mutex>
#include "Version.h"

namespace dargon {
namespace hidden {

    constexpr const char* LogFileName = "dargon.log";
    static std::ofstream LogFile;
    static std::mutex LogFileMutex;

    /**
     * @brief Underlying Log function for macros.
     * Use the macros 'InfoLog', 'WarnLog', and 'ErrorLog' instead.
    */
    void Log(const std::string& type, const std::string& msg, int lineNum = 0, const char* fileName = "", bool includeLoc = false) noexcept;

}}; // dargon::hidden

// MACRO JUSTIFICATION: The utility of the dynamic macros '__FILE__' and '__LINE__'.

// Prints "Time - [INFO]: msg" to the log file.
#define InfoLog(msg) dargon::hidden::Log("INFO", msg, __LINE__, __FILE__, false)
// Prints "Time - [WARN]: msg (at FILE line LINENUM)" to the log file.
#define WarnLog(msg) dargon::hidden::Log("WARN", msg, __LINE__, __FILE__, true)
// Prints "Time - [ERROR]: msg (at FILE line LINENUM)" to the log file.
#define ErroLog(msg) dargon::hidden::Log("ERROR", msg, __LINE__, __FILE__, true)
// Prints "Time - [DEBUG]: msg (at FILE line LINENUM)" to the log file but ONLY in debug mode.
#ifdef DARGON_DEBUG
#define DebugLog(msg) dargon::hidden::Log("DEBUG", msg, __LINE__, __FILE__, true)
#else
#define DebugLog(msg)
#endif // DARGON_DEBUG

#endif
