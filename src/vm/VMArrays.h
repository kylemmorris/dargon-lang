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

	/// @brief Represents a dynamically-resizable list used for multiple typedefs.
	/// @author Kyle Morris
	/// @since v0.1
	template<typename T>
	class VMDynamicArray {
    private:
        T*  m_code;
        int m_count;
        int m_capacity;
        inline void grow() {
            int old_capacity = m_capacity;
            m_capacity = (m_capacity < 8) ? 8 : m_capacity * 2;
            m_code = (T*)Reallocate(m_code, old_capacity, m_capacity);
        }
    public:
        VMDynamicArray() : m_code(nullptr), m_count(0), m_capacity(0) {}
        ~VMDynamicArray() {
            free(m_code);
        }
        void Append(const T& data) {
            if(m_capacity < m_count + 1) {
                grow();
            }
            m_code[m_count] = data;
            m_count++;
        }
        const T& At(const int& ind) const { return m_code[ind]; }
        int GetCount() const { return m_count; }
	};

	typedef VMDynamicArray<byte> VMInstruction;
	typedef VMDynamicArray<double> VMValueArray;

};

#endif
