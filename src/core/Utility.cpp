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
        strftime(buf, sizeof(buf), "%m.%d.%Y %X", &tstruct);
        return buf;
    }

    bool FileExists(const std::string& filePath) {
		// Check file status before anything else.
		struct stat st = { 0 };
		if (stat(filePath.c_str(), &st) == -1) {
            //throw Exception("Could not find file: " + filePath);
			return false;
		}
		std::ifstream file;
		file.open(filePath);
		if (!file.is_open()) {
            //throw Exception("Could not open file: " + filePath);
			file.close();
			return false;
		}
		file.close();
		return true;
	}

	std::string GetFilename(const std::string& path, bool include_extension) {
        // Go from "home/kmorris/Desktop/test.dargon" to "test.dargon"
        std::string ret = path;
        if(!ret.empty()) {
            // "home/kmorris/Desktop/test.dargon"
            size_t slash = ret.find('/');
            while(slash != std::string::npos) {
                ret.erase(ret.begin(), ret.begin() + slash + 1);
                slash = ret.find('/');
            }
            // Is now "test.dargon"
            if(!include_extension) {
                size_t ext = ret.find('.');
                while(ext != std::string::npos) {
                    ret.erase(ret.begin() + ext, ret.end()-1);
                    ext = ret.find('.');
                }
            }
        }
        return ret;
	}

};
