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
    : _full(path), _fnameNoExt(), _fname(), _ext()
    {

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

    std::string Path::GetFileExtension() const {
        return _ext;
    }

};
