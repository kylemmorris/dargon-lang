/**
 * Dargon Programming Language
 * (C) Kyle Morris 2023 - See LICENSE.txt for license information.
 *
 * @file TestingMacros.h
 * @author Kyle Morris
 * @since v0.1
 * @section Description
 * Contains the unit test macros used in all unit tests.
 *
 */

#ifndef DARGON_HEADER_TESTMACROS
#define DARGON_HEADER_TESTMACROS

#include "UnitTest.h"

namespace dargon {

/**
* @brief Primary macro for creating a new unit test.
*/
#define DARGON_UNIT_TEST(testName, body) \
class DARGON_UNIT_TEST_##testName## : public UnitTest { \
public:\
    DARGON_UNIT_TEST_##testName##() : UnitTest() {\
        _result.name = "##testName##";\
    }\
    virtual TestResult Test() override { body }};


#define DARGON_TEST_ASSERT(boolExpr) \
    _result.Assert(boolExpr, ##boolExpr##, DARGON_FILE_POSITION)


};

#endif
