/**
 * Dargon Programming Language
 * (C) Kyle Morris 2023 - See LICENSE.txt for license information.
 *
 * @file
 * @author Kyle Morris
 * @since v0.1
 * @section Description
 *
 *
 */

#include <iomanip>
#include "Nugget.h"
#include "../core/io/IO.h"

namespace dargon {
namespace vm {

    Nugget::Nugget(const char* name) : m_name(name) {}

    int Nugget::AddConst(const value& val) {
        m_constants.Write(val);
        return m_constants.m_count- 1;
    }

    void Nugget::Disassemble() {
        std::ostringstream os;
        vm::OPCODE op;
        os << "\n== NUGGET: " << m_name << " ==\n";
        for(int offset = 0; offset < m_count;) {
            os << std::setw(4) << std::setfill('0') << offset << "    ";
            op = static_cast<vm::OPCODE>(m_data[offset]);
            switch(op) {
                case vm::OPCODE::RETURN: {
                    os << "RETURN   ";
                    offset = offset + 1;
                    break;
                }
                case vm::OPCODE::CONSTANT: {
                    byte const_index = m_data[offset + 1];
                    os << "CONSTANT " << m_constants.m_data[const_index] << " (" << static_cast<int>(const_index) << ")";
                    offset = offset + 2;
                    break;
                }
                case vm::OPCODE::NEGATE: {
                    os << "NEGATE   ";
                    offset = offset + 1;
                    break;
                }
                case vm::OPCODE::ADD: os << "ADD      "; offset++; break;
                case vm::OPCODE::SUBTRACT: os << "SUBTRACT "; offset++; break;
                case vm::OPCODE::MULTIPLY: os << "MULTIPLY "; offset++; break;
                case vm::OPCODE::DIVIDE: os << "DIVIDE   "; offset++; break;
                default: {
                    os << "UNKNOWN";
                }
            }
            os << "\n";
        }
        os << "== END ==\n";
        dargon::out(os.str());
    }

}};
