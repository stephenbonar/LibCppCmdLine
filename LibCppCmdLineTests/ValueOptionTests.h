// ValueOptionTests.h - Defines the ValueOptionTests fixture.
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

#ifndef CMD_LINE_VALUE_OPTION_TESTS_H
#define CMD_LINE_VALUE_OPTION_TESTS_H

#include <string>
#include <deque>
#include <memory>
#include "gtest/gtest.h"
#include "ExampleArguments.h"
#include "ExampleHelp.h"
#include "TestDataStructures.h"
#include "TestAlgorithms.h"
#include "ValueOption.h"
#include "OptionParam.h"

namespace CmdLine
{
    /// @brief Test fixture for the ValueOption tests.
    ///
    /// Shared data and functions for the ValueOption tests are implemented as
    /// part of the fixture, although functions shared across all fixtures are 
    /// implemented in TestAlgorithms.h. See ValueOptionTests.cpp for the 
    /// actual tests.
    class ValueOptionTests : public ::testing::Test
    {
    protected:
        /// @brief Constructs the ValueOptionTests fixture.
        ///
        /// Initializes shared data common to all ValueOption tests. This 
        /// includes a few different ValueOption definitions, OptionParam
        /// definitions, ValueOption instances, OptionParam instances, the
        /// instance's expected states, and a few different argument queues 
        /// used to test populating the ValueOption instances
        /// with.
        ValueOptionTests();

        /// @brief Defines each shared ValueOption.
        ///
        /// Sets the properties on each of the ValueOption definitions used to
        /// construct the shared ValueOption instances to what they should be. 
        /// 
        /// @post All shared ValueOption definitions are defined.
        void DefineOptions();

        /// @brief Defines each shared OptionParam.
        ///
        /// Sets the properties on each of the OptionParam definitions used
        /// to construct the shared OptionParam instances to what they 
        /// should be. 
        /// 
        /// @post All shared OptionParam definitions are defined.
        void DefineOptionParams();

        /// @brief Defines what each expected state should be initially.
        ///
        /// @post All expected states will be in their initial state.
        void DefineInitialExpectedStates();

        /// @brief Initializes each shared ValueOption from its definition.
        ///
        /// @pre DefineOptions() should be called prior to calling this method.
        /// @post All shared ValueOption instances are initialized.
        void InitializeOptions();

        /// @brief Initializes each shared OptionParams from its definition.
        ///
        /// @pre DefineOptionParams() should be called prior to this.
        /// @post All shared OptionParam instances are initialized.
        void InitializeOptionParams();

        /// @brief Adds each shared OptionParams to its respective Option.
        ///
        /// Each OptionParam should be added to a ValueOption to be
        /// populated.
        /// 
        /// @pre DefineOptions() and DefineOptionParameters() should be called.
        /// @post Each shared OptionParameter is added its respective Option.
        void AddParamsToOptions();

        /// @brief Adds all args to the argument queues.
        ///
        /// Different set of arguments need to be added to different queues to
        /// cover different population tests. 
        /// 
        /// @post All non-empty argument queues are filled with arguments.
        void AddArgsToQueues();

        /// @brief Tests all ValueOption instances are in expected states.
        ///
        /// Each shared ValueOption that's part of the fixture has an expected
        /// state that each test can adjust. Tests can then call this function
        /// to ensure each ValueOption is in the expected state. If the test 
        /// does not adjust any of the expected states, calling this function 
        /// will test that each shared ValueOption is in its initial state.
        void TestExpectedStates();

        /// @brief Tests the printOption is successfully populated by song arg.
        ///
        /// Tests that the printOption will be successfully populated by the 
        /// song argument in the noParamValueArgs argument queue.
        /// 
        /// @post expectedSongPrintState is updated.
        /// @post expectedPrintOptionState is updated.
        /// @post 2 arguments are consumed from the noParameterValueArgs queue.
        /// @post printOption and songPrintParam are populated.
        void ExpectPopulatePrintOptionWithSong();

