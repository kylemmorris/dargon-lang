/*****************************************************************
* Dargon Programming Language
* (C) Kyle Morris 2025 - See LICENSE.txt for license information.
*
* @file Version.h
* @author Kyle Morris
* @since v0.1
* @section Description
* Contains version information.
*
*****************************************************************/

#ifndef DRG_H_VERSION
#define DRG_H_VERSION

#define DRG_DEBUG 1

#define DRG_PROGRAM_NAME "Dargon Programming Language version 0.1"
#define DRG_COPYRIGHT "(C) Kyle Morris 2025 - See LICENSE.txt for license information."

static const char* const D_SoftwareVersion =
    DRG_PROGRAM_NAME 
    #ifdef _WIN32
    " (Windows 32-bit)"
    #elif _WIN64
    " (Windows 64-bit)"
    #elif __APPLE__ || __MACH__
    " (Mac OS)"
    #elif __linux__
    " (Linux)"
    #elif __FreeBSD__
    " (FreeBSD)"
    #elif __unix__ || __unix
    " (Unix)"
    #endif
    "\n" DRG_COPYRIGHT "\n";

#endif // DRG_H_VERSION
