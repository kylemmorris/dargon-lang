/**
 * Dargon Programming Language
 * (C) Kyle Morris 2023 - See LICENSE.txt for license information.
 *
 * @file UnitTest.h
 * @author Kyle Morris
 * @since v0.1
 * @section Description
 * Contains the Unit Test class.
 *
 */

#ifndef DARGON_HEADER_UNIT_TEST
#define DARGON_HEADER_UNIT_TEST

#include <string>
#include "../core/FilePosition.h"

namespace dargon {

    /// @brief Represents a test result. Tracks its own status.
    /// @author Kyle Morris
    /// @since v0.1
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

    /// @brief Represents a single Unit Test.
    /// @author Kyle Morris
    /// @since v0.1
	class UnitTest {
	public:
        virtual TestResult Test() = 0;
    protected:
        TestResult _result;
	};

};

#endif
