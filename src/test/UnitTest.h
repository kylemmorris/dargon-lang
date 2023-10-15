/*
 * Dargon Programming Language
 * (C) Kyle Morris 2023 - See LICENSE.txt for license information.
 *
 * FILE: UnitTest.h
 *
 * DESCRIPTION: Represents a single Unit Test. All Unit Tests have one test method,
 *              but can share functionalty such as assert and comparison.
 *
 * SINCE: v0.1
 *
 */

#ifndef DARGON_UNIT_TEST_H
#define DARGON_UNIT_TEST_H

#include <string>
#include "../core/FilePosition.h"

namespace dargon {

    /**
     * @brief Struct representing a test result.
     * @author Kyle Morris
     * @since v0.1
    */
    class TestResult {
    public:
        /**
        * @brief Constructor with name of test.
        */
        TestResult(const std::string& name) : testName(name) {}
        /**
        * @brief Repors the test result.
        */
        std::string Report() const {
            std::ostringstream os;
            os << testName << ": ";
            if(passed == total) {
                os << "PASS";
            }
            else {
                os << "FAIL " << std::endl;
                os << "REASON -> " << reason << std::endl;
            }
            return os.str();
        }

        /**
        * @brief Asserts that a given expression is true.
        * If not, a reason for failure is provided.
        */
        inline void Assert(bool inp, const std::string& errstr, const FilePosition& pos) {
            if(inp) {
                passed++;
            }
            else {
                reason = errstr + "at " + pos.ToString() + "; " + reason;
            }
            total++;
        }
    private:
        std::string testName = "";
        int passed = 0;
        int total = 0;
        std::string reason = "";
    };

	/**
     * @brief Represents a single Unit Test.
     * @author Kyle Morris
     * @since v0.1
    */
	class UnitTest {
	public:
        virtual TestResult Test() = 0;
    protected:
        TestResult _result;
	};

};

#endif
