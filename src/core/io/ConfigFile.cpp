/**
 * Dargon Programming Language
 * (C) Kyle Morris 2023 - See LICENSE.txt for license information.
 *
 * @file ConfigFile.cpp
 * @author Kyle Morris
 * @since v0.1
 * @section Description
 * Implementation of ConfigFile.h
 *
 */

#include <cmath>
#include <set>
#include <algorithm>
#include <sstream>
#include "ConfigFile.h"
#include "../Utility.h"

namespace dargon {

    bool ConfigFile::Parse(std::string& feedback) {
        feedback = "";
        std::ostringstream os;
        std::string line;
        std::vector<std::string> nvPair;
        std::set<param> visitedParams;
        // Just 'name=value' for each line.
        for(size_t i = 0; i < _contents.size(); ++i) {
            line = _contents[i];
            RemoveFromString(line, ' ');
            RemoveFromString(line, '\t');
            if(line.empty() || line[0] == '#') { continue; }
            nvPair = SegmentString(_contents[i], '=');
            if(nvPair.size() != 2 || nvPair.at(0).size() == 0 || nvPair.at(1).size() == 0) {
                Goto(i, 0);
                os << "Improper line formatting:\n" << ShowExactPosition() << "\n";
                feedback = os.str();
                return false;
            }
            if(m_params.find(nvPair.at(0)) == m_params.end()) {
                int p = std::floor(nvPair.at(0).size() / 2);
                Goto(i, p);
                os << "Unknown configuration parameter:\n" << ShowExactPosition() << "\n";
                feedback = os.str();
                return false;
            }
            m_params[nvPair.at(0)].value = nvPair.at(1);
            visitedParams.insert(m_params[nvPair.at(0)]);
        }
        // Ensure all required parameters exist
        for(const auto& kvp : m_params) {
            if(visitedParams.find(kvp.second) == visitedParams.end()) {
                os << "Missing required configuration parameter: " << kvp.first << "\n";
                feedback = os.str();
                return false;
            }
        }
        // Set to default all parameters that were not included
        for(auto& kvp : m_params) {
            if(kvp.second.required) { continue; }
            if(visitedParams.find(kvp.second) == visitedParams.end()) {
                kvp.second.value = kvp.second.default_value;
            }
        }
        return true;
    }

    void ConfigFile::AddParam(const std::string& name, const ConfigType& type, bool required, const std::string& default_value) {
        if(m_params.find(name) != m_params.end() || type == ConfigType::NONE) { return; }
        param p;
        p.name = name;
        p.type = type;
        p.required = required;
        p.default_value = default_value;
        m_params.insert(std::make_pair(name, p));
    }

    bool ConfigFile::ParamExists(const std::string& name) const {
        return m_params.find(name) != m_params.end();
    }

    bool ConfigFile::TryGetInt(const std::string& name, int& outInt) const {
        try {
            const param& p = m_params.at(name);
            if(p.type != ConfigType::INT) { return false; }
            outInt = std::stoi(p.value);
            return true;
        }
        catch(...) {}
        return false;
    }

    bool ConfigFile::TryGetString(const std::string& name, std::string& outStr) const {
        try {
            const param& p = m_params.at(name);
            if(p.type != ConfigType::STRING) { return false; }
            outStr = p.value;
            return true;
        }
        catch(...) {}
        return false;
    }

    bool ConfigFile::TryGetBool(const std::string& name, bool& outBool) const {
        try {
            const param& p = m_params.at(name);
            if(p.type != ConfigType::BOOLEAN) { return false; }
            // All lower case
            std::string data = p.value;
            std::transform(data.begin(), data.end(), data.begin(),
                [](unsigned char c){ return std::tolower(c); });
            if(data == "true") { outBool = true; return true; }
            if(data == "false") { outBool = false; return true; }
        }
        catch(...) {}
        return false;
    }
};
