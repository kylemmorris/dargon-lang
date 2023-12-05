/**
 * Dargon Programming Language
 * (C) Kyle Morris 2023 - See LICENSE.txt for license information.
 *
 * @file File.cpp
 * @author Kyle Morris
 * @since v0.1
 * @section Description
 * Implementation of File superclass.
 *
 */

#include <sstream>
#include "File.h"
#include "Utility.h"
#include <iomanip>

namespace dargon {

    File::File() {}

    File::~File() {
        Close();
    }

    bool File::OpenAbsolute(const std::string& path) {
        if(FileExists(path)) {
            std::ifstream file(path);
            if(file.is_open()) {
                // TODO: Optimize for larger files.
                _fname = GetFilename(path, true);
                // Copy entire contents of file
                std::string line;
                while(std::getline(file, line)) {
                    _contents.push_back(line);
                }
                Reset();
                file.close();
                return true;
            }
            file.close();
            return false;
        }
        return false;
    }

    bool File::OpenRelative(const std::string& relPath) {
        return true;
    }

    void File::Close() {
        _contents.clear();
    }

    FilePosition File::CurrentPosition() const {
        // Internally we index by 0 - for the user, they expect
        // line 1, column 1 to the be the origin.
        FilePosition ret = _pos;
        ret.line++;
        ret.col++;
        return ret;
    }

    std::string File::ShowPosition() const {
        std::ostringstream os;
        os << _fname << " @ " << CurrentPosition().ToString();
        return os.str();
    }

    std::string File::ShowExactPosition() const {
        std::ostringstream os;
        os << ShowPosition() << std::endl;
        os << _contents[_pos.line] << std::endl;
        size_t tot = _contents.size();
        for(int i = 0; i < _pos.col; i++) {
            os << "-";
        }
        os << "^";
        return os.str();
    }

    void File::Reset() {
        // Internally, we use 0-based to keep things simple
        _pos = FilePosition(0,0);
    }

    bool File::MoveUp(int spaces) {
        // Go up one line (try to).
        for(int i = 0; i < spaces; i++) {
            if(_pos.line == 0) { return false; }
            _pos.line--;
            _pos.col = 0;
        }
        return true;
    }

    bool File::MoveDown(int spaces) {
        // Go down one line (try to).
        for(int i = 0; i < spaces; i++) {
            if(_pos.line == _contents.size()) { return false; }
            _pos.line++;
            _pos.col = 0;
        }
        return true;
    }

    bool File::MoveRight(int spaces) {
        // Move right one space - if we are on the last place, go to next line
        for(int i = 0; i < spaces; i++) {
            // If we are at the last position of this line, try to go to the next line.
            if(_pos.col == _contents[_pos.line].length()) {
                _pos.col = 0;
                _pos.line++;
                // End of file!
                if(_pos.line == _contents[_pos.line].length()) {
                    return false;
                }
            }
            else {
                _pos.col++;
            }
        }
        return true;    // A-OK
    }

    bool File::MoveLeft(int spaces) {
        // Move left one space - if we are on the first place, go to previous line if it exists
        for(int i = 0; i < spaces; i++) {
            // If we are at the last position of this line, try to go to the next line.
            if(_pos.col == 0) {
                // If we are also on the first line
                if(_pos.line == 0) {
                    return false;
                }
                _pos.line--;
                _pos.col = _contents[_pos.line].length()-1;
            }
            else {
                _pos.col--;
            }
        }
        return true;    // A-OK
    }

    char File::ReadChar() const {
        // Return char only if valid
        if(_pos.line < _contents.size() && _pos.col < _contents[_pos.line].length()) {
            return _contents[_pos.line][_pos.col];
        }
        // Else we are at end of file
        return EOF;
    }

    std::string File::ReadLine() const {
        // Return only if valid
        if(_pos.line < _contents.size()) {
            return _contents[_pos.line];
        }
        return "(EOF)";
    }

    std::string File::PrintAllContents() const {
        std::ostringstream os;
        os << "[" << _fname << "]:" << std::endl;
        // Separate stream used to properly format numbers
        std::ostringstream numStream;
        size_t t = _contents.size();
        size_t width = 1;
        if(t >= 10) { width = 2; }
        else if(t >= 100) { width = 3; }
        numStream.width(width);

        for(size_t i = 0; i < t; i++) {
            // This formatting is so it looks pretty
            numStream << (i+1);
            os << numStream.str() << "|" << _contents[i] << std::endl;
            numStream.str("");
            numStream.width(width);
        }
        return os.str();
    }

};
