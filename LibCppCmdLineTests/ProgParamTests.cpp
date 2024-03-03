// ProgParamTests.cpp - Defines the tests for the ProgParam class.
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

#include "ProgParamTests.h"

namespace CmdLine
{
    ProgParamTests::ProgParamTests()
    {     
        mediaDef.name = mediaProgramName;
        mediaDef.description = mediaProgramDescription;
        mediaProgParam = std::make_unique<ProgParam>(mediaDef);
        expectedMediaProgParamState = GetInitialState(mediaDef);

        searchDef.name = searchProgramName;
        searchDef.description = searchProgramDescription;
        searchProgParam = std::make_unique<ProgParam>(searchDef);
        expectedSearchProgParamState = GetInitialState(searchDef);

        copyDef.name = copyProgramName;
        copyDef.description = copyProgramDescription;
        copyProgParam = std::make_unique<ProgParam>(copyDef);
        expectedCopyProgParamState = GetInitialState(copyDef);

        mediaArgs.push_back(mediaProgramName);
        searchArgs.push_back(searchProgramName);
        copyArgs.push_back(copyProgramName);
    }

    void ProgParamTests::TestExpectedStates()
    {
        ExpectState(*mediaProgParam, expectedMediaProgParamState);
        ExpectState(*searchProgParam, expectedSearchProgParamState);
        ExpectState(*copyProgParam, expectedCopyProgParamState);
    }

    TEST_F(ProgParamTests, CreatesProgParamProperly)
    {
        TestExpectedStates();
    }

    TEST_F(ProgParamTests, ChecksCanPopulateProperly)
    {
        EXPECT_FALSE(mediaProgParam->CanPopulate(emptyArgs));
        EXPECT_FALSE(searchProgParam->CanPopulate(emptyArgs));
        EXPECT_FALSE(copyProgParam->CanPopulate(emptyArgs));
        EXPECT_TRUE(mediaProgParam->CanPopulate(mediaArgs));
        EXPECT_TRUE(searchProgParam->CanPopulate(searchArgs));
        EXPECT_TRUE(copyProgParam->CanPopulate(copyArgs));
    }

    TEST_F(ProgParamTests, PopulatesProperly)
    {
        TestExpectedStates();

        expectedMediaProgParamState.isSpecified = true;
        expectedMediaProgParamState.value = mediaProgramName;
        expectedSearchProgParamState.isSpecified = true;
        expectedSearchProgParamState.value = searchProgramName;
        expectedCopyProgParamState.isSpecified = true;
        expectedCopyProgParamState.value = copyProgramName;

        PopulationTestScenario<ProgParam, ProgParamState> m;
        m.param = mediaProgParam.get();
        m.expectedState = &expectedMediaProgParamState;
        m.args = &mediaArgs;
        ExpectPopulation(m);

        PopulationTestScenario<ProgParam, ProgParamState> s;
        s.param = searchProgParam.get();
        s.expectedState = &expectedSearchProgParamState;
        s.args = &searchArgs;
        ExpectPopulation(s);

        PopulationTestScenario<ProgParam, ProgParamState> c;
        c.param = copyProgParam.get();
        c.expectedState = &expectedCopyProgParamState;
        c.args = &copyArgs;
        ExpectPopulation(c);

        TestExpectedStates();
    }

    TEST_F(ProgParamTests, DoesNotPopulateWithMultipleArgs)
    {
        TestExpectedStates();

        expectedMediaProgParamState.isSpecified = true;
        expectedMediaProgParamState.value = mediaProgramName;

        PopulationTestScenario<ProgParam, ProgParamState> m;
        m.param = mediaProgParam.get();
        m.expectedState = &expectedMediaProgParamState;
        m.args = &mediaArgs;
        ExpectPopulation(m);

        EXPECT_FALSE(mediaProgParam->CanPopulate(copyArgs));
        EXPECT_FALSE(mediaProgParam->Populate(copyArgs));

        TestExpectedStates();
    }

    TEST_F(ProgParamTests, DoesNotPopulateWithEmptyArgs)
    {
        TestExpectedStates();

        PopulationTestScenario<ProgParam, ProgParamState> s;
        s.args = &emptyArgs;
        s.expectedState = &expectedMediaProgParamState;
        s.param = mediaProgParam.get();
        ExpectNoPopulation(s);

        s.expectedState = &expectedSearchProgParamState;
        s.param = searchProgParam.get();
        ExpectNoPopulation(s);

        s.expectedState = &expectedCopyProgParamState;
        s.param = copyProgParam.get();
        ExpectNoPopulation(s);

        TestExpectedStates();
    }

    TEST_F(ProgParamTests, GeneratesHelpProperly)
    {
        std::string expectedMediaHelp{ mediaProgramParamHelpLine };
        std::string expectedSearchHelp{ searchProgramParamHelpLine };
        std::string expectedCopyHelp{ copyProgramParamHelpLine };
        EXPECT_EQ(mediaProgParam->HelpInfo(), expectedMediaHelp);
        EXPECT_EQ(searchProgParam->HelpInfo(), expectedSearchHelp);
        EXPECT_EQ(copyProgParam->HelpInfo(), expectedCopyHelp);
    }

    TEST_F(ProgParamTests, ReportsCorrectNumberOfArgsConsumed)
    {
        EXPECT_EQ(mediaProgParam->Consumes(mediaArgs), 1);
        EXPECT_EQ(searchProgParam->Consumes(searchArgs), 1);
    }
}
