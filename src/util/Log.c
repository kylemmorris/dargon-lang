/*****************************************************************
* Dargon Programming Language
* (C) Kyle Morris 2025 - See LICENSE.txt for license information.
*
* @file Log.c
* @author Kyle Morris
* @since v0.1
* @section Description
* Logging utility.
*
*****************************************************************/
#include <stdio.h>
#include <time.h>

#include "Log.h"

static const char* const _logFileName = "dargon.log";
static const char* const _drgTimeFormat = "%X";

static void _log(const char* type, const char* fmt, va_list args)
{
    static FILE* _logFile = NULL;
    static int _firstCall = 1;

    static char _timeBuf[80];
    static time_t _now;
    static struct tm _tstruct;

    // Create copy for later
    va_list _forcout;
    va_copy(_forcout, args);

    // Open file
    _logFile = fopen(_logFileName, _firstCall ? "w" : "a");
    if(!_logFile) {
        perror("ERROR: _log(): fopen() failed!");
        fclose(_logFile);
        return;
    }
    _firstCall = 0;
    int errCode = 0;

    // Write: "time [type] msg\n"
    // -- time + type
    _now = time(0);
    _tstruct = *localtime(&_now);
    strftime(_timeBuf, sizeof(_timeBuf), _drgTimeFormat, &_tstruct);
    errCode = fprintf(_logFile, "%s [%s] ", _timeBuf, type);
    if(errCode < 0) {
        perror("ERROR: _log(): fprintf() produced a negative value!");
        fclose(_logFile);
        return;
    }
    errCode = fprintf(stdout, "[%s] ", type); // also write to stdout
    if(errCode < 0) {
        perror("ERROR: _log(): fprintf() produced a negative value!");
        fclose(_logFile);
        return;
    }
    //  -- rest of message
    errCode = vfprintf(_logFile, fmt, args);
    if(errCode < 0) {
        perror("ERROR: _log(): vfprintf() produced a negative value!");
        fclose(_logFile);
        return;
    }
    errCode = vfprintf(stdout, fmt, _forcout);
    if(errCode < 0) {
        perror("ERROR: _log(): vfprintf() produced a negative value!");
        fclose(_logFile);
        return;
    }

    fprintf(_logFile, "\n");
    fprintf(stdout, "\n");
    fclose(_logFile);
}

void D_Log(const char* msgFmt, ...) {
    va_list args;
    va_start(args, msgFmt);
    _log("INFO", msgFmt, args);
    va_end(args);
}
void D_LogWarning(const char* msgFmt, ...) {
    va_list args;
    va_start(args, msgFmt);
    _log("WARN", msgFmt, args);
    va_end(args);
}
void D_LogError(const char* msgFmt, ...) {
    va_list args;
    va_start(args, msgFmt);
    _log("ERROR", msgFmt, args);
    va_end(args);
}