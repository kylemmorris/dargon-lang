/**
 * Dargon Programming Language
 * (C) Kyle Morris 2023 - See LICENSE.txt for license information.
 *
 * @file Common.h
 * @author Kyle Morris
 * @since v0.1
 * @section Description
 * Commonalities between all VM components.
 * Part of the DVM, the Dargon Virtual Machine.
 *
 */

#ifndef DARGON_HEADER_VM_COMMON
#define DARGON_HEADER_VM_COMMON

#include <cstdint>
#include <cstddef>
#include "../core/Exception.h"

namespace dargon {
namespace vm {

	/// @brief Bytes are represented as unsigned 8-bit integers.
	typedef uint8_t byte;

	/// @brief TODO
	typedef double value;

	/// @brief Maximum amount for a given stack.
	#define STACK_MAX 256

	/// @brief Resizes a given chunk of memory.
    void* Reallocate(void* ptr, size_t oldSz, size_t newSz);

}};

#endif
