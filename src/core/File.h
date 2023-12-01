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

#include <iostream>
#include <fstream>
#include "FilePosition.h"

namespace dargon {

	/// @brief Supetclass for all Dargon files (scripts, config files, etc.)
	/// @author Kyle Morris
	/// @since v0.1
	class File {
	public:
        /// @brief Constructor
        File();

        /// @brief Virtual destructor.
        virtual ~File();

        /// @brief Opens a file using an absolute path.
        /// @param path The absolute path.
        /// @returns True if okay, false if file not found.
        bool OpenAbsolute(const std::string& path);

        /// @brief Opens a file using a path relative to the Dargon workspace.
        /// @param path The relative path.
        /// @returns True if okay, false if file not found.
        bool OpenRelative(const std::string& relPath); //, const Workspace& workspace);

        /// @brief Closes the file reference.
        /// Note that this is called in the File destructor automatically too.
        void Close();

        /// @brief Provides the current file position.
        /// @returns The FilePosition object.
        /// @see FilePosition
        FilePosition CurrentPosition() const;

        /// @brief Provides the file position as the following string:
        ///     filename @ Line x Col y
        std::string ShowPosition() const;

        /// @brief Provides a more detailed position string:
        ///     filename @ Line x Col y
        ///     some line here, column pointer below
        ///     ~~~~~~~~~~~~~~^
        std::string ShowExactPosition() const;

        /// @brief Resets the file position to (1,1)
        void Reset();

        /// @brief Moves the file pointer up.
        /// @param spaces The spaces to move. Default 1.
        /// @returns True if okay, false if the position would be out
        /// of the bounds of the file.
        bool MoveUp(unsigned int spaces = 1);

        /// @brief Moves the file pointer down.
        /// @param spaces The spaces to move. Default 1.
        /// @returns True if okay, false if the position would be out
        /// of the bounds of the file.
        bool MoveDown(unsigned int spaces = 1);

        /// @brief Moves the file pointer left.
        /// @param spaces The spaces to move. Default 1.
        /// @returns True if okay, false if the position would be out
        /// of the bounds of the file.
        bool MoveLeft(unsigned int spaces = 1);

        /// @brief Moves the file pointer right.
        /// @param spaces The spaces to move. Default 1.
        /// @returns True if okay, false if the position would be out
        /// of the bounds of the file.
        bool MoveRight(unsigned int spaces = 1);

        /// @brief Goes directly to a specific line, resetting the
        /// column to 0.
        /// @returns True if okay, false if the position would be out
        /// of bounds of the file.
        bool GotoLine(unsigned int exactLine);

        /// @brief Goes directly to a specific column in the current line.
        /// @returns True if okay, false if the position would be out
        /// of bounds of the file
        bool GotoColumn(unsigned int exactColumn);

        /// @brief Reads the character currently pointed to.
        /// @returns The character (including EOF).
        char ReadChar() const;

        /// @brief Returns the contents of the current line.
        /// @returns The contents of the line, regarless of column.
        std::string ReadLine() const;
	private:
        /// @brief The file stream.
        std::ifstream _file;
        /// @brief Filename (w/ extension)
        std::string _fname;
        /// @brief The file position (tracked).
        FilePosition _pos;
	};

	/// @brief A Dargon script, interpreted by DIR.
	/// @author Kyle Morris
	/// @since v0.1
	class Script : public File {};

};

#endif
