/*
 * Dargon Programming Language
 * (C) Kyle Morris 2023 - See LICENSE.txt for license information.
 *
 * FILE: Utility.h
 *
 * DESCRIPTION: General-purpose utility functions/classes.
 *
 * SINCE: v0.1
 *
 */

#ifndef DARGON_UTILITY_H
#define DARGON_UTILITY_H

#include <string>
#include <fstream>

namespace dargon {

	/**
     * @brief Returns the current date and time in YEAR-MONTH-DAY.TIME form.
    */
    const std::string GetDateTimeString();

    /**
     * @brief Attempts to open the file specified at filePath.
     * @param filePath Path to the file.
     * @param file The file stream being outputted.
     * @returns True if okay, false if not.
    */
    bool TryOpenFile(const std::string& filePath, std::fstream& file);

};

#endif
