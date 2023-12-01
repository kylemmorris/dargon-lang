/**
 * Dargon Programming Language
 * (C) Kyle Morris 2023 - See LICENSE.txt for license information.
 *
 * @file File.h
 * @author Kyle Morris
 * @since v0.1
 * @section Description
 * This superclass represents any Dargon file (scripts, config files, etc.)
 * Includes common utilities such as managing file positions, memoization,
 * etc.
 *
 */

#ifndef DARGON_HEADER_FILE
#define DARGON_HEADER_FILE

#include "FilePosition.h"

namespace dargon {

	/// @brief Supetclass for all Dargon files (scripts, config files, etc.)
	/// @author Kyle Morris
	/// @since v0.1
	class File {
	public:
        File();
        virtual ~File();
        bool OpenAbsolute(const std::string& path);
        bool OpenRelative(const std::string& relPath); //, const Workspace& workspace);
        FilePosition CurrentPosition() const;
        std::string DisplayPosition() const;
	private:
	};

	/// @brief A Dargon script, interpreted by DIR.
	/// @author Kyle Morris
	/// @since v0.1
	class Script : public File {};

};

#endif
