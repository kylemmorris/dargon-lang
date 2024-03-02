/**
 * Dargon Programming Language
 * (C) Kyle Morris 2023 - See LICENSE.txt for license information.
 *
 * @file VMInstruction.cpp
 * @author Kyle Morris
 * @since v0.1
 * @section Description
 * Implementation of VMInstruction.h
 *
 */

#include "VMInstruction.h"

namespace dargon {

    void VMInstruction::grow() {
        int old_capacity = m_capacity;
        m_capacity = (m_capacity < 8) ? 8 : m_capacity * 2;
        m_code = (byte*)Reallocate(m_code, old_capacity, m_capacity);
    }

    VMInstruction::~VMInstruction() {
        free(m_code);
    }

    void VMInstruction::Append(const byte& inByte) {
        if(m_capacity < m_count + 1) {
            grow();
        }
        m_code[m_count] = inByte;
        m_count++;
    }

}
