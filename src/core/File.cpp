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

#include "File.h"
#include "Utility.h"

namespace dargon {

    File::File() _file(), _fname(""), _pos(0,0) {}

    File::~File() {
        Close();
    }

    bool File::OpenAbsolute(const std::string& path) {
        if(FileExists(path)) {
            _file.open(path);
            _fname = GetFilename(path, true);
            Reset();
            return true;
        }
        return false;
    }

    bool File::OpenRelative(const std::string& relPath) {
        return true;
    }

    void File::Close() {
        _file.close();
    }

    FilePosition File::CurrentPosition() {
        // Internally we index by 0 - for the user, they expect
        // line 1, column 1 to the be the origin.
        FilePosition ret = _pos;
        ret.line++;
        ret.col++;
        return ret;
    }

    void File::Reset() {
        // Rewind to start of file
        _file.seekg(0);
        // Internally, we use 0-based to keep things simple
        _pos = FilePosition(0,0);
    }



};
