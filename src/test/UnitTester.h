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

#include <memory>
#include <vector>
#include "UnitTest.h"

namespace dargon {

    class UnitTester;

    /**
    * @brief Typedef for the unique_ptr.
    */
    typedef UnitTesterPtr std::unique_ptr<UnitTester>;

    namespace hidden {
        static UnitTesterPtr _unitTester;
    };

	/**
     * @brief Runs all the unit tests if DARGON_TEST is set.
     * @author Kyle Morris
     * @since v0.1
     * @see UnitTest
    */
	class UnitTester {
	public:
        static UnitTesterPtr Get() {
            if(hidden::_unitTester == nullptr) {
                hidden::_unitTester.reset(new UnitTester());
            }
            return hidden::_unitTester;
        }
        void AddUnitTest(UnitTest* t) {
            _test.push_back(t);
        }
	private:
        std::vector<UnitTest*> _tests;
	};

};

#endif
