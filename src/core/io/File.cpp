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
#include <iomanip>
#include <sys/stat.h>
#include "File.h"
#include "../Utility.h"
#include "Log.h"

namespace dargon {

    File::File() {}

    File::~File() {
        Close();
    }

    bool File::OpenAbsolute(const Path& path) {
        if(File::Exists(path)) {
            Close();
            _path = path;
            std::ifstream file(path.GetFull());
            if(file.is_open()) {
                // TODO: Optimize for larger files.
                // Copy entire contents of file
                std::string line;
                while(std::getline(file, line)) {
                    line = line + "\n"; // Add newline to end
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

    bool File::OpenRelative(const Path& relPath) {
        Close();
        // TODO
        //DARGON_LOG_ERROR("OpenRelative is not implemented yet.");
        return true;
    }

    void File::BufferRawData(std::string& data) {
        Close();
        _path = Path("");
        // Segment by lines
        _contents = SegmentString(data, '\n');
    }

    void File::Close() {
        _contents.clear();
        Reset();
    }

    const FilePosition& File::CurrentPosition() const {
        // Internally we index by 0 - for the user, they expect
        // line 1, column 1 to the be the origin.
        //FilePosition ret = _pos;
        //ret.line++;
        //ret.col++;
        //return ret;
        return _pos;
    }

    std::string File::ShowPosition() const {
        std::ostringstream os;
        os << _path.GetFileName() << " @ " << CurrentPosition().ToString();
        return os.str();
    }

    std::string File::ShowExactPosition() const {
        // Sanity check
        if(!_pos.Valid()) {
            std::string s = "File::ShowExactPosition() - File's current position was invalid.";
            DARGON_LOG_ERROR(s.c_str());
            return s;
        }
        // If EOF, just return nothing
        if(isEOF()) {
            return "[EOF]";
        }
        // Separate stream used to properly format numbers
        std::ostringstream numStream;
        size_t t = (size_t)_pos.line;
        size_t width = 1;
        if(t >= 10) { width = 2; }
        else if(t >= 100) { width = 3; }
        numStream.width(width);
        numStream << t << "|";
        std::string num = numStream.str();

        std::ostringstream os;
        //os << ShowPosition() << std::endl;
        std::string pos;
        try {
            pos = _contents.at(_pos.line); // Do this to not display newline in output
        }
        catch(std::out_of_range& e) {
            std::string s = "File::ShowExactPosition() - File's current position was out of the range of the file: " + _pos.ToString();
            DARGON_LOG_ERROR(s.c_str());
            return s;
        }
        //std::string pos = _contents[_pos.line]; // Do this to not display newline in output
        //os << "[" << _path.GetFileName() << "]" << std::endl;
        os << num << pos.substr(0, pos.length()) << std::endl;
        size_t tot = (size_t)_pos.col + num.length();
        for(size_t i = 0; i < tot; i++) {
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
            if(isEOF()) {
                return false;
            }
            _pos.line++;
            _pos.col = 0;
        }
        return true;
    }

    bool File::MoveRight(int spaces) {
        // Move right one space - if we are on the last place, go to next line
        for(int i = 0; i < spaces; i++) {
            // If we are at the last position of this line, try to go to the next line.
            if((size_t)_pos.col == (_contents[_pos.line].length()-1)) {
                _pos.col = 0;
                _pos.line++;
                // End of file!
                if(isEOF()) {
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

    bool File::GotoLine(int exactLine) {
        if((size_t)exactLine < _contents.size() && exactLine >= 0) {
            _pos.line = exactLine;
            return true;
        }
        return false;
    }

    bool File::GotoColumn(int exactColumn) {
        if(exactColumn < _contents[_pos.line].length() && exactColumn >= 0) {
            _pos.col = exactColumn;
            return true;
        }
        return false;
    }

    bool File::Goto(int exactLine, int exactColumn) {
        FilePosition old = CurrentPosition();
        if(GotoLine(exactLine) && GotoColumn(exactColumn)) {
            return true;
        }
        _pos = old;
        return false;
    }

    bool File::Goto(const FilePosition& pos) {
        return Goto(pos.line, pos.col);
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
        os << "[" << _path.GetFileName() << "]:" << std::endl;
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

    bool File::Exists(const Path& filePath) {
        return File::Exists(filePath.GetFull());
    }

    bool File::Exists(const std::string& filePath) {
        // Check file status before anything else.
		struct stat st = { 0 };
		if (stat(filePath.c_str(), &st) == -1) {
            //throw Exception("Could not find file: " + filePath);
			return false;
		}
		std::ifstream file;
		file.open(filePath);
		if (!file.is_open()) {
            //throw Exception("Could not open file: " + filePath);
			file.close();
			return false;
		}
		file.close();
		return true;
    }

    bool File::isEOF() const {
        return ((size_t)_pos.line == _contents.size());
    }

};
