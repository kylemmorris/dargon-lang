/**
 * Dargon Programming Language
 * (C) Kyle Morris 2023 - See LICENSE.txt for license information.
 *
 * @file Nugget.h
 * @author Kyle Morris
 * @since v0.1
 * @section Description
 * A 'Nugget' is a single unit of DVM bytecode that contains
 * the instruction array and constant array. Synonymous to
 * a scope of bytecode.
 *
 */

#ifndef DARGON_HEADER_VM_NUGGET
#define DARGON_HEADER_VM_NUGGET

#include <sstream>
#include "DynamicArray.h"

namespace dargon {
namespace vm {

    /// @brief Operation codes defined by the DVM.
	enum class OPCODE : vm::byte {
        RETURN      = 0x00,     ///< [0x00] END
        CONSTANT    = 0x01,     ///< [0x01] [index] END
        NEGATE      = 0x02,     ///< [0x02] END
        ADD         = 0x03,     ///< [0x03] END
        SUBTRACT    = 0x04,     ///< [0x04] END
        MULTIPLY    = 0x05,     ///< [0x05] END
        DIVIDE      = 0x06,     ///< [0x06] END
	};

	/// @brief A resizable chunk of bytecode, termed a 'nugget'.
	/// @author Kyle Morris
	/// @since v0.1
    class Nugget : public DynamicArray<vm::byte> {
    protected:
        DynamicArray<value> m_constants;
        const char* m_name;
        friend class VirtualMachine;
    public:
        Nugget(const char* name);
        int AddConst(const value& data);
        //value& GetConst(int index);
        void Disassemble();
    };

}};

#endif
