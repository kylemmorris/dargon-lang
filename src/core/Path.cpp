/**
 * Dargon Programming Language
 * (C) Kyle Morris 2023 - See LICENSE.txt for license information.
 *
 * @file Path.cpp
 * @author Kyle Morris
 * @since v0.1
 * @section Description
 * Implementation of Path.h
 *
 */

#include "Path.h"

namespace dargon {

    Path::Path(const std::string& path)
    : _full(path), _fnameNoExt(), _fname(), _ext(), _type(Extension::INVALID)
    {
        // Get file name
        // Go from "home/kmorris/Desktop/test.dargon" to "test.dargon"
        std::string ret = path;
        if(!ret.empty()) {
            // "home/kmorris/Desktop/test.dargon"
            size_t slash = ret.find('/');
            while(slash != std::string::npos) {
                ret.erase(ret.begin(), ret.begin() + slash + 1);
                slash = ret.find('/');
            }
            // Is now "test.dargon"
            _fname = ret;
            // Split and get name without extension + extension
            size_t ext = ret.find('.'); // Only looks for first period
            _fnameNoExt = ret.substr(0,ext);
            _ext = ret.substr(ext+1);
            // Set the type
            if(_ext == "dargon") {
                _type = Extension::DARGON;
            }
            else if(_ext == "dargconf") {
                _type = Extension::DARGON_CONFIG;
            }
            // Set to UNKNOWN otherwise
        }
    }

    Path::~Path() {}

    std::string Path::GetFull() const {
        return _full;
    }

    std::string Path::GetFilenNameNoExt() const {
        return _fnameNoExt;
    }

    std::string Path::GetFileName() const {
        return _fname;
    }

    Path::Extension Path::GetFileExtension() const {
        return _type;
    }

};
