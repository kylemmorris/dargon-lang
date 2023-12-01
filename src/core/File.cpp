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

namespace dargon {

    File::File() {}

    File::~File() {
        Close();
    }

    bool File::OpenAbsolute(const std::string& path) {
        if(FileExists(path)) {
            std::ifstream file(path);
            if(file.is_open()) {
                _fname = GetFilename(path, true);
                Reset();
                return true;
            }
        }
        return false;
    }

    bool File::OpenRelative(const std::string& relPath) {
        return true;
    }

    void File::Close() {
        _file.close();
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
        os << _fname << " @ " << _pos.ToString();
        return os.str();
    }

    std::string File::ShowExactPosition() const {
        std::ostringstream os;
        os << ShowPosition() << std::endl;
        for(int i = 0; i < _pos.col-1; i++) {
            os << "-";
        }
        os << "^";
        return os.str();
    }

    void File::Reset() {
        // Rewind to start of file
        _file.seekg(0);
        // Internally, we use 0-based to keep things simple
        _pos = FilePosition(0,0);
        _char = ' ';
    }

    bool File::MoveRight(unsigned int spaces) {
        // The file is simply a stream of characters.
        // It's up to use to decide when to go to the next line.
        // See this:
        //  a = 1
        //  b = 2
        // Is technically:
        //  a = 1\nb = 2\n
        //  1234567.......
        //
        // If we're at pos 7 and move right, we enter a new line.
        // Perform the following N times
        for(unsigned int i = 1; i <= spaces; i++) {
            switch(_char) {
            case EOF:           // We're already at the end, sorry!
                return false;
            case '\n':          // We will now enter a new line
                _pos.Set(_pos.line+1, 0);
                break;
            default:            // Else, just move
                _file.get(_char);
                _pos.col++;
            }
        }
        return true;
    }

    bool File::MoveLeft(unsigned int spaces) {
        // The file is simply a stream of characters.
        // It's up to use to decide when to go to the previous line.
        // See this:
        //  a = 1
        //  b = 2
        // Is technically:
        //  a = 1\nb = 2\n
        //  .....1234567..
        //
        // If we're at pos 3 and move left, we go back 1 line.

        // If we're already at the beginning, can't do anything
        if(_pos.line == 0 && _pos.col == 0) {
            return false;
        }
        // Else do the following N times
        for(unsigned int i = 1; i <= spaces; i++) {

        }
        return true;
    }










};
