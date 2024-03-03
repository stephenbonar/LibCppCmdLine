// PosParamTests.cpp - Defines the tests for the PosParam class.
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

#include "PosParamTests.h"

namespace CmdLine
{
    PosParamTests::PosParamTests()
    {
        searchPatternDef.name = searchPatternPosName;
        searchPatternDef.description = searchPatternPosDescription;
        searchPatternPosParam = std::make_unique<PosParam>(searchPatternDef);
        expectedSearchPatternState = GetInitialState(searchPatternDef);

        copyDestinationDef.name = copyDestinationPosName;
        copyDestinationDef.description = copyDestinationPosDescription;
        copyDestinationPosParam = std::make_unique<PosParam>(
            copyDestinationDef);
        expectedCopyDestinationState = GetInitialState(copyDestinationDef);

        mandatoryDef = copyDestinationDef;
        mandatoryDef.isMandatory = true;
        mandatoryPosParam = std::make_unique<PosParam>(mandatoryDef);
        expectedMandatoryState = GetInitialState(mandatoryDef);

        optionArgs.push_back(unixVerboseOptionShortName);

        posArgs.push_back(searchPatternText);
        posArgs.push_back(copyDestinationFileName);
    }

    void PosParamTests::TestExpectedStates()
    {
        ExpectState(*searchPatternPosParam, expectedSearchPatternState);
        ExpectState(*copyDestinationPosParam, expectedCopyDestinationState);
        ExpectState(*mandatoryPosParam, expectedMandatoryState);
    }

    TEST_F(PosParamTests, CreatesPosParamProperly)
    {
        TestExpectedStates();
    }

    TEST_F(PosParamTests, ConstructorEnforcesInvariants)
    {
        TestParamInvariants<PosParam::Definition, PosParam>();
    }

    TEST_F(PosParamTests, GeneratesHelpInfoProperly)
    {
        std::string expectedHelpInfo{ searchPatternPosHelpLine };
        EXPECT_EQ(searchPatternPosParam->HelpInfo(), expectedHelpInfo);
    }

    TEST_F(PosParamTests, ChecksCanPopulateProperly)
    {
        EXPECT_FALSE(searchPatternPosParam->CanPopulate(emptyArgs));
        EXPECT_FALSE(searchPatternPosParam->CanPopulate(optionArgs));
        EXPECT_TRUE(searchPatternPosParam->CanPopulate(posArgs));
    }

    TEST_F(PosParamTests, PopulatesPosParamProperly)
    {
        TestExpectedStates();

        expectedSearchPatternState.isSpecified = true;
        expectedSearchPatternState.value = searchPatternText;
        expectedCopyDestinationState.isSpecified = true;
        expectedCopyDestinationState.value = copyDestinationFileName;
        
        PopulationTestScenario<PosParam, PosParamState> s;
        s.param = searchPatternPosParam.get();
        s.expectedState = &expectedSearchPatternState;
        s.args = &posArgs;
        ExpectPopulation(s);

        PopulationTestScenario<PosParam, PosParamState> d;
        d.param = copyDestinationPosParam.get();
        d.expectedState = &expectedCopyDestinationState;
        d.args = &posArgs;
        ExpectPopulation(d);

        TestExpectedStates();
    }

    TEST_F(PosParamTests, DoesNotPopulateInvalidArgs)
    {
        TestExpectedStates();

        PopulationTestScenario<PosParam, PosParamState> s;
        s.param = searchPatternPosParam.get();
        s.expectedState = &expectedSearchPatternState;
        s.args = &emptyArgs;
        ExpectNoPopulation(s);

        s.args = &optionArgs;
        ExpectNoPopulation(s);

        TestExpectedStates();
    }

    TEST_F(PosParamTests, DoesNotPopulateWithMultipleArgs)
    {
        TestExpectedStates();

        expectedSearchPatternState.isSpecified = true;
        expectedSearchPatternState.value = searchPatternText;

        PopulationTestScenario<PosParam, PosParamState> s;
        s.param = searchPatternPosParam.get();
        s.expectedState = &expectedSearchPatternState;
        s.args = &posArgs;
        ExpectPopulation(s);

        EXPECT_FALSE(s.param->CanPopulate(posArgs));
        EXPECT_FALSE(s.param->Populate(posArgs));

        TestExpectedStates();
    }

    TEST_F(PosParamTests, ReportsCorrectNumberOfArgsConsumed)
    {
        EXPECT_EQ(searchPatternPosParam->Consumes(posArgs), 1);
        EXPECT_EQ(copyDestinationPosParam->Consumes(posArgs), 1);
    }
}
