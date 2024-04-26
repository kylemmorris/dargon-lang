/**
 * Dargon Programming Language
 * (C) Kyle Morris 2023 - See LICENSE.txt for license information.
 *
 * @file path.h
 * @author Kyle Morris
 * @since v0.1
 * @section Description
 * A nice interface for file paths.
 *
 */

#ifndef DARGON_HEADER_PATH
#define DARGON_HEADER_PATH

#include <string>

namespace dargon {

    /// @brief File types supported
    enum class FileType : int {
        SOURCE, ///< *.dargon
        CONFIG, ///< *.snoot
        UNKNOWN ///< Unsupported
    };

	/// @brief Utility for file paths.
	/// @author Kyle Morris
	/// @since v0.1
	class Path final {
	private:
        std::string m_full, m_name, m_name_noext, m_ext;
        FileType m_type;
        void init();
	public:
        Path();
        Path(const std::string& path);
        Path(const char* path);

        const std::string& GetFull() const;
        const std::string& GetFileName(bool extension = true) const;
        const std::string& GetFileExtension() const;
        const FileType& GetFileType() const;

        #if defined(_WIN32) || defined(_WIN64)
        constexpr static char Slash = '\\';
        #else
        constexpr static char Slash = '/';
        #endif
	};

};

#endif
