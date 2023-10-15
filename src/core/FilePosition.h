/*
 * Dargon Programming Language
 * (C) Kyle Morris 2023 - See LICENSE.txt for license information.
 *
 * FILE: FilePosition.h
 *
 * DESCRIPTION: A struct that represents a position in the file.
 *              This piece of metadata is stored in Tokens.
 *
 * SINCE: v0.1
 *
 */

#ifndef DARGON_FILEPOS_H
#define DARGON_FILEPOS_H

#include <string>

namespace dargon {

	/**
     * @brief A struct that represents a position
     *        in a Dargon file.
    */
	struct FilePosition {
	public:
        FilePosition() : line(0), col(0), fileName("") {}
        FilePosition(int line) : line(line), col(0), fileName("") {}
        FilePosition(int line, int pos) : line(line), col(pos), fileName("") {}
        FilePosition(int line, int pos, const std::string& fName) : line(line), col(pos), fileName(fName) {}
        bool Valid() const { return line != 0 && col != 0; }
        std::string ToString() const {
            return "[" + fileName + " Line " + std::to_string(line) + " Col " + std::to_string(col) + "]";
        }
        // The line number.
        int line;
        // The position (column) in that line.
        int col;
        // The file name
        std::string fileName;
	};

// Macro for building a file positon from this source code
#define DARGON_FILE_POSITION FilePosition(__LINE__, 0, __FILE__)

};

#endif
