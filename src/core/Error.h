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

namespace dargon {

	/// @brief The error codes used throughout the program.
	/// @author Kyle Morris
	/// @since v0.1
	enum class ECode : int32_t {
        NO_ERROR = 0
	};

	/// @brief A simple error structure.
	/// @author Kyle Morris
	/// @since v0.1
	struct Error {
        ECode code;
        const char* msg;
	};

};

#endif
