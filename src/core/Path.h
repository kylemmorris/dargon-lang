/**
 * Dargon Programming Language
 * (C) Kyle Morris 2023 - See LICENSE.txt for license information.
 *
 * @file Paht.h
 * @author Kyle Morris
 * @since v0.1
 * @section Description
 * Provides cross-platform support for file paths, along with other utilities.
 *
 */

#ifndef DARGON_HEADER_PATH
#define DARGON_HEADER_PATH

#include <string>

namespace dargon {

	/// @brief Provides cross-platform support for file paths, along with other utilities.
	/// @author Kyle Morris
	/// @since v0.1
	class Path {
	public:
        Path(const std::string& path);
        ~Path();

        std::string GetFull() const;
        std::string GetFilenNameNoExt() const;
        std::string GetFileName() const;
        std::string GetFileExtension() const;

        // operator ...
	private:
        // Lazy memoization below
        std::string _full;
        std::string _fnameNoExt;
        std::string _fname;
        std::string _ext;
        #ifdef _WIN32
        //static char _separator = '\\';
        #else
        //static char _separator = '/';
        #endif
	};

};

#endif
