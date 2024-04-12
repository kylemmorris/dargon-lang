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
#include "../core/Exception.h"

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
        inline byte read_byte() { return *m_ip++; }
        inline value read_constant() {
            value ret;
            if(m_nugget->m_constants.Get(read_byte(), ret)) {
                return ret;
            }
            throw new Exception(dargon::ErrorCode::INTERNAL_ERROR, "Could not read constant.");
        }
        void binary_op(const vm::OPCODE& code);
        Result run();
    public:
        VirtualMachine();
        ~VirtualMachine();
        Result Interpret(Nugget* nugget);
    };

}};

#endif
