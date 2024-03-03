/**
 * Dargon Programming Language
 * (C) Kyle Morris 2023 - See LICENSE.txt for license information.
 *
 * @file VMCommon.h
 * @author Kyle Morris
 * @since v0.1
 * @section Description
 *
 *
 */

#include "Common.h"

namespace dargon {
namespace vm {

    void* Reallocate(void* ptr, size_t oldSz, size_t newSz) {
        if(newSz == 0) {
            free(ptr);
            return nullptr;
        }
        void* res = realloc(ptr, newSz);
        if(res == nullptr) {
            throw new Exception(ErrorCode::OUT_OF_MEMORY, "COULD NOT ALLOCATE MEMORY WITHIN VM IN 'Reallocate()'");
        }
        return res;
    }

}};
