// OptionTest.cpp - Defines the tests for the Options class.
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

#include "OptionTests.h"

namespace CmdLine
{ 
    OptionTests::OptionTests()
    {
        DefineOptions();
        InitializeOptions();
        DefineInitialExpectedStates();
        AddArgsToQueues();
    }

    void OptionTests::DefineOptions()
    {
        unixVerboseDef.shortName = verboseOptionShortName;
        unixVerboseDef.longName = verboseOptionLongName;
        unixVerboseDef.description = verboseOptionDescription;

        windowsVerboseDef = unixVerboseDef;
        windowsVerboseDef.style = Option::Style::Windows;

        // Just re-use the verbose option descriptor for convinience
        mandatoryDef = unixVerboseDef;
        mandatoryDef.isMandatory = true;

        unixShortDef.shortName = shortOptionName;
        unixShortDef.description = shortOptionDescription;

        windowsShortDef = unixShortDef;
        windowsShortDef.style = Option::Style::Windows;

        unixLongDef.longName = longOptionName;
        unixLongDef.description = longOptionDescription;

        windowsLongDef = unixLongDef;
        windowsLongDef.style = Option::Style::Windows;
    }

    void OptionTests::InitializeOptions()
    {
        unixVerboseOption = std::make_unique<Option>(unixVerboseDef);
        dupUnixVerboseOption = std::make_unique<Option>(unixVerboseDef);

        windowsVerboseOption = std::make_unique<Option>(windowsVerboseDef);
        dupWindowsVerboseOption = std::make_unique<Option>(windowsVerboseDef);

        mandatoryOption = std::make_unique<Option>(mandatoryDef);
        unixShortOption = std::make_unique<Option>(unixShortDef);
        windowsShortOption = std::make_unique<Option>(windowsShortDef);
        unixLongOption = std::make_unique<Option>(unixLongDef);
        windowsLongOption = std::make_unique<Option>(windowsLongDef);
    }

    void OptionTests::DefineInitialExpectedStates()
    {
        expectedUnixVerboseState = GetInitialState(unixVerboseDef);
        expectedDupUnixVerboseState = GetInitialState(unixVerboseDef);

        expectedWindowsVerboseState = GetInitialState(windowsVerboseDef);
        expectedDupWindowsVerboseState = GetInitialState(windowsVerboseDef);

        expectedMandatoryState = GetInitialState(mandatoryDef);
        expectedUnixShortState = GetInitialState(unixShortDef);
        expectedUnixLongState = GetInitialState(unixLongDef);
        expectedWindowsShortState = GetInitialState(windowsShortDef);
        expectedWindowsLongState = GetInitialState(windowsLongDef);
    }

    void OptionTests::AddArgsToQueues()
    {
        unixOptionArgs.push_back(unixVerboseOptionShortName);
        unixOptionArgs.push_back(unixVerboseOptionLongName);

        windowsOptionArgs.push_back(windowsVerboseOptionShortName);
        windowsOptionArgs.push_back(windowsVerboseOptionLongName);

        nonOptionArgs.push_back(songOptionParamName);

        mixedArgs.push_back(unixVerboseOptionShortName);
        mixedArgs.push_back(songOptionParamName);
        mixedArgs.push_back(windowsVerboseOptionShortName);
        mixedArgs.push_back(unixVerboseOptionLongName);
    }

    void OptionTests::TestExpectedStates()
    {
        ExpectState(*unixVerboseOption, expectedUnixVerboseState);
        ExpectState(*windowsVerboseOption, expectedWindowsVerboseState);
        ExpectState(*dupUnixVerboseOption, expectedDupUnixVerboseState);
        ExpectState(*dupWindowsVerboseOption, expectedDupWindowsVerboseState);
        ExpectState(*mandatoryOption, expectedMandatoryState);
        ExpectState(*unixShortOption, expectedUnixShortState);
        ExpectState(*unixLongOption, expectedUnixLongState);
        ExpectState(*windowsShortOption, expectedWindowsShortState);
        ExpectState(*windowsLongOption, expectedWindowsLongState);
    }

    TEST_F(OptionTests, ConstructorEnforcesInvariants)
    {
        TestOptionInvariants<Option::Definition, Option>();
    }
    
    TEST_F(OptionTests, CreatesOptionsProperly)
    {
        TestExpectedStates();
    }

    TEST_F(OptionTests, GeneratesUnixHelpInfoProperly)
    {
        std::string expectedHelpInfo{ unixVerboseOptionHelpLine };
        EXPECT_EQ(unixVerboseOption->HelpInfo(), expectedHelpInfo);
    }

    TEST_F(OptionTests, GenerateWindowsHelpInfoProperly)
    {
        std::string expectedHelpInfo{ windowsVerboseOptionHelpLine };
        EXPECT_EQ(windowsVerboseOption->HelpInfo(), expectedHelpInfo);
    }

    TEST_F(OptionTests, GenerateUnixShortNameHelpInfoProperly)
    {
        std::string expectedHelpInfo{ unixShortOptionHelpLine };
        EXPECT_EQ(unixShortOption->HelpInfo(), expectedHelpInfo);
    }

    TEST_F(OptionTests, GenerateUnixLongNameHelpInfoProperly)
    {
        std::string expectedHelpInfo{ unixLongOptionHelpLine };
        EXPECT_EQ(unixLongOption->HelpInfo(), expectedHelpInfo);
    }

    TEST_F(OptionTests, GenerateWindowsShortNameHelpInfoProperly)
    {
        std::string expectedHelpInfo{ windowsShortOptionHelpLine };
        EXPECT_EQ(windowsShortOption->HelpInfo(), expectedHelpInfo);
    }

