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

    void VirtualMachine::binary_op(const vm::OPCODE& code) {
        value a = m_stack.Pop();
        value b = m_stack.Pop();
        switch(code) {
            case vm::OPCODE::ADD: m_stack.Push(a + b); break;
            case vm::OPCODE::SUBTRACT: m_stack.Push(a - b); break;
            case vm::OPCODE::MULTIPLY: m_stack.Push(a * b); break;
            case vm::OPCODE::DIVIDE: m_stack.Push(a / b); break;
            default:
                break;
        };
    }

    Result VirtualMachine::run() {
        #ifdef DARGON_VERSION_DEBUG
        m_stack.Print();
        m_nugget->Disassemble();
        #endif
        vm::byte instruction;
        vm::OPCODE current_code;
        for(;;) {
            instruction = read_byte();
            current_code = static_cast<vm::OPCODE>(instruction);
            switch(current_code) {
                case vm::OPCODE::RETURN: {
                    DARGON_OUT << m_stack.Pop() << "\n";
                    return Result::OK;
                }
                case vm::OPCODE::CONSTANT: {
                    vm::value constant = read_constant();
                    m_stack.Push(constant);
                    break;
                }
                case vm::OPCODE::NEGATE: {
                    m_stack.Push(-m_stack.Pop());
                    break;
                }
                case vm::OPCODE::ADD:
                case vm::OPCODE::SUBTRACT:
                case vm::OPCODE::MULTIPLY:
                case vm::OPCODE::DIVIDE: {
                    binary_op(current_code);
                    break;
                }
                default: {
                    return Result::INTERNAL_ERROR;
                }
            }
        }
        return Result::INTERNAL_ERROR;
    }

}};
