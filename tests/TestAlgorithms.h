// TestAlgorithms.h - Declares shared test algorithm functions.
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

#ifndef CMD_LINE_TEST_ALGORITHMS_H
#define CMD_LINE_TEST_ALGORITHMS_H

#include <string>
#include <sstream>
#include <vector>
#include <climits>
#include "gtest/gtest.h"
#include "ExampleArguments.h"
#include "ExampleHelp.h"
#include "TestDataStructures.h"
#include "Option.h"
#include "ValueOption.h"
#include "PosParam.h"
#include "MultiPosParam.h"
#include "ProgParam.h"
#include "Constants.h"

namespace CmdLine
{
    /// @brief Generates a bundle of different test Param names.
    ///
    /// Generates a bundle of different test Param names, including
    /// valid names, invalid names, valid short names, and invalid short names.
    /// The valid and invalid names can be tested with both an Option and a
    /// non-Option Parameter. Short names can only be tested with an Option.
    /// The resulting valid and invalid names are intended for testing 
    /// Param invariants related to names.
    /// 
    /// @param m The NameGenerationMode to use.
    /// @return The bundle of test names generated.
    TestNameBundle GenerateTestNames(NameGenerationMode m);

    /// @brief Generates the expected help info for a Unix-style print Option.
    ///
    /// Generates formatted help info for testing an example multimedia tag
    /// print option. The expected help info is generated from 
    /// unixPrintOptionHelpLine in ExampleHelp.h.
    /// 
    /// @return The expected formatted help info.
    std::string GenerateExpectedUnixPrintOptionHelpInfo();

    /// @brief Generates the expected help info for a ValueOption w/o Params.
    ///
    /// Generates formatted help info for testing an example multimedia tag
    /// print option, but without OptionParams. The expected help info is
    /// generated from unixPrintOptionHelpLine in ExampleHelp.h.
    /// 
    /// @return The expected formatted help info.
    std::string GenerateExpectedUnixPrintOptionHelpInfoNoParams();

    /// @brief Generates the expected help info for a Unix-style edit Option.
    ///
    /// Generates formatted help info for testing an example multimedia tag
    /// edit option. The expected help info is generated from 
    /// unixEditOptionHelpLine in ExampleHelp.h.
    /// 
    /// @return The expected formatted help info.
    std::string GenerateExpectedUnixEditOptionHelpInfo();

    /// @brief Generates expected help info for a Windows-style print Option.
    ///
    /// Generates formatted help info for testing an example multimedia tag
    /// print option. The expected help info is generated from 
    /// windowsPrintOptionHelpLine in ExampleHelp.h.
    /// 
    /// @return The expected formatted help info.
    std::string GenerateExpectedWindowsPrintOptionHelpInfo();

    /// @brief Generates expected usage info based on specified ProgramInfo.
    ///
    /// Generates expected usage info based on the specified ProgramInfo. The
    /// usage is what will be shown if a user requests usage info without
    /// additional help info. 
    /// 
    /// @param i The ProgramInfo from which to generate expected usage.
    /// @return The expected usage info.
    std::string GenerateExpectedUsage(ProgramInfo i);

    /// @brief Generates expected usage info with added help message.
    ///
    /// Same as GenerateExpectedUsage(), but adds a message explaining how to
    /// request additional help info.
    /// 
    /// @param i The ProgramInfo from which to generate expected usage.
    /// @return The expected usage info.
    std::string GenerateExpectedUsageWithMessage(ProgramInfo i);

    /// @brief Generates expected program help from ProgramInfo.
    ///
    /// Generates expected full, formatted program help, including usage info
    /// and help for individual options, positional parameters, etc.
    /// 
    /// @param i The ProgramInfo to generate expected help info from.
    /// @return The expected help info.
    std::string GenerateExpectedProgramHelp(ProgramInfo i);

    /// @brief Tests that the specified Param is in the specified state.
    /// 
    /// Use this function to ensure a Param is in its expected state.
    /// 
    /// @param p The Param to evaluate.
    /// @param s The expected state of the Param.
    void ExpectParamState(Param* p, ParamState* s);

    /// @brief Gets the initial state of an Option based on its definition.
    ///
    /// Gets the initial state an Option is supposed to be in when it is 
    /// first constructed. This is not only useful for checking that an
    /// Option was created properly, but should also be a starting point for
    /// building expected states.
    /// 
    /// @param d The definition from which to get the initial state.
    /// @return Returns the expected initial state.
    OptionState GetInitialState(Option::Definition d);

    /// @brief Gets the initial state of a ValueOption based on its definition.
    ///
    /// Gets the initial state a ValueOption is supposed to be in when it is 
    /// first constructed. This is not only useful for checking that a 
    /// ValueOption was created properly, but should also be a starting point 
    /// for building expected states.
    /// 
    /// @param d The definition from which to get the initial state.
    /// @return Returns the expected initial state.
    ValueOptionState GetInitialState(ValueOption::Definition d);

