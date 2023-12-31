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
#include <vector>

namespace dargon {

    /// @brief Returns the current date and time in YEAR-MONTH-DAY.TIME form.
    const std::string GetDateTimeString();

    /// @brief Segments a string by a character.
    /// @param str The input string.
    /// @param c The delimitter.
    /// @returns Segmented string.
    std::vector<std::string> SegmentString(std::string str, char c) noexcept;

    /// @brief Removes all instances of a given character from a line.
    /// @param str The string input.
    /// @param c The character to remove.
    void RemoveFromString(std::string& str, char c) noexcept;

};

#endif
