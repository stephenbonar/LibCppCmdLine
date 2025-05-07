// OptionTests.h - Declares the OptionTests fixture.
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

#ifndef CMD_LINE_OPTION_TESTS_H
#define CMD_LINE_OPTION_TESTS_H

#include <string>
#include <deque>
#include <locale>
#include <sstream>
#include <limits>
#include <memory>
#include "gtest/gtest.h"
#include "ExampleArguments.h"
#include "ExampleHelp.h"
#include "TestDataStructures.h"
#include "TestAlgorithms.h"
#include "Constants.h"
#include "Option.h"

namespace CmdLine
{
    /// @brief Test fixture for the Option tests.
    ///
    /// Shared data and functions for the Option tests are implemented as part
    /// of the fixture, although functions shared across all fixtures are 
    /// implemented in TestAlgorithms.h. See OptionTests.cpp for the actual 
    /// tests.
    class OptionTests : public ::testing::Test
    {
    protected:
        /// @brief Constructs the OptionTests fixture.
        ///
        /// Initializes shared data common to all Option tests. This includes a
        /// few different Option definitions, Option instances, the instance's 
        /// expected states, and a few different argument queues used to test 
        /// populating the Option instances with.
        OptionTests();

        /// @brief Defines each shared Option.
        ///
        /// Sets the properties on each of the Option definitions used to
        /// construct the shared Option instances to what they should be. 
        /// 
        /// @post All shared Option definitions are defined.
        void DefineOptions();

        /// @brief Initializes each shared Option from its definition.
        ///
        /// @pre DefineOptions() should be called prior to calling this method.
        /// @post All shared Option instances are initialized.
        void InitializeOptions();

        /// @brief Defines what each expected Option state should be initially.
        ///
        /// @post All expected Option states will be in their initial state.
        void DefineInitialExpectedStates();

        /// @brief Adds all args to the argument queues.
        ///
        /// Different set of args need to be added to different queues to
        /// cover different population tests. 
        /// 
        /// @post All non-empty argument queues are filled with arguments.
        void AddArgsToQueues();

        /// @brief Tests all shared Options are in expected states.
        ///
        /// Each shared Option that's part of the fixture has an expected state
        /// that each test can adjust. Tests can then call this function to 
        /// ensure each Option is in the expected state. If the test does not 
        /// adjust any of the expected states, calling this function will test
        /// that each shared Option is in its initial state.
        void TestExpectedStates();

        Option::Definition unixVerboseDef;
        Option::Definition windowsVerboseDef;
        Option::Definition mandatoryDef;
        Option::Definition unixShortDef;
        Option::Definition unixLongDef;
        Option::Definition windowsShortDef;
        Option::Definition windowsLongDef;

        OptionState expectedUnixVerboseState;
        OptionState expectedDupUnixVerboseState;
        OptionState expectedWindowsVerboseState;
        OptionState expectedDupWindowsVerboseState;
        OptionState expectedMandatoryState;
        OptionState expectedUnixShortState;
        OptionState expectedUnixLongState;
        OptionState expectedWindowsShortState;
        OptionState expectedWindowsLongState;

        std::unique_ptr<Option> unixVerboseOption;
        std::unique_ptr<Option> dupUnixVerboseOption;
        std::unique_ptr<Option> windowsVerboseOption;
        std::unique_ptr<Option> dupWindowsVerboseOption;
        std::unique_ptr<Option> mandatoryOption;
        std::unique_ptr<Option> unixShortOption;
        std::unique_ptr<Option> unixLongOption;
        std::unique_ptr<Option> windowsShortOption;
        std::unique_ptr<Option> windowsLongOption;

        std::deque<std::string> unixOptionArgs;
        std::deque<std::string> windowsOptionArgs;
        std::deque<std::string> nonOptionArgs;
        std::deque<std::string> mixedArgs;
        std::deque<std::string> emptyArgs;
    };
}

#endif