    /// @brief Gets the initial state of a MultiPosParam from its definition.
    ///
    /// Gets the initial state a MultiPosParam is supposed to be in when it 
    /// is first constructed. This is not only useful for checking that a 
    /// MultiPosParam was created properly, but should also be a starting 
    /// point for building expected states.
    /// 
    /// @param d The definition from which to get the initial state.
    /// @return Returns the expected initial state.
    MultiPosParamState GetInitialState(MultiPosParam::Definition d);

    /// @brief Gets the initial state of a PosParam from its definition.
    ///
    /// Gets the initial state a PosParam is supposed to be in when it 
    /// is first constructed. This is not only useful for checking that a 
    /// PosParam was created properly, but should also be a starting 
    /// point for building expected states.
    /// 
    /// @param d The definition from which to get the initial state.
    /// @return Returns the expected initial state.
    PosParamState GetInitialState(PosParam::Definition d);

    /// @brief Gets initial state of an OptionParam from its definition.
    ///
    /// Gets the initial state an OptionParam is supposed to be in when it 
    /// is first constructed. This is not only useful for checking that an 
    /// OptionParam was created properly, but should also be a starting 
    /// point for building expected states.
    /// 
    /// @param d The definition from which to get the initial state.
    /// @return Returns the expected initial state.
    OptionParamState GetInitialState(OptionParam::Definition d);

    /// @brief Gets initial state of a ProgParam from its definition.
    ///
    /// Gets the initial state an ProgParam is supposed to be in when it
    /// is first constructed. This is not only useful for checking that a 
    /// ProgParam was created properly, but should also be a starting 
    /// point for building expected states.
    /// 
    /// @param d The definition from which to get the initial state.
    /// @return Returns the expected initial state.
    ProgParamState GetInitialState(ProgParam::Definition d);

    /// @brief Tests that the specified Option is in the specified state.
    /// 
    /// Use this function to ensure an Option is in its expected state.
    /// 
    /// @param o The Option to evaluate.
    /// @param s The expected state of the Option.
    void ExpectState(const Option& o, const OptionState& s);

    /// @brief Tests that the specified ValueOption is in the specified state.
    /// 
    /// Use this function to ensure a ValueOption is in its expected state.
    /// 
    /// @param o The ValueOption to evaluate.
    /// @param s The expected state of the ValueOption.
    void ExpectState(const ValueOption& o, const ValueOptionState& s);

    /// @brief Tests specified OptionParam is in the specified state.
    /// 
    /// Use this function to ensure an OptionParam is in its expected 
    /// state.
    /// 
    /// @param p The OptionParam to evaluate.
    /// @param s The expected state of the OptionParam.
    void ExpectState(const OptionParam& p, const OptionParamState& s);

    /// @brief Tests specified ProgParam is in the specified state.
    /// 
    /// Use this function to ensure a ProgParam is in its expected 
    /// state.
    /// 
    /// @param p The ProgParam to evaluate.
    /// @param s The expected state of the ProgParam.
    void ExpectState(const ProgParam& p, const ProgParamState& s);

    /// @brief Tests specified PosParam is in the specified state.
    /// 
    /// Use this function to ensure a PosParam is in its expected state.
    /// 
    /// @param p The PosParam to evaluate.
    /// @param s The expected state of the PosParam.
    void ExpectState(const PosParam& p, const PosParamState& s);

    /// @brief Tests specified MultiPosParam is in the specified state.
    /// 
    /// Use this function to ensure a MultiPosParam is in its expected state.
    /// 
    /// @param p The MultiPosParam to evaluate.
    /// @param s The expected state of the MultPosParam.
    void ExpectState(const MultiPosParam& p, const MultiPosParamState& s);

    /// @brief Gets the initial state of an Option based on its definition.
    ///
    /// Gets the initial state an Option is supposed to be in when it is first
    /// constructed. This is not only useful for checking that an Option was
    /// created properly, but should also be a starting point for building
    /// expected states. This is a function tempate used for generating the
    /// initial state of different types of Option and its derived types.
    /// 
    /// @tparam T The type of option definition to use.
    /// @tparam U The type of option state to use.
    /// @param definition The definition from which to get the initial state.
    /// @return Returns the expected initial state.
    template<typename T, typename U>
    U GetInitialOptionState(T definition)
    {
        U state;
        std::string shortPrefix;
        std::string longPrefix;

        if (definition.style == Option::Style::Unix)
        {
            shortPrefix = unixOptionShortPrefix;
            longPrefix = unixOptionLongPrefix;
        }
        else
        {
            shortPrefix = windowsOptionShortPrefix;
            longPrefix = windowsOptionLongPrefix;
        }

        std::string shortName{ definition.shortName };
        std::string longName{ definition.longName };

        if (definition.shortName == 0)
            state.name = longPrefix + longName;
        else
            state.name = shortPrefix + shortName;

        if (longName != "")
            state.longName = longPrefix + longName;

        state.description = definition.description;
        state.isMandatory = definition.isMandatory;

        return state;
    }

