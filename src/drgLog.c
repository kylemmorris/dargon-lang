/*****************************************************************
* Dargon Programming Language
* (C) Kyle Morris 2025 - See LICENSE.txt for license information.
*
* @file drgLog.c
* @author Kyle Morris
* @since v0.1
* @section Description
* Logging utility.
*
*****************************************************************/
#include <stdio.h>
#include <time.h>

#include "drgLog.h"

static const char* const _drgLogFileName = "drg.log";
static const char* const _drgTimeFormat = "%X";

#ifdef DRG_DEBUG
static void _drgVLog(const char* fileName, int lineNum, const char* type, const char* fmt, va_list args)
#else
static void _drgVLog(const char* type, const char* fmt, va_list args)
#endif
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
    _logFile = fopen(_drgLogFileName, _firstCall ? "w" : "a");
    if(!_logFile) {
        perror("ERROR: _drgVLog(): fopen() failed!");
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
        perror("ERROR: _drgVLog(): fprintf() produced a negative value!");
        fclose(_logFile);
        return;
    }
    errCode = fprintf(stdout, "[%s] ", type); // also write to stdout
    if(errCode < 0) {
        perror("ERROR: _drgVLog(): fprintf() produced a negative value!");
        fclose(_logFile);
        return;
    }
    //  -- rest of message
    errCode = vfprintf(_logFile, fmt, args);
    if(errCode < 0) {
        perror("ERROR: _drgVLog(): vfprintf() produced a negative value!");
        fclose(_logFile);
        return;
    }
    errCode = vfprintf(stdout, fmt, _forcout);
    if(errCode < 0) {
        perror("ERROR: _drgVLog(): vfprintf() produced a negative value!");
        fclose(_logFile);
        return;
    }

    // Write DEBUG stuff is applicable
#ifdef DRG_DEBUG
    errCode = fprintf(_logFile, "\n\tat %s - line %d\n", fileName, lineNum);
    if(errCode < 0) {
        perror("ERROR: _drgVLog(): fprintf() produced a negative value!");
        fclose(_logFile);
        return;
    }
    errCode = fprintf(stdout, "\n\tat %s - line %d\n", fileName, lineNum);
    if(errCode < 0) {
        perror("ERROR: _drgVLog(): fprintf() produced a negative value!");
        fclose(_logFile);
        return;
    }
#endif

    fprintf(_logFile, "\n");
    fprintf(stdout, "\n");
    fclose(_logFile);
}

#ifdef DRG_DEBUG
void _drgLog(int lineNum, const char* fileName, const char* msgFmt, ...) {
    va_list args;
    va_start(args, msgFmt);
    _drgVLog(fileName, lineNum, "INFO", msgFmt, args);
    va_end(args);
}

void _drgLogWarning(int lineNum, const char* fileName, const char* msgFmt, ...) {
    va_list args;
    va_start(args, msgFmt);
    _drgVLog(fileName, lineNum, "WARN", msgFmt, args);
    va_end(args);
}

void _drgLogError(int lineNum, const char* fileName, const char* msgFmt, ...) {
    va_list args;
    va_start(args, msgFmt);
    _drgVLog(fileName, lineNum, "ERROR", msgFmt, args);
    va_end(args);
}
#else

void drgLog(const char* msgFmt, ...) {
    va_list args;
    va_start(args, msgFmt);
    _drgVLog("INFO", msgFmt, args);
    va_end(args);
}
void drgLogWarning(const char* msgFmt, ...) {
    va_list args;
    va_start(args, msgFmt);
    _drgVLog("WARN", msgFmt, args);
    va_end(args);
}
void drgLogError(const char* msgFmt, ...) {
    va_list args;
    va_start(args, msgFmt);
    _drgVLog("ERROR", msgFmt, args);
    va_end(args);
}
#endif
