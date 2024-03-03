/**
 * Dargon Programming Language
 * (C) Kyle Morris 2023 - See LICENSE.txt for license information.
 *
 * @file Stack.h
 * @author Kyle Morris
 * @since v0.1
 * @section Description
 * A simple stack implementation that allows for an
 * allocated size.
 *
 */

#ifndef DARGON_HEADER_VM_STACK
#define DARGON_HEADER_VM_STACK

#include "Common.h"
#include "../core/io/IO.h"

namespace dargon {
namespace vm {

    /// @brief A simple stack template that includes pre-allocated memory space.
    /// @author Kyle Morris
    /// @since v0.1
    template<typename T, int N>
    class Stack {
    private:
        T m_stack[N];
        T* m_top;
    public:
        Stack() {
            Reset();
        }
        void Push(const T& val) {
            *m_top = val;
            m_top++;
        }
        T Pop() {
            m_top--;
            return *m_top;
        }
        void Reset() {
            m_top = m_stack; // Goes right to beginning.
        }
        /// @brief Prints contents to DARGON_OUT.
        void Print() {
            for(T* slot = m_stack; slot < m_top; slot++) {
                DARGON_OUT << "[" << *slot << "]\n";
            }
        }
    };

}};

#endif