    TEST_F(OptionTests, GenerateWindowsLongNameHelpInfoProperly)
    {
        std::string expectedHelpInfo{ windowsLongOptionHelpLine };
        EXPECT_EQ(windowsLongOption->HelpInfo(), expectedHelpInfo);
    }

    TEST_F(OptionTests, GeneratesNameProperly)
    {
        EXPECT_EQ(unixVerboseOption->Name(), unixVerboseOptionShortName);
        EXPECT_EQ(windowsVerboseOption->Name(), windowsVerboseOptionShortName);
        EXPECT_EQ(unixShortOption->Name(), unixShortOptionName);
        EXPECT_EQ(unixLongOption->Name(), unixLongOptionName);
        EXPECT_EQ(windowsShortOption->Name(), windowsShortOptionName);
        EXPECT_EQ(windowsLongOption->Name(), windowsLongOptionName);
    }

    TEST_F(OptionTests, PopulatesUnixOptionProperly)
    {
        TestExpectedStates();

        expectedUnixVerboseState.isSpecified = true;
        expectedDupUnixVerboseState.isSpecified = true;

        PopulationTestScenario<Option, OptionState> sShortName;
        sShortName.param = unixVerboseOption.get();
        sShortName.args = &unixOptionArgs;
        sShortName.expectedState = &expectedUnixVerboseState;
        ExpectPopulation(sShortName);

        PopulationTestScenario<Option, OptionState> sLongName;
        sLongName.param = dupUnixVerboseOption.get();
        sLongName.args = &unixOptionArgs;
        sLongName.expectedState = &expectedDupUnixVerboseState;
        ExpectPopulation(sLongName);

        TestExpectedStates();
    }

    TEST_F(OptionTests, PopulatesWindowsOptionProperly)
    {
        TestExpectedStates();

        expectedWindowsVerboseState.isSpecified = true;
        expectedDupWindowsVerboseState.isSpecified = true;

        PopulationTestScenario<Option, OptionState> sShortName;
        sShortName.param = windowsVerboseOption.get();
        sShortName.args = &windowsOptionArgs;
        sShortName.expectedState = &expectedWindowsVerboseState;
        ExpectPopulation(sShortName);

        PopulationTestScenario<Option, OptionState> sLongName;
        sLongName.param = dupWindowsVerboseOption.get();
        sLongName.args = &windowsOptionArgs;
        sLongName.expectedState = &expectedDupWindowsVerboseState;
        ExpectPopulation(sLongName);

        TestExpectedStates();
    }

    TEST_F(OptionTests, DoesNotPopulateWithInvalidArguments)
    {
        TestExpectedStates();

        PopulationTestScenario<Option, OptionState> sUnix;
        sUnix.param = unixVerboseOption.get();
        sUnix.expectedState = &expectedUnixVerboseState;
        sUnix.args = &nonOptionArgs;
        ExpectNoPopulation(sUnix);

        PopulationTestScenario<Option, OptionState> sWindows;
        sWindows.param = windowsVerboseOption.get();
        sWindows.expectedState = &expectedWindowsVerboseState;
        sWindows.args = &nonOptionArgs;
        ExpectNoPopulation(sWindows);

        sUnix.args = &emptyArgs;
        sWindows.args = &emptyArgs;
        ExpectNoPopulation(sUnix);
        ExpectNoPopulation(sWindows);

        TestExpectedStates();
    }

    TEST_F(OptionTests, HandlesMixedArgumentsProperly)
    {
        TestExpectedStates();

        expectedUnixVerboseState.isSpecified = true;

        PopulationTestScenario<Option, OptionState> sOption;
        sOption.param = unixVerboseOption.get();
        sOption.expectedState = &expectedUnixVerboseState;
        sOption.args = &mixedArgs;
        ExpectPopulation(sOption);

        PopulationTestScenario<Option, OptionState> sNonOption;
        sNonOption.param = dupUnixVerboseOption.get();
        sNonOption.expectedState = &expectedDupUnixVerboseState;
        sNonOption.args = &mixedArgs;
        ExpectNoPopulation(sNonOption);

        TestExpectedStates();
    }

    TEST_F(OptionTests, ChecksCanPopulateProperly)
    {
        EXPECT_EQ(unixVerboseOption->CanPopulate(unixOptionArgs), true);
        EXPECT_EQ(unixVerboseOption->CanPopulate(windowsOptionArgs), false);
        EXPECT_EQ(unixVerboseOption->CanPopulate(nonOptionArgs), false);
        EXPECT_EQ(unixVerboseOption->CanPopulate(emptyArgs), false);

        EXPECT_EQ(windowsVerboseOption->CanPopulate(unixOptionArgs), false);
        EXPECT_EQ(windowsVerboseOption->CanPopulate(windowsOptionArgs), true);
        EXPECT_EQ(windowsVerboseOption->CanPopulate(nonOptionArgs), false);
        EXPECT_EQ(windowsVerboseOption->CanPopulate(emptyArgs), false);
    }

    TEST_F(OptionTests, DetectsOptionArguemntsProperly)
    {
        EXPECT_EQ(IsOption(unixPrintOptionShortName), true);
        EXPECT_EQ(IsOption(unixPrintOptionLongName), true);
        EXPECT_EQ(IsOption(windowsPrintOptionShortName), true);
        EXPECT_EQ(IsOption(windowsPrintOptionLongName), true);
        EXPECT_EQ(IsOption(searchPatternText), false);
        EXPECT_EQ(IsOption(fullFilePath), false);
    }

    TEST_F(OptionTests, ReportsCorrectNumberOfArgumentsConsumed)
    {
        EXPECT_EQ(unixVerboseOption->Consumes(unixOptionArgs), 1);
        EXPECT_EQ(windowsVerboseOption->Consumes(windowsOptionArgs), 1);
    }
}
