/*
 * Dargon Programming Language
 * (C) Kyle Morris 2023 - See LICENSE.txt for license information.
 *
 * FILE: TestingMacros.h
 *
 * DESCRIPTION: Contains macro definitions for testing.
 *
 * SINCE: v0.1
 *
 */

#ifndef DARGON_TEST_MACROS_H
#define DARGON_TEST_MACROS_H

#include "UnitTest.h"

namespace dargon {

/**
* @brief Primary macro for creating a new unit test.
*/
#define DARGON_UNIT_TEST(testName) \
class DARGON_UNIT_TEST_##testName## : public UnitTest { \
public:\
    DARGON_UNIT_TEST_##testName##() {\
        _result.name = "##testName##";\
    }\
    virtual TestResult Test() override


#define DARGON_TEST_ASSERT(boolExpr) \
    _result.Assert(boolExpr, ##boolExpr##, DARGON_FILE_POSITION)


};

#endif
