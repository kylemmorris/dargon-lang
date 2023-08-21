/*
 * Dargon Programming Language
 * (C) Kyle Morris 2023 - See LICENSE.txt for license information.
 *
 * FILE: Log.cpp
 *
 * DESCRIPTION: Implementation of Logging functions.
 *
 * SINCE: v0.1
 *
 */

#include "../include/Log.h"
#include "../include/Output.h"
#include "../include/Utility.h"

namespace dargon {
namespace hidden {

    void Log(const std::string& type, const std::string& msg, int lineNum, const char* fileName, bool includeLoc) noexcept {
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
            LogFile << GetDateTimeString() << " - " << "[" << type << "]: " << msg;
            if(includeLoc) {
                std::string s(fileName);
                LogFile << " (at " << s.substr(s.find_last_of("/\\") + 1) << " line " << lineNum;
            }
            LogFile << std::endl;
            LogFile.close();
            LogFileMutex.unlock();
        }
        catch(std::exception e) {
            // Should never get thrown!
            std::string s = "UNEXPECTED ERROR OCCURED: ";
            s += e.what();
            out(s);
        }
    }

}};
