/**
 * Dargon Programming Language
 * (C) Kyle Morris 2023 - See LICENSE.txt for license information.
 *
 * @file path.cpp
 * @author Kyle Morris
 * @since v0.1
 * @section Description
 * Implementation of path.h
 *
 */

#include "Path.h"

namespace dargon {

    Path::Path()
        : m_full(""), m_name(""), m_name_noext(""), m_ext(""),
        m_type(FileType::UNKNOWN)
    {}

    Path::Path(const std::string& path)
        : m_full(path), m_name(""), m_name_noext(""), m_ext(""),
        m_type(FileType::UNKNOWN)
    {
        init();
    }

    Path::Path(const char* path)
        : m_full(path), m_name(""), m_name_noext(""), m_ext(""),
        m_type(FileType::UNKNOWN)
    {
        init();
    }

    void Path::init() {
        std::string s = m_full;
        if(!s.empty()) {
            size_t slash_loc = s.find(m_slash);
            while(slash_loc != std::string::npos) {
                s.erase(s.begin(), s.begin() + slash_loc + 1);
                slash_loc = s.find(m_slash);
            }
            m_name = s;
            // TODO: Only looks for first extension
            size_t ext_loc = s.find('.');
            if(ext_loc != std::string::npos) {
                m_name_noext = s.substr(0, ext_loc);
                m_ext = s.substr(ext_loc+1);
                if(m_ext == "dargon") { m_type = FileType::SOURCE; }
                else if(m_ext == "snoot") { m_type = FileType::CONFIG; }
            }

        }
    }

    const std::string& Path::GetFull() const {
        return m_full;
    }

    const std::string& Path::GetFileName(bool extension) const {
        return extension ? m_name : m_name_noext;
    }

    const std::string& Path::GetFileExtension() const {
        return m_ext;
    }

    const FileType& Path::GetFileType() const {
        return m_type;
    }

};
