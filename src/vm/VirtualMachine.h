/**
 * Dargon Programming Language
 * (C) Kyle Morris 2023 - See LICENSE.txt for license information.
 *
 * @file VirtualMachine.h
 * @author Kyle Morris
 * @since v0.1
 * @section Description
 * Contains the virtual machine (VM).
 *
 */

#ifndef DARGON_HEADER_VM
#define DARGON_HEADER_VM

#include "Nugget.h"
#include "Stack.h"

namespace dargon {
namespace vm {

    /// @brief The result of running the virtual machine.
	enum class Result {
        OK,
        COMPILE_ERROR,
        RUNTIME_ERROR,
        INTERNAL_ERROR
	};

	/// @brief The Dargon Virtual Machine (VM).
	/// @author Kyle Morris
	/// @since v0.1
	class VirtualMachine {
	private:
        Nugget* m_nugget;
        byte* m_ip;     // Instruction Pointer
        Stack<value,STACK_MAX> m_stack;
        Result run();
	public:
        VirtualMachine();
        ~VirtualMachine();
        Result Interpret(Nugget* nugget);
	};

}};

#endif
