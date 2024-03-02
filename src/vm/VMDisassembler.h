/**
 * Dargon Programming Language
 * (C) Kyle Morris 2023 - See LICENSE.txt for license information.
 *
 * @file VMDisassembler.h
 * @author Kyle Morris
 * @since v0.1
 * @section Description
 * Contains a disassembler for debugging VM bytecode.
 *
 */

#ifndef DARGON_HEADER_VM_DISASSEMBLER
#define DARGON_HEADER_VM_DISASSEMBLER

#include "VMInstruction.h"

namespace dargon {

	/// @brief Dissassembles Virtual Machine (VM) instructions.
	/// Currently used for debugging.
	/// @author Kyle Morris
	/// @since v0.1
	class VMDissasembler {
	private:
        int disassembleInstruction(const VMInstruction& data, const char* name, int offset);
	public:
        void Disassemble(const VMInstruction& data, const char* name);
	};

};

#endif
