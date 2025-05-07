// MultiPosParamTests.h - Declares the MultiPosParamTests fixture.
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

#ifndef CMD_LINE_MULTI_POS_PARAM_TESTS_H
#define CMD_LINE_MULTI_POS_PARAM_TESTS_H

#include <string>
#include <vector>
#include <memory>
#include "gtest/gtest.h"
#include "ExampleHelp.h"
#include "ExampleArguments.h"
#include "TestDataStructures.h"
#include "TestAlgorithms.h"
#include "Param.h"
#include "MultiPosParam.h"
#include "Option.h"

namespace CmdLine
{
    /// @brief Test fixture for the MultiPosParam tests.
    ///
    /// Shared data and functions for the MultiPosParam tests are 
    /// implemented as part of the fixture, although functions shared across
    /// all fixtures are implemented in TestAlgorithms.h. See 
    /// MultiPosParamTests.cpp for the actual tests.
    class MultiPosParamTests : public ::testing::Test
    {
    protected:
        /// @brief Constructs the MultiPosParamTests fixture.
        ///
        /// Initializes shared data common to all MultiPosParam tests. This
        /// includes a few different MultiPosParam definitions, 
        /// MultiPosParam instances, the instance's expected states, and 
        /// a few different argument queues used to test populating the
        /// MultiPosParam instances with.
        MultiPosParamTests();

        /// @brief Tests all shared MultiPosParam are in expected states.
        ///
        /// Each shared MultiPosParam that's part of the fixture has an
        /// expected state that each test can adjust. Tests can then call
        /// this function to ensure each MultiPosParam is in the expected
        /// state. If the test does not adjust any of the expected states,
        /// calling this function will test that each shared MultiPosParam
        /// is in its initial state.
        void TestExpectedStates();

        MultiPosParam::Definition searchFilesDef;
        MultiPosParam::Definition copySourceDef;
        MultiPosParam::Definition mandatoryDef;

        MultiPosParamState expectedSearchFilesState;
        MultiPosParamState expectedCopySourceState;
        MultiPosParamState expectedMandatoryState;

        std::unique_ptr<MultiPosParam> searchFilesMultiPosParam;
        std::unique_ptr<MultiPosParam> copySourceMultiPosParam;
        std::unique_ptr<MultiPosParam> mandatoryMultiPosParam;

        std::deque<std::string> emptyArgs;
        std::deque<std::string> optionArgs;
        std::deque<std::string> mixedArgs;
        std::deque<std::string> multiPosArgs;
    };
}

#endif
