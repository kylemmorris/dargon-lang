/**
 * Dargon Programming Language
 * (C) Kyle Morris 2023 - See LICENSE.txt for license information.
 *
 * @file Error.h
 * @author Kyle Morris
 * @since v0.1
 * @section Description
 * The Error header includes a proper definition of errors that
 * will be tracked by DIR.
 *
 */

#ifndef DARGON_HEADER_ERROR
#define DARGON_HEADER_ERROR

#include <sstream>
#include "FilePosition.h"

namespace dargon {

	/// @brief The error codes used throughout the program.
	/// @author Kyle Morris
	/// @since v0.1
	enum class ECode : int32_t {
        NO_ERROR = 0x0,
        INVALID_TOKEN = 0xC01
	};

	/// @brief A simple error structure.
	/// @author Kyle Morris
	/// @since v0.1
	struct Error {
        ECode code;
        std::string msg;
        FilePosition where;

        Error() : code(ECode::NO_ERROR), msg(""), where() {}
        Error(ECode inCode, std::string inMsg) : code(inCode), msg(inMsg), where() {}
        bool IsError() const { return code != ECode::NO_ERROR; }
        std::string ToString() const {
            std::ostringstream os;
            os << (int)code << ":" << msg << std::endl << where.ToString() << std::endl;
            return os.str();
        }
	};

	//Exception* BuildException()

};

#endif
