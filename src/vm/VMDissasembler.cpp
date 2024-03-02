/**
 * Dargon Programming Language
 * (C) Kyle Morris 2023 - See LICENSE.txt for license information.
 *
 * @file VMDisassembler
 * @author Kyle Morris
 * @since v0.1
 * @section Description
 *
 *
 */

#include "VMDisassembler.h"
#include "../core/io/IO.h"
#include <iomanip>

namespace dargon {

    int VMDissasembler::disassembleInstruction(const VMInstruction& data, const char* name, int offset) {
        DARGON_OUT << std::setw(4) << std::setfill('0') << offset;
        const VMOpCode& instruction = (VMOpCode)data.At(offset);
        switch(instruction) {
            case VMOpCode::OP_RETURN:
                DARGON_OUT << " " << "OP_RETURN";
                return offset + 1;
            default:
                DARGON_OUT << "Unknown Opcode: " << (byte)instruction << "\n";
                return offset + 1;
        }
        return offset + 1;
    }

    void VMDissasembler::Disassemble(const VMInstruction& data, const char* name) {
        DARGON_OUT << "== " << name << " ==\n";
        for(int offset = 0; offset < data.GetCount();) {
            offset = disassembleInstruction(data, name, offset);
        }
    }

};
