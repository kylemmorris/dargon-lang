/**
 * Dargon Programming Language
 * (C) Kyle Morris 2023 - See LICENSE.txt for license information.
 *
 * @file Utility.cpp
 * @author Kyle Morris
 * @since v0.1
 * @section Description
 * A place for general-purpose utility functions.
 *
 */

#include <chrono>
#include <ctime>
#include <time.h>
#include <sys/stat.h>
#include "Utility.h"
#include "Exception.h"

namespace dargon {

    const std::string GetDateTimeString() {
        time_t     now = time(0);
        struct tm  tstruct;
        char       buf[80];
        tstruct = *localtime(&now);
        // "%Y-%m-%d.%X"
        strftime(buf, sizeof(buf), "%m.%d.%Y.%X", &tstruct);
        return buf;
    }

    bool TryOpenFile(const std::string& filePath, std::fstream& file) {
		// Check file status before anything else.
		struct stat st = { 0 };
		if (stat(filePath.c_str(), &st) == -1) {
            throw Exception("Could not find file: " + filePath);
			return false;
		}
		file.open(filePath, std::ios::out | std::ios::out);
		if (!file.is_open()) {
            throw Exception("Could not open file: " + filePath);
			file.close();
			return false;
		}
		return true;
	}

};
