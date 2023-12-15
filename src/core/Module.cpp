/**
 * Dargon Programming Language
 * (C) Kyle Morris 2023 - See LICENSE.txt for license information.
 *
 * @file Module.cpp
 * @author Kyle Morris
 * @since v0.1
 * @section Description
 * Contains implementation of Module header file.
 *
 */

#include "Module.h"

namespace dargon {

    std::unique_ptr<Script> Module::_runningScript(nullptr);

}
