// MultiPosParamTests.cpp - Defines tests for the MultiPosParam class.
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

#include "MultiPosParamTests.h"

namespace CmdLine
{
    MultiPosParamTests::MultiPosParamTests()
    {
        searchFilesDef.name = searchFilesMultiPosName;
        searchFilesDef.description = searchFilesMultiPosDescription;
        searchFilesMultiPosParam = std::make_unique<MultiPosParam>(
            searchFilesDef);
        expectedSearchFilesState = GetInitialState(searchFilesDef);

        copySourceDef.name = copySourceMultiPosName;
        copySourceDef.description = copySourceMultiPosDescription;
        copySourceDef.order = MultiPosParam::ParsingOrder::AfterOptions;
        copySourceMultiPosParam = std::make_unique<MultiPosParam>(
            copySourceDef);
        expectedCopySourceState = GetInitialState(copySourceDef);

        mandatoryDef = searchFilesDef;
        mandatoryDef.isMandatory = true;
        mandatoryMultiPosParam = std::make_unique<MultiPosParam>(mandatoryDef);
        expectedMandatoryState = GetInitialState(mandatoryDef);

        optionArgs.push_back(unixVerboseOptionShortName);
        optionArgs.push_back(unixEditOptionShortName);

        mixedArgs.push_back(unixVerboseOptionShortName);
        mixedArgs.push_back(searchFileName1);

        multiPosArgs.push_back(searchFileName1);
        multiPosArgs.push_back(searchFileName2);
    }

    void MultiPosParamTests::TestExpectedStates()
    {
        ExpectState(*searchFilesMultiPosParam, expectedSearchFilesState);
        ExpectState(*copySourceMultiPosParam, expectedCopySourceState);
        ExpectState(*mandatoryMultiPosParam, expectedMandatoryState);
    }

    TEST_F(MultiPosParamTests, CreatesMultiPosParamProperly)
    {
        TestExpectedStates();
    }

    TEST_F(MultiPosParamTests, ConstructorEnforcesInvariants)
    {
        TestParamInvariants<MultiPosParam::Definition, MultiPosParam>();
    }

    TEST_F(MultiPosParamTests, GeneratesHelpInfoProperly)
    {
        std::string expectedHelpInfo{ searchFilesMultiPosHelpLine };
        EXPECT_EQ(searchFilesMultiPosParam->HelpInfo(), expectedHelpInfo);
    }

    TEST_F(MultiPosParamTests, ChecksCanPopulateProperly)
    {
        EXPECT_FALSE(searchFilesMultiPosParam->CanPopulate(emptyArgs));
        EXPECT_FALSE(searchFilesMultiPosParam->CanPopulate(optionArgs));
        EXPECT_FALSE(searchFilesMultiPosParam->CanPopulate(mixedArgs));
        EXPECT_TRUE(searchFilesMultiPosParam->CanPopulate(multiPosArgs));
    }

    TEST_F(MultiPosParamTests, PopulatesMultiPosParamProperly)
    {
        TestExpectedStates();

        expectedSearchFilesState.isSpecified = true;
        expectedSearchFilesState.values.push_back(searchFileName1);
        expectedSearchFilesState.values.push_back(searchFileName2);

        PopulationTestScenario<MultiPosParam, MultiPosParamState> s;
        s.param = searchFilesMultiPosParam.get();
        s.expectedState = &expectedSearchFilesState;
        s.args = &multiPosArgs;
        s.argsToConsume = 2;
        ExpectPopulation(s);

        TestExpectedStates();
    }

    TEST_F(MultiPosParamTests, DoesNotPopulateInvalidArguments)
    {
        TestExpectedStates();

        PopulationTestScenario<MultiPosParam, MultiPosParamState> s;
        s.param = searchFilesMultiPosParam.get();
        s.expectedState = &expectedSearchFilesState;
        s.args = &emptyArgs;
        ExpectNoPopulation(s);

        s.args = &optionArgs;
        ExpectNoPopulation(s);

        TestExpectedStates();
    }

    TEST_F(MultiPosParamTests, ReportsCorrectNumberOfArgumentsConsumed)
    {
        EXPECT_EQ(searchFilesMultiPosParam->Consumes(emptyArgs), 0);
        EXPECT_EQ(searchFilesMultiPosParam->Consumes(optionArgs), 0);
        EXPECT_EQ(searchFilesMultiPosParam->Consumes(mixedArgs), 1);
        EXPECT_EQ(searchFilesMultiPosParam->Consumes(multiPosArgs), 2);
    }
}
