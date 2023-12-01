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



    )

};

#endif