    /// @brief Gets the initial state of a Param based on its definition.
    ///
    /// Gets the initial state a Param is supposed to be in when it is 
    /// first constructed. This is not only useful for checking that a 
    /// Param was created properly, but should also be a starting point for
    /// building expected states. This is a function tempate used for 
    /// generating the initial state of different types of Param and its 
    /// derived types, but this one is used for the simplest types.
    /// 
    /// @tparam T The type of Param definition to use.
    /// @tparam U The type of Param state to use.
    /// @param definition The definition from which to get the initial state.
    /// @return Returns the expected initial state.
    template<typename T, typename U>
    U GetInitialParamState(T definition)
    {
        U state;
        state.name = definition.name;
        state.description = definition.description;
        state.isMandatory = definition.isMandatory;

        return state;
    }

    /// @brief Expects that the test scenario will result in population.
    ///
    /// Accepts a PopulationTestScenario and tests that the Param in the
    /// scenario is succcessfully populated by the scenario's arguments, etc.
    /// 
    /// @tparam T The type of Param to test.
    /// @tparam U The type of ParamState to test.
    /// @param s The scenario to test population with.
    template<typename T, typename U>
    void ExpectPopulation(PopulationTestScenario<T, U> s)
    {
        ASSERT_GE(s.args->size(), s.argsToConsume);
        std::deque<std::string> argsRemaining = *s.args;

        EXPECT_TRUE(s.param->Populate(*s.args));
        ExpectState(*s.param, *s.expectedState);

        for (std::size_t i = 0; i < s.argsToConsume; i++)
            argsRemaining.pop_front();

        EXPECT_EQ(*s.args, argsRemaining);
    }

    /// @brief Expects that the test scenario will not result in population.
    ///
    /// Accepts a PopulationTestScenario and tests that the Param in the
    /// scenario is not successfully populated by the scenario's arguments, 
    /// etc.
    /// 
    /// @tparam T The type of Param to test.
    /// @tparam U The type of Param state to test.
    /// @param s The scenario to test population with.
    template<typename T, typename U>
    void ExpectNoPopulation(PopulationTestScenario<T, U> s)
    {
        std::deque<std::string> argsRemaining = *s.args;
        EXPECT_FALSE(s.param->Populate(*s.args));
        ExpectState(*s.param, *s.expectedState);
        EXPECT_EQ(*s.args, argsRemaining);
    }

    /// @brief Tests that a Param enforces its invariants.
    ///
    /// Tests that a Param enforces its invariants by throwing an exception
    /// when an invalid Param::Definition is supplied to the constructor
    /// and not throwing any exceptions when a valid Param::Definition is
    /// supplied. This is a function template to ensure various types of
    /// Param (derivatives) can be tested.
    /// 
    /// @tparam T The type of Param to use.
    /// @tparam U The type of Param::Definition to use.
    template<typename T, typename U>
    void TestParamInvariants()
    {
        T definition;
        definition.name = "test";
        definition.description = "test description";

        TestNameBundle test = GenerateTestNames(NameGenerationMode::PlainName);

        for (auto name : test.validNames)
        {
            definition.name = name;
            EXPECT_NO_THROW(U{ definition });
        }

        for (auto name : test.invalidNames)
        {
            definition.name = name;
            EXPECT_THROW(U{ definition }, Param::InvalidDefinition);
        }
    }

    /// @brief Tests that an Option enforces its invariants.
    ///
    /// Tests that an Option enforces its invariants by throwing an exception
    /// when an invalid Option::Definition is supplied to the constructor
    /// and not throwing any exceptions when a valid Option::Definition is
    /// supplied. This is a function template to ensure various types of
    /// Option (derivatives) can be tested.
    /// 
    /// @tparam T The type of Option to use.
    /// @tparam U The type of Option::Definition to use.
    template<typename T, typename U>
    void TestOptionInvariants()
    {
        T d;
        d.shortName = 't';
        d.longName = "test";
        d.description = "test option descriptor";

        TestNameBundle test = GenerateTestNames(NameGenerationMode::PlainName);

        for (auto name : test.validShortNames)
        {
            d.shortName = name;
            ASSERT_NO_THROW(U{ d });
        }

        for (auto name : test.invalidShortNames)
        {
            d.shortName = name;
            if (name != 0)
                ASSERT_THROW(U{ d }, Param::InvalidDefinition);
        }

        // Put the short name back so it doesn't interfere with long name tests
        d.shortName = 't';

        for (auto name : test.validNames)
        {
            d.longName = name;
            ASSERT_NO_THROW(U{ d });
        }

        for (auto name : test.invalidNames)
        {
            d.longName = name;
            if (name != "")
                ASSERT_THROW(U{ d }, Param::InvalidDefinition);
        }

        d.longName = "test";
        U o{ d };

        EXPECT_EQ(o.IsSpecified(), false);
        EXPECT_EQ(o.IsMandatory(), false);

        d.shortName = 0;
        ASSERT_NO_THROW(U{ d });
        d.longName = "";
        ASSERT_THROW(U{ d }, Param::InvalidDefinition);
        d.longName = "test";
        ASSERT_NO_THROW(U{ d });
    }
}

#endif
