/**
 * Dargon Programming Language
 * (C) Kyle Morris 2023 - See LICENSE.txt for license information.
 *
 * @file Instruction.h
 * @author Kyle Morris
 * @since v0.1
 * @section Description
 * Represents an instruction of bytecode.
 *
 */

#ifndef DARGON_HEADER_VM_INSTRUCTION
#define DARGON_HEADER_VM_INSTRUCTION

#include <vector>
#include "VMCommon.h"

namespace dargon {

	/// @brief Operation Code (OPCODE).
	enum class VMOpCode : byte {
        OP_RETURN
	};

	/// @brief Represents an instruction (list of bytes) in the Virtual Machine (VM).
	/// @author Kyle Morris
	/// @since v0.1
	class VMInstruction {
	private:
        byte* m_code;
        int m_count;
        int m_capacity;
        inline void grow();
	public:
        VMInstruction() : m_code(nullptr), m_count(0), m_capacity(0) {}
        ~VMInstruction();
        void Append(const byte& inByte);
        const byte& At(const int& ind) const { return m_code[ind]; }
        int GetCount() const { return m_count; }
	};

};

#endif
