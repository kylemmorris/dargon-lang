/**
 * Dargon Programming Language
 * (C) Kyle Morris 2023 - See LICENSE.txt for license information.
 *
 * @file VirtualMachine.cpp
 * @author Kyle Morris
 * @since v0.1
 * @section Description
 * Implementation of VirtualMachine.h
 *
 */

#include "VirtualMachine.h"
#include "../core/io/IO.h"
#include "../core/Version.h"

namespace dargon {
namespace vm {

    VirtualMachine::VirtualMachine() {}

    VirtualMachine::~VirtualMachine() {}

    Result VirtualMachine::Interpret(Nugget* nugget) {
        m_nugget = nugget;
        m_ip = nugget->m_data;
        return run();
    }

    Result VirtualMachine::run() {
        #define READ_BYTE() *m_ip++
        #define READ_CONSTANT() (m_nugget->m_constants.m_data[READ_BYTE()])
        #define BINARY_OP(op) \
            do { \
               value b = m_stack.Pop();\
               value a = m_stack.Pop();\
               m_stack.Push(a op b);\
            } while(false)

        #ifdef DARGON_VERSION_DEBUG
        m_stack.Print();
        m_nugget->Disassemble();
        #endif
        vm::byte instruction;
        for(;;) {
            instruction = READ_BYTE();
            switch(static_cast<vm::OPCODE>(instruction)) {
                case vm::OPCODE::RETURN: {
                    DARGON_OUT << m_stack.Pop() << "\n";
                    return Result::OK;
                }
                case vm::OPCODE::CONSTANT: {
                    vm::value constant = READ_CONSTANT();
                    m_stack.Push(constant);
                    break;
                }
                case vm::OPCODE::NEGATE: {
                    m_stack.Push(-m_stack.Pop());
                    break;
                }
                case vm::OPCODE::ADD: BINARY_OP(+); break;
                case vm::OPCODE::SUBTRACT: BINARY_OP(-); break;
                case vm::OPCODE::MULTIPLY: BINARY_OP(*); break;
                case vm::OPCODE::DIVIDE: BINARY_OP(/); break;
                default: {
                    return Result::INTERNAL_ERROR;
                }
            }
        }
        return Result::INTERNAL_ERROR;
        #undef READ_BYTE
        #undef READ_CONSTANT
        #undef BINARY_OP
    }

}};
