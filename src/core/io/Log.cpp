/**
 * Dargon Programming Language
 * (C) Kyle Morris 2023 - See LICENSE.txt for license information.
 *
 * @file Log.cpp
 * @author Kyle Morris
 * @since v0.1
 * @section Description
 * A place for general-purpose logging utilities.
 *
 */

#include <sstream>
#include "Log.h"
#include "IO.h"
#include "../Utility.h"

namespace dargon {
namespace hidden {

    void Log(const LogType& type, const std::string& msg, int lineNum, const char* fileName, bool includeLoc, bool isVerbose) noexcept {
        if(flags::LogSetting == flags::LogSeverity::NONE) { return; }
        if(isVerbose && flags::LogSetting != flags::LogSeverity::VERBOSE) { return; }
        if(flags::LogSetting == flags::LogSeverity::ERROR_ONLY && type != LogType::ERROR) { return; }
        try {
            LogFileMutex.lock();
            static bool firstCall = true;
            if(firstCall) {
                LogFile.open(LogFileName, std::ios::out | std::ios::out);
                firstCall = false;
            }
            else {
                LogFile.open(LogFileName, std::ios::out | std::ios::app);
            }
            LogFile << GetDateTimeString();
            switch(type) {
                case LogType::INFO: LogFile << "INFO"; break;
                case LogType::WARN: LogFile << "WARN"; break;
                case LogType::ERROR: LogFile << "ERROR"; break;
                case LogType::DEBUG: LogFile << "DEBUG"; break;
                default: break;
            };
            LogFile << ": " << msg;
            out(msg);
            if(includeLoc) {
                std::string s(fileName);
                LogFile << " (at " << s.substr(s.find_last_of("/\\") + 1) << " line " << lineNum << ")";
            }
            LogFile << std::endl;
            LogFile.close();
            LogFileMutex.unlock();
        }
        catch(const std::exception& e) {
            // Should never get thrown!
            std::string s = "UNEXPECTED ERROR OCCURED: ";
            s += e.what();
            out(s);
            LogFile.close();
            LogFileMutex.unlock();
        }
    }

    void LogFormat(const LogType& type, int lineNum, const char* fileName, bool includeLoc, bool isVerbose, const char* fmt, ...) noexcept {
        if(flags::LogSetting == flags::LogSeverity::NONE) { return; }
        if(isVerbose && flags::LogSetting != flags::LogSeverity::VERBOSE) { return; }
        if(flags::LogSetting == flags::LogSeverity::ERROR_ONLY && type != LogType::ERROR) { return; }
        try {
            LogFileMutex.lock();
            if(firstCall) {
                LogFilef = fopen(LogFileName, "w");
                firstCall = false;
            }
            else {
                LogFilef = fopen(LogFileName, "a");
            }
            fprintf(LogFilef, "%s ", GetDateTimeString().c_str());
            switch(type) {
                case LogType::INFO: fprintf(LogFilef, "[%s]: ", "INFO"); break;
                case LogType::WARN: fprintf(LogFilef, "[%s]: ", "WARN"); break;
                case LogType::ERROR: fprintf(LogFilef, "[%s]: ", "ERROR"); break;
                case LogType::DEBUG: fprintf(LogFilef, "[%s]: ", "DEBUG"); break;
                default: break;
            }
            va_list args;
            va_start(args, fmt);
            vfprintf(LogFilef, fmt, args);
            va_start(args, fmt);
            vfprintf(DARGON_OUTF, fmt, args); // Print same message to console
            fprintf(DARGON_OUTF, "\n");
            if(includeLoc) {
                std::string s(fileName);
                fprintf(LogFilef, " (at %s line %d)", s.substr(s.find_last_of("/\\") + 1).c_str(), lineNum);
            }
            fprintf(LogFilef, "\n");
            fclose(LogFilef);
            va_end(args);
            LogFileMutex.unlock();
        }
        catch(const std::exception& e) {
            // Should never get thrown!
            std::string s = "UNEXPECTED ERROR OCCURED: ";
            s += e.what();
            out(s);
            fclose(LogFilef);
            LogFileMutex.unlock();
        }
    }

}
};
