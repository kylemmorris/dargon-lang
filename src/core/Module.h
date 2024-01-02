/**
 * Dargon Programming Language
 * (C) Kyle Morris 2023 - See LICENSE.txt for license information.
 *
 * @file Module.h
 * @author Kyle Morris
 * @since v0.1
 * @section Description
 * Module is the superclass for all of the primary modules in DIR
 * (lexer, parser, etc.). This class is used to store shared memory
 * and functionalities between the modules.
 *
 */

#ifndef DARGON_HEADER_MODULE
#define DARGON_HEADER_MODULE

#include <memory>
#include <stack>
#include "File.h"
#include "Log.h"
#include "Error.h"

namespace dargon {

	/// @brief Module is the superclass of all primary modules in DIR.
	/// @author Kyle Morris
	/// @since v0.1
	class Module {
	public:
        /// @brief Constructor
        Module() {}

        /// @brief Destructor
        virtual ~Module() {}

        /// @brief The main, abstract function for modules.
        /// @returns An Error structure.
        virtual Error Work() = 0;

	protected:
        /// @brief A ref to the current script being interpreted.
        //static std::unique_ptr<Script> _runningScript;
	};

};

#endif
