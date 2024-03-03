// PosParamTests.h - Declares the PosParamTests fixture.
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

#ifndef CMD_LINE_POS_PARAM_TESTS_H
#define CMD_LINE_POS_PARAM_TESTS_H

#include <string>
#include <deque>
#include <memory>
#include "gtest/gtest.h"
#include "ExampleArguments.h"
#include "TestDataStructures.h"
#include "TestAlgorithms.h"
#include "ExampleHelp.h"
#include "PosParam.h"

namespace CmdLine
{
    /// @brief Test fixture for the PosParam tests.
    ///
    /// Shared data and functions for the PosParam tests are implemented as 
    /// part of the fixture, although functions shared across all fixtures are 
    /// implemented in TestAlgorithms.h. See PosParamTests.cpp for the actual
    /// tests.
    class PosParamTests : public ::testing::Test
    {
    protected:
        /// @brief Constructs the PosParamTests fixture.
        ///
        /// Initializes shared data common to all PosParam tests. This 
        /// includes a few different PosParam definitions, PosParam 
        /// instances, the instance's expected states, and a few different 
        /// argument queues used to test populating the PosParam instances 
        /// with.
        PosParamTests();

        /// @brief Tests all shared PosParam are in expected states.
        ///
        /// Each shared PosParam that's part of the fixture has an expected 
        /// state that each test can adjust. Tests can then call this function
        /// to ensure each PosParam is in the expected state. If the test 
        /// does not adjust any of the expected states, calling this function
        /// will test that each shared PosParam is in its initial state.
        void TestExpectedStates();

        PosParam::Definition searchPatternDef;
        PosParam::Definition copyDestinationDef;
        PosParam::Definition mandatoryDef;

        PosParamState expectedSearchPatternState;
        PosParamState expectedCopyDestinationState;
        PosParamState expectedMandatoryState;

        std::unique_ptr<PosParam> searchPatternPosParam;
        std::unique_ptr<PosParam> copyDestinationPosParam;
        std::unique_ptr<PosParam> mandatoryPosParam;

        std::deque<std::string> emptyArgs;
        std::deque<std::string> optionArgs;
        std::deque<std::string> posArgs;
    };
}

#endif