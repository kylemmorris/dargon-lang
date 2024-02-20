/**
 * Dargon Programming Language
 * (C) Kyle Morris 2023 - See LICENSE.txt for license information.
 *
 * @file ConfigFile.h
 * @author Kyle Morris
 * @since v0.1
 * @section Description
 * Configuration file for Dargon.
 *
 */

#ifndef DARGON_HEADER_CONFIGFILE
#define DARGON_HEADER_CONFIGFILE

#include <string>
#include <map>
#include "File.h"

namespace dargon {

    /// @brief Type in configuration files
    enum class ConfigType {
        INT,
        STRING,
        BOOLEAN
    };

	/// @brief Configuration file.
	/// @author Kyle Morris
	/// @since v0.1
	class ConfigFile : public File {
	private:
        struct param {
            std::string name;
            ConfigType type;
            std::string value;
            bool required;
            std::string default_value;
        };
        std::map<std::string, param> m_params;
	public:
        /// @brief Returns true on success, false otherwise.
        /// 'feedback' will be set when false is returned.
        bool Parse(std::string& feedback);

        void AddParam(const std::string& name, const ConfigType& type, bool required = false, const std::string& default_value = "");
        bool ParamExists(const std::string& name) const;

        bool TryGetInt(const std::string& name, int& outInt) const;
        bool TryGetString(const std::string& name, std::string& outStr) const;
        bool TryGetBool(const std::string& name, bool& outBool) const;
	};

};

#endif
