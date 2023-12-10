/**
 * Dargon Programming Language
 * (C) Kyle Morris 2023 - See LICENSE.txt for license information.
 *
 * @file Paht.h
 * @author Kyle Morris
 * @since v0.1
 * @section Description
 * Provides a nice interface for file paths.
 *
 */

#ifndef DARGON_HEADER_PATH
#define DARGON_HEADER_PATH

#include <string>

namespace dargon {

	/// @brief Provides cross-platform support for file paths, along with other utilities.
	/// @author Kyle Morris
	/// @since v0.1
	class Path final {
	public:
        /// @brief Enumeration of supported file extensions.
        enum class Extension {
            DARGON,
            DARGON_CONFIG,
            INVALID
        };

        /// @brief Empty constructor.
        Path() {}
        /// @brief Main constructor.
        Path(const std::string& path);
        /// @brief Destructor.
        ~Path();
        /// @brief Returns the full path.
        std::string GetFull() const;
        /// @brief Returns the file name without its extension.
        std::string GetFilenNameNoExt() const;
        /// @brief Returns the file name including its extension.
        std::string GetFileName() const;
        /// @brief Returns the file extension recognized by Dargon.
        Extension GetFileExtension() const;

        // operator ...
	private:
        // Lazy memoization below
        std::string _full;
        std::string _fnameNoExt;
        std::string _fname;
        std::string _ext;
        Extension _type;
	};

};

#endif
