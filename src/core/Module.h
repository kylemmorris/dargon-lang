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

        /// @brief Adds an error to the error stack.
        static void AddError(const ECode& code, const char* msg) {
            Error e;
            e.code = code;
            e.msg = msg;
            _errors.push(e);
        }

        /// @brief Returns true if an error occured.
        static bool ErrorOccured() {
            return !_errors.empty();
        }

        /// @brief Sets the current Dargon script that will be used by all modules
        /// i.e. parts of the interpreter.
        /// @param scriptPath - Path to the script to load.
        static bool SetCurrentScript(const Path& scriptPath) {
            _runningScript.reset(new Script);
            if(_runningScript->OpenAbsolute(scriptPath)) {
                DARGON_LOG_INFO(_runningScript->PrintAllContents());
                return true;
            }
            else {
                DARGON_LOG_ERROR("Couldn't open file: " + scriptPath.GetFull());
            }
            return false;
        }
	protected:
        /// @brief A ref to the current script being interpreted.
        static std::unique_ptr<Script> _runningScript;

        /// @brief The stack of errors.
        static std::stack<Error> _errors;

	};

};

#endif