        /// @brief Tests printOption successfully populated w/ non-name value.
        ///
        /// Although the printOption has OptionParam instances added to it
        /// expecting values that populate those, a ValueOption should also
        /// accept values that don't populate any OptionParams. This
        /// method tests that scenario works properly.
        void ExpectPopulatePrintOptionWithNonNameValue();

        /// @brief Tests the editOption is successfully populated.
        ///
        /// Tests the editOption by running a PopulationTestScenario based on
        /// the current expectedEditOptionState and the paramValueArgs.
        /// This method should be called by other population test methods
        /// after setting the expectedEditOptionState.
        /// 
        /// @pre The expectedEditOptionState has been set.
        /// @pre A corresponding OptionParameterState has been set (if used).
        /// @post editOption and zero or one of its parameters are populated.
        void ExpectPopulateEditOption();

        /// @brief Tests the editOption is successfully populated by album arg.
        ///
        /// Tests that the editOption will be successfully populated by the 
        /// album argument in the paramValueArgs argument queue.
        /// 
        /// @post expectedAlbumEditState is updated.
        /// @post expectedEditOptionState is updated. 
        /// @post 2 arguments removed from paramValueArgs queue.
        /// @post editOption and albumEditParam are populated.
        void ExpectPopulateEditOptionWithAlbum();

        /// @brief Tests the editOption is successfully populated by artist arg
        ///
        /// Tests that the editOption will be successfully populated by the 
        /// artist argument in the paramValueArgs argument queue.
        /// 
        /// @post expectedAlbumEditState is updated.
        /// @post expectedEditOptionState is updated. 
        /// @post 2 arguments removed from paramValueArgs queue.
        /// @post editOption and artistEditParam are populated.
        void ExpectPopulateEditOptionWithArtist();

        /// @brief Tests that editOption cannot be populated with invalid args.
        ///
        /// Tries to populate the editOption using several argument queues
        /// containing invalid arguments, including emptyAgs, noParameterArgs,
        /// and nonOptionArgs. This test will pass if all three population
        /// attempts fail.
        void ExpectInvalidArgsDoNotPopulateEditOption();

        ValueOption::Definition printDef;
        ValueOption::Definition windowsPrintDef;
        ValueOption::Definition editDef;
        ValueOption::Definition mandatoryDef;

        OptionParam::Definition songDef;
        OptionParam::Definition artistDef;
        OptionParam::Definition albumDef;

        ValueOptionState expectedPrintOptionState;
        ValueOptionState expectedEditOptionState;
        ValueOptionState expectedMandatoryOptionState;

        OptionParamState expectedSongPrintState;
        OptionParamState expectedArtistPrintState;
        OptionParamState expectedAlbumPrintState;
        OptionParamState expectedSongEditState;
        OptionParamState expectedArtistEditState;
        OptionParamState expectedAlbumEditState;

        std::unique_ptr<ValueOption> printOption;
        std::unique_ptr<ValueOption> editOption;
        std::unique_ptr<ValueOption> mandatoryOption;
        std::unique_ptr<ValueOption> windowsPrintOption;

        std::unique_ptr<OptionParam> songPrintParam;
        std::unique_ptr<OptionParam> artistPrintParam;
        std::unique_ptr<OptionParam> albumPrintParam;

        std::unique_ptr<OptionParam> songEditParam;
        std::unique_ptr<OptionParam> artistEditParam;
        std::unique_ptr<OptionParam> albumEditParam;

        std::unique_ptr<OptionParam> dupSongPrintParam;

        std::deque<std::string> emptyArgs;
        std::deque<std::string> noParamArgs;
        std::deque<std::string> nonOptionArgs;
        std::deque<std::string> noParamValueArgs;
        std::deque<std::string> paramValueArgs;
        std::deque<std::string> mixedArgs;
        std::deque<std::string> nonNameValueArgs;
    };
}

#endif
