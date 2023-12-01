 /**
 * Dargon Programming Language
 * (C) Kyle Morris 2023 - See LICENSE.txt for license information.
 *
 * @file FileTests.h
 * @author Kyle Morris
 * @since v0.1
 * @section Description
 * Contains unit tests for the File supertype.
 *
 */

#ifndef DARGON_HEADER_FILE_TESTS
#define DARGON_HEADER_FILE_TESTS

#include "TestingMacros.h"
#include "../core/File.h"
#include <sstream>

namespace dargon {

    /// @brief Opens various types of files, both that
    /// exist and that don't.
    DARGON_UNIT_TEST(OpenFile,

        Script s;

        // Try to open invalid files
        DARGON_TEST_ASSERT( !s.OpenAbsolute("home/kylemorris/FAKE.dargon") );
        DARGON_TEST_ASSERT( !s.OpenRelative("FAKE.dargon") );

        // Open a legitamate file
        DARGON_TEST_ASSERT( s.OpenRelative("TEST.dargon") );

        // Close it
        s.Close();
    )

    /// @brief Read lines from the file and print status
    DARGON_UNIT_TEST(ReadFromFile,
        /*
        TEST.dargon

        1 # A comment line
        2
        3 const a :int = 1
        4 const b :int = 2
        5
        6 print(a + b)

        */

        // Open file
        Script s;
        DARGON_TEST_ASSERT( s.OpenRelative("TEST.dargon") );

        // File position is 1,1
        FilePosition f = FilePosition(1, 1);
        DARGON_TEST_ASSERT( s.CurrentPosition().Equals(f) );

        // File position prints appropriately
        DARGON_TEST_ASSERT( s.ShowPosition() == "TEST.dargon @ Line 1 Col 1" );

        // Go down two lines and confirm
        s.MoveDown(1);
        std::string l1 = s.ReadLine();
        DARGON_TEST_ASSERT( s.ShowPosition() == "TEST.dargon @ Line 2 Col 1" );

        s.MoveDown(1);
        std::string l2 = s.ReadLine();
        DARGON_TEST_ASSERT( s.ShowPosition() == "TEST.dargon @ Line 3 Col 1" );

        // Go back to first line
        s.MoveUp(2);
        DARGON_TEST_ASSERT( s.ShowPosition() == "TEST.dargon @ Line 1 Col 1" );

        // Show more in-depth information
        // Should be:
        // TEST.dargon @ Line 1 Col 1:
        // # A comment line
        // ^
        std::ostringstream os;
        os << "TEST.dargon @ Line 1 Col 1:" << std::endl;
        os << "# A comment line" << std::endl;
        os << "^";
        DARGON_TEST_ASSERT( s.ShowExactPosition() == os.str() );

        s.Close();
    )

    DARGON_UNIT_TEST(MultilateralMovement,
        /*
        TEST.dargon

        1 # A comment line
        2
        3 const a :int = 1
        4 const b :int = 2
        5
        6 print(a + b)

        */
        // Open file
        Script s;
        DARGON_TEST_ASSERT( s.OpenRelative("TEST.dargon") );

        // Move to line 3 column 5 in two different ways
        FilePosition f = FilePosition(3, 5);

        s.MoveDown(2); s.MoveRight(4);
        DARGON_TEST_ASSERT( s.CurrentPosition().Equals(f) );

        s.Reset();
        s.GotoLine(3); s.GotoColumn(5);
        DARGON_TEST_ASSERT( s.CurrentPosition().Equals(f) );

        // Print it out
        DARGON_TEST_ASSERT( s.ShowPosition() == "TEST.dargon @ Line 2, Col 5" );

        // Show more in-depth information
        // Should be:
        // TEST.dargon @ Line 3 Col 5:
        // const a :int = 1
        // ~~~~^
        std::ostringstream os;
        os << "TEST.dargon @ Line 3 Col 5:" << std::endl;
        os << "const a :int = 1" << std::endl;
        os << "~~~~^";
        DARGON_TEST_ASSERT( s.ShowExactPosition() == os.str() );
        os.str("");

        // Move right a few and print out again
        s.MoveRight(4);
        os << "TEST.dargon @ Line 3 Col 5:" << std::endl;
        os << "const a :int = 1" << std::endl;
        os << "~~~~~~~~^";

        s.Close();
    )

    DARGON_UNIT_TEST(EdgeCases,

    )

};

#endif
