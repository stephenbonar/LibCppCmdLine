// TestDataStructures.h - Declares shared test data structures.
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


#ifndef CMD_LINE_TEST_DATA_STRUCTURES
#define CMD_LINE_TEST_DATA_STRUCTURES

#include <string>
#include <vector>
#include "MultiPosParam.h"
#include "ProgParam.h"
#include "PosParam.h"

namespace CmdLine
{
    /// @brief Determines what types of test names should be generated.
    enum class NameGenerationMode 
    {
        /// @brief Generates plain test Parameter names.
        PlainName, 

        /// @brief Generates test names that are paired with test values.
        NameValuePair 
    };

    /// @brief The scenario for testing Parameter Population.
    ///
    /// The PopulationTestScenario allows you to specify the Param to
    /// test Population with, its expectedState, the args to populate the
    /// Param from, and the number of args the Param is expected
    /// to consume. Passing a PopulationTestScenario to ExpectPopulation() or
    /// ExpectNoPopulation() in TestAlgorithms.h will perform the population
    /// tests based on the scenario.
    /// 
    /// @tparam T The type of Param to use.
    /// @tparam U The type of ParamState state to use.
    template <typename T, typename U>
    struct PopulationTestScenario
    {
        /// @brief The Param to test population with.
        T* param = nullptr;

        /// @brief The state Param is expected to be in after population.
        U* expectedState = nullptr;

        /// @brief The arguments to test population with.
        std::deque<std::string>* args = nullptr;

        /// @brief The number of args the Param is expected to consume.
        std::size_t argsToConsume = 1;
    };

    /// @brief A bundle of valid and invalid names used for testing invariants.
    ///
    /// A Param has invariants around what types of Param names are
    /// valid and invalid. The TestNameBundle provides vectors of validNames,
    /// invalidNames, validShortNames, and invalidShortNames for testing these
    /// invariants. validNames and validShortNames are compatible with all
    /// types that inherit from Param, but validShortNames and 
    /// invalidShortNames are only compatible with types that inherit from
    /// Option. A fully populated TestNameBundle can be generated using
    /// GenerateTestNames() in TestAlgorithms.h.
    struct TestNameBundle
    {
        /// @brief A vector of valid Param names to test with.
        std::vector<std::string> validNames;

        /// @brief A vector of invalid Param names to test with.
        std::vector<std::string> invalidNames;

        /// @brief A vector of valid short Option names to test with.
        std::vector<char> validShortNames;

        /// @brief A vector of invalid short Option names to test with.
        std::vector<char> invalidShortNames;
    };

    /// @brief Represents the state of the most basic Param types.
    ///
    /// Use ParamState to test expected Param states with actual
    /// states of Param instances.
    struct ParamState
    {
        /// @brief The name of the Param.
        std::string name;

        /// @brief The description of the Param.
        std::string description;

        /// @brief Determines whether the Param is specified.
        bool isSpecified = false;
        
        /// @brief Determines whether the Param is mandatory.
        bool isMandatory = false;
    };

    /// @brief Represents the state of an OptionParam.
    ///
    /// Use OptionParamState to test expected OptionParam states with
    /// actual states of OptionParam instances.
    struct OptionParamState : public ParamState
    {
        /// @brief The value of the OptionParam.
        std::string value;
    };

    /// @brief Represents the state of a ProgParam.
    ///
    /// Use ProgParamState to test expected ProgParam states with
    /// actual states of ProgParam instances.
    struct ProgParamState : public ParamState
    {
        /// @brief The value of the ProgramParam.
        std::string value;
    };

    /// @brief Represents the state of an Option.
    ///
    /// Use OptionState to test expected Option states with actual states of 
    /// Option instances.
    struct OptionState : public ParamState
    {
        /// @brief The long name of the Option.
        std::string longName;
    };

    /// @brief Represents the state of a ValueOption.
    ///
    /// Use ValueOptionState to test expected ValueOption states with actual
    /// states of ValueOption instances.
    struct ValueOptionState : public OptionState
    {
        /// @brief The values of the ValueOption.
        std::vector<std::string> values;
    };

    /// @brief Represents the state of a PosParam.
    ///
    /// Use PosParamState to test expected PosParam states with actual 
    /// states of PosParam instances.
    struct PosParamState : public ParamState
    {
        /// @brief The value of the PosParam.
        std::string value;
    };

    /// @brief Represents the state of a MultiPosParam.
    ///
    /// Use MultiPosParamState to test expected MultiPosParam states with
    /// actual states of MultiPosParam instances.
    struct MultiPosParamState : public ParamState
    {
        /// @brief The values of the MultiPosParam.
        std::vector<std::string> values;

        /// @brief The ParsingOrder of the MultiPosParam.
        MultiPosParam::ParsingOrder order;
    };

    /// @brief Test info representing an entire example program.
    ///
    /// The ProgramInfo contains all the command line Param instances
    /// necessary to represent a complete program.
    struct ProgramInfo
    {
        /// @brief The ProgParam instance of the example program.
        ProgParam* program = nullptr;

        /// @brief The Option instances of the example program.
        std::vector<Option*> options;

        /// @brief The PosParam instances of the example program.
        std::vector<PosParam*> positionals;

        /// @brief The MultiPosParam instance of the example program.
        MultiPosParam* multiPosParam = nullptr;
    };
}

#endif
