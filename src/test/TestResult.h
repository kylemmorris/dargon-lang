/*
 * Dargon Programming Language
 * (C) Kyle Morris 2023 - See LICENSE.txt for license information.
 *
 * FILE: NAME.h
 *
 * DESCRIPTION:
 *
 * SINCE: v0.1
 *
 */

#ifndef DARGON_TEST_RESULT_H
#define DARGON_TEST_RESULT_H

#include <functional>
#include <string>
#include <sstream>

namespace dargon {
namespace test {

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
        inline void Assert(bool inp, const std::string& errstr) {
            if(inp) {
                passed++;
            }
            else {
                reason = errstr + "; " + reason;
            }
            total++;
        }

        /**
        * @brief Checks if two values are equal. If not,
        * a reason for failure is provided.
        */
        template<typename T>
        inline void CheckEq(const T& lhs, const T& rhs, const std::string& errstr) {
            if(lhs == rhs) {
                passed++;
            }
            else {
                reason = errstr + "; " + reason;
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
    * @brief Test function type.
    */
    typedef  std::function<TestResult()> TestFunc;


// Marker for a Dargon unit test function.
#define DARGON_UNIT_TEST static TestResult

#define DARGON_UNIT_TEST_BEGIN(str) \
    TestResult result(str);

#define DARGON_UNIT_TEST_ASSERT(expr, issue_if_wrong) \
    result.Assert(expr, issue_if_wrong);

#define DARGON_UNIT_TEST_END \
    return result;

}}; // dargon::test

#endif
