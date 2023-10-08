/*
 * Dargon Programming Language
 * (C) Kyle Morris 2023 - See LICENSE.txt for license information.
 *
 * FILE: UnitTest.h
 *
 * DESCRIPTION: Simple framework for running tests.
 *
 * SINCE: v0.1
 *
 */

#ifndef DARGON_UNIT_TEST_H
#define DARGON_UNIT_TEST_H

namespace dargon {

    /**
     * @brief Struct representing a test result.
     * @author Kyle Morris
     * @since v0.1
    */
    struct TestResult {
    };

	/**
     * @brief Superclass of all built-in tests.
     * @author Kyle Morris
     * @since v0.1
    */
	class UnitTest {
	public:
        virtual TestResult Test() noexcept = 0;
	private:
        UnitTest() {}
	};

};

#endif
