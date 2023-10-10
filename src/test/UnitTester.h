/*
 * Dargon Programming Language
 * (C) Kyle Morris 2023 - See LICENSE.txt for license information.
 *
 * FILE: UnitTester.h
 *
 * DESCRIPTION: Runs all the Unit Tests if the DARGON_TEST flag is set.
 *
 * SINCE: v0.1
 *
 */

#ifndef DARGON_UNIT_TESTER_H
#define DARGON_UNIT_TESTER_H

#include <vector>
#include "TokenUnitTest.h"

namespace dargon {
namespace test {


	/**
     * @brief Singelton that runs all the unit tests.
     * @author Kyle Morris
     * @since v0.1
     * @see UnitTest
    */
	class UnitTester {
	public:

        /**
        * @brief Initializes all unit tests.
        */
        UnitTester()
        {
            AddUnitTest(TokenUnitTest);
        }

        /**
        * @brief Runs all unit tests.
        */
        std::string RunUnitTests() {
            std::ostringstream os;
            size_t total = _tests.size();
            for(size_t i = 0; i < total; i++) {
                os << "[" << i+1 << "/" << total << "] " << _tests[i]().Report() << std::endl;
            }
            return os.str();
        }

        /**
        * @brief Adds a unit test.
        */
        void AddUnitTest(TestFunc t) {
            _tests.push_back(t);
        }
	private:
        std::vector<TestFunc> _tests;
	};

}}; // dargon::test

#endif
