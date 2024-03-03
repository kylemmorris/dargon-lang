/**
 * Dargon Programming Language
 * (C) Kyle Morris 2023 - See LICENSE.txt for license information.
 *
 * @file DynamicArray.h
 * @author Kyle Morris
 * @since v0.1
 * @section Description
 * Custom made dynamic array.
 *
 */

#ifndef DARGON_HEADER_VM_DYNAMICARRAY
#define DARGON_HEADER_VM_DYNAMICARRAY

#include <vector>
#include "Common.h"

namespace dargon {
namespace vm {

	/// @brief Represents a dynamically-resizable array used for multiple typedefs.
	/// @author Kyle Morris
	/// @since v0.1
	template<typename T>
	class DynamicArray {
	public:
        int m_count;
        int m_capacity;
        T*  m_data;
        void grow() {
            int old_capacity = m_capacity;
            m_capacity = (m_capacity < 8) ? 8 : m_capacity * 2;
            m_data = (T*)Reallocate(m_data, old_capacity, m_capacity);
        }
        DynamicArray() : m_data(nullptr), m_count(0), m_capacity(0) {}
        virtual ~DynamicArray() { free(m_data); }
        void Write(const T& data) {
            if(m_capacity < m_count + 1) { grow(); }
            m_data[m_count] = data;
            m_count++;
        }
	};

}};

#endif
