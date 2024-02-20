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
    enum class FileType {
        SOURCE, ///< *.dargon
        CONFIG, ///< *.snoot
        UNKNOWN ///< Unsupported
    };

	/// @brief Utility for file paths.
	/// @author Kyle Morris
	/// @since v0.1
	class Path final {
	private:
        #ifdef _WIN32 || _WIN64
        constexpr char m_slash = '\\';
        #else
        constexpr char m_slash = '/';
        #endif
        std::string m_full, m_name, m_name_noext, m_ext;
        file_type m_type;
        void init();
	public:
        Path();
        Path(const std::string& path);
        Path(const char* path);

        std::string& GetFull() const;
        std::string& GetFileName(bool extension = true) const;
        std::string& GetExtension() const;
        FileType& GetFileType() const;
	};

};

#endif
