// ProgParamTests.h - Defines the ProgParamTests fixture.
//
// Copyright (C) 2024 Stephen Bonar
//
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
//
// http ://www.apache.org/licenses/LICENSE-2.0
// 
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissionsand
// limitations under the License.

#ifndef CMD_LINE_PROG_PARAM_TESTS_H
#define CMD_LINE_PROG_PARAM_TESTS_H

#include <memory>
#include "gtest/gtest.h"
#include "ExampleArguments.h"
#include "ExampleHelp.h"
#include "TestDataStructures.h"
#include "TestAlgorithms.h"
#include "ProgParam.h"

namespace CmdLine
{
    /// @brief Test fixture for the ProgParam tests.
    ///
    /// Shared data and functions for the ProgParam tests are 
    /// implemented as part of the fixture, although functions shared across 
    /// all fixtures are implemented in TestAlgorithms.h. See 
    /// ProgParamTests.cpp for the actual tests.
    class ProgParamTests : public ::testing::Test
    {
    protected:
        /// @brief Constructs the ProgParamTests fixture.
        ///
        /// Initializes shared data common to all ProgParam tests. This 
        /// includes a few different ProgParam definitions and 
        /// instances, the instance's expected states, and a few different 
        /// argument queues used to test populating the ProgParam 
        /// instances with.
        ProgParamTests();

        /// @brief Tests all shared ProgParam are in expected states.
        ///
        /// Each shared ProgParam that's part of the fixture has an 
        /// expected state that each test can adjust. Tests can then call this 
        /// function to ensure each ProgParam is in the expected state. 
        /// If the test does not adjust any of the expected states, calling 
        /// this function will test that each shared ProgParam is in its
        /// initial state.
        void TestExpectedStates();

        ProgParam::Definition mediaDef;
        ProgParam::Definition searchDef;
        ProgParam::Definition copyDef;

        ProgParamState expectedMediaProgParamState;
        ProgParamState expectedSearchProgParamState;
        ProgParamState expectedCopyProgParamState;

        std::unique_ptr<ProgParam> mediaProgParam;
        std::unique_ptr<ProgParam> searchProgParam;
        std::unique_ptr<ProgParam> copyProgParam;

        std::deque<std::string> emptyArgs;
        std::deque<std::string> mediaArgs;
        std::deque<std::string> searchArgs;
        std::deque<std::string> copyArgs;
    };
}

#endif // ! COMMAND_LINE_PROGRAM_NAME_TESTS_H
