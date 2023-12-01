/**
 * Dargon Programming Language
 * (C) Kyle Morris 2023 - See LICENSE.txt for license information.
 *
 * @file FilePosition.h
 * @author Kyle Morris
 * @since v0.1
 * @section Description
 * A struct used to represent a position in a Dargon file.
 *
 */

#ifndef DARGON_HEADER_FILEPOS
#define DARGON_HEADER_FILEPOS

#include <string>

namespace dargon {

    /// @brief Represents a position in a Dargon file.
	struct FilePosition {
	public:
        FilePosition() : line(0), col(0) {}
        FilePosition(int line) : line(line), col(0) {}
        FilePosition(int line, int pos) : line(line), col(pos) {}
        bool Valid() const { return line != 0 && col != 0; }
        std::string ToString() const {
            return "Line " + std::to_string(line) + " Col " + std::to_string(col);
        }
        bool Equals(const FilePosition& other) {
            return line == other.line && col == other.col;
        }
        // The line number.
        int line;
        // The position (column) in that line.
        int col;
	};

};

#endif
