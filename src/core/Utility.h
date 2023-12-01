/**
 * Dargon Programming Language
 * (C) Kyle Morris 2023 - See LICENSE.txt for license information.
 *
 * @file Utility.h
 * @author Kyle Morris
 * @since v0.1
 * @section Description
 * A place for general-purpose utility functions.
 *
 */

#ifndef DARGON_HEADER_UTIL
#define DARGON_HEADER_UTIL

#include <string>
#include <fstream>

namespace dargon {

    /// @brief Returns the current date and time in YEAR-MONTH-DAY.TIME form.
    const std::string GetDateTimeString();

    /// @brief Checks if a file exists.
    /// @returns True if okay, false if not.
    bool FileExists(const std::string& filePath);

    /// @brief Given a path properly delimitted, returns the name of that file.
    /// @param path The path.
    /// @param include_extension If true, will include file extension. True by default.
    /// @param The name of the file without or without extension.
    std::string GetFilename(const std::string& path, bool include_extension = true);

};

#endif
