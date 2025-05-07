// OptionParamTests.h - Declares the OptionParam test fixture.
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

#ifndef CMD_LINE_OPTION_PARAM_TESTS_H
#define CMD_LINE_OPTION_PARAM_TESTS_H

#include <memory>
#include "gtest/gtest.h"
#include "ExampleArguments.h"
#include "ExampleHelp.h"
#include "TestDataStructures.h"
#include "TestAlgorithms.h"
#include "OptionParam.h"
#include "NameValuePair.h"

namespace CmdLine
{
    /// @brief Test fixture for the OptionParam tests.
    ///
    /// Shared data and functions for the OptionParam tests are 
    /// implemented as part of the fixture, although functions shared across
    /// all fixtures are implemented in TestAlgorithms.h. See 
    /// OptionParamTests.cpp for the actual tests.
    class OptionParamTests : public ::testing::Test
    {
    protected:
        /// @brief Constructs the OptionParamTests fixture.
        ///
        /// Initializes shared data common to all OptionParam tests. This
        /// includes a few different OptionParam definitions, 
        /// OptionParam instances, the instance's expected states, and 
        /// a few different NameValuePairs used to test populating the
        /// OptionParam instances with.
        OptionParamTests();

        /// @brief Tests all shared OptionParams are in expected states.
        ///
        /// Each shared OptionParam that's part of the fixture has an
        /// expected state that each test can adjust. Tests can then call
        /// this function to ensure each OptionParam is in the expected
        /// state. If the test does not adjust any of the expected states,
        /// calling this function will test that each shared OptionParam
        /// is in its initial state.
        void TestExpectedStates();

        OptionParam::Definition songDef;
        OptionParam::Definition albumDef;
        OptionParam::Definition mandatoryDef;

        OptionParamState expectedSongState;
        OptionParamState expectedAlbumState;
        OptionParamState expectedMandatoryState;

        std::unique_ptr<OptionParam> songParam;
        std::unique_ptr<OptionParam> albumParam;
        std::unique_ptr<OptionParam> mandatoryParam;

        NameValuePair songPair{ songOptionParamName };
        NameValuePair albumPair{ albumNameValuePairArg };
    };
}

#endif
