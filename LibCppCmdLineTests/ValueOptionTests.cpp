// ValueOptionTests.cpp - Defines tests for the ValueOptions class.
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

#include "ValueOptionTests.h"

namespace CmdLine
{
    ValueOptionTests::ValueOptionTests()
    {
        DefineOptions();
        DefineOptionParams();
        DefineInitialExpectedStates();
        InitializeOptions();
        InitializeOptionParams();
        AddParamsToOptions();
        AddArgsToQueues();
    }

    void ValueOptionTests::DefineOptions()
    {
        printDef.shortName = printOptionShortName;
        printDef.longName = printOptionLongName;
        printDef.description = printOptionDescription;

        windowsPrintDef = printDef;
        windowsPrintDef.style = Option::Style::Windows;

        editDef.shortName = editOptionShortName;
        editDef.longName = editOptionLongName;
        editDef.description = editOptionDescription;

        // Just re-use the print option descriptor for convinience
        mandatoryDef = printDef;
        mandatoryDef.isMandatory = true;
    }

    void ValueOptionTests::DefineOptionParams()
    {
        songDef.name = songOptionParamName;
        songDef.description = songOptionParamDescription;

        artistDef.name = artistOptionParamName;
        artistDef.description = artistOptionParamDescription;

        albumDef.name = albumOptionParamName;
        albumDef.description = albumOptionParamDescription;
    }

    void ValueOptionTests::DefineInitialExpectedStates()
    {
        expectedPrintOptionState = GetInitialState(printDef);
        expectedEditOptionState = GetInitialState(editDef);
        expectedMandatoryOptionState = GetInitialState(mandatoryDef);
        expectedSongPrintState = GetInitialState(songDef);
        expectedArtistPrintState = GetInitialState(artistDef);
        expectedAlbumPrintState = GetInitialState(albumDef);
        expectedSongEditState = GetInitialState(songDef);
        expectedArtistEditState = GetInitialState(artistDef);
        expectedAlbumEditState = GetInitialState(albumDef);
    }

    void ValueOptionTests::InitializeOptions()
    {
        printOption = std::make_unique<ValueOption>(printDef);
        windowsPrintOption = std::make_unique<ValueOption>(windowsPrintDef);
        editOption = std::make_unique<ValueOption>(editDef);
        mandatoryOption = std::make_unique<ValueOption>(mandatoryDef);
    }

    void ValueOptionTests::InitializeOptionParams()
    {
        songPrintParam = std::make_unique<OptionParam>(songDef);
        songEditParam = std::make_unique<OptionParam>(songDef);
        dupSongPrintParam = std::make_unique<OptionParam>(songDef);

        artistPrintParam = std::make_unique<OptionParam>(artistDef);
        artistEditParam = std::make_unique<OptionParam>(artistDef);

        albumPrintParam = std::make_unique<OptionParam>(albumDef);
        albumEditParam = std::make_unique<OptionParam>(albumDef);
    }

    void ValueOptionTests::ExpectPopulateEditOptionWithArtist()
    {
        expectedEditOptionState.values.push_back(artistNameValuePairArg);
        expectedEditOptionState.isSpecified = true;
        expectedArtistEditState.isSpecified = true;
        expectedArtistEditState.value = artistValue;
        ExpectPopulateEditOption();
    }

    void ValueOptionTests::AddParamsToOptions()
    {
        printOption->Add(songPrintParam.get());
        printOption->Add(artistPrintParam.get());
        printOption->Add(albumPrintParam.get());

        // Although the windows option is getting the same parameter pointers,
        // it will just be used to test the help output
        windowsPrintOption->Add(songPrintParam.get());
        windowsPrintOption->Add(artistPrintParam.get());
        windowsPrintOption->Add(albumPrintParam.get());

        editOption->Add(songEditParam.get());
        editOption->Add(artistEditParam.get());
        editOption->Add(albumEditParam.get());
    }

    void ValueOptionTests::AddArgsToQueues()
    {
        noParamArgs.push_back(unixPrintOptionShortName);

        noParamValueArgs.push_back(unixPrintOptionShortName);
        noParamValueArgs.push_back(songOptionParamName);

        paramValueArgs.push_back(unixEditOptionLongName);
        paramValueArgs.push_back(albumNameValuePairArg);
        paramValueArgs.push_back(unixEditOptionShortName);
        paramValueArgs.push_back(artistNameValuePairArg);

        nonOptionArgs.push_back(songOptionParamName);
        nonOptionArgs.push_back(artistOptionParamName);

        mixedArgs.push_back(unixPrintOptionShortName);
        mixedArgs.push_back(songOptionParamName);
        mixedArgs.push_back(unixPrintOptionLongName);
        mixedArgs.push_back(artistOptionParamName);
        mixedArgs.push_back(unixEditOptionShortName);
        mixedArgs.push_back(albumNameValuePairArg);
        mixedArgs.push_back(artistOptionParamName);

        nonNameValueArgs.push_back(unixPrintOptionShortName);
        nonNameValueArgs.push_back(nonNameValue1);
        nonNameValueArgs.push_back(unixPrintOptionLongName);
        nonNameValueArgs.push_back(nonNameValue2);        
    }

    void ValueOptionTests::TestExpectedStates()
    {
        ExpectState(*printOption, expectedPrintOptionState);
        ExpectState(*editOption, expectedEditOptionState);
        ExpectState(*mandatoryOption, expectedMandatoryOptionState);
        ExpectState(*songPrintParam, expectedSongPrintState);
        ExpectState(*artistPrintParam, expectedArtistPrintState);
        ExpectState(*albumPrintParam, expectedAlbumPrintState);
        ExpectState(*songEditParam, expectedSongEditState);
        ExpectState(*artistEditParam, expectedArtistEditState);
        ExpectState(*albumEditParam, expectedAlbumEditState);
    }

    void ValueOptionTests::ExpectPopulatePrintOptionWithSong()
    {
        expectedPrintOptionState.values.push_back(songOptionParamName);
        expectedPrintOptionState.isSpecified = true;
        expectedSongPrintState.isSpecified = true;

        PopulationTestScenario<ValueOption, ValueOptionState> s;
        s.args = &noParamValueArgs;
        s.param = printOption.get();
        s.expectedState = &expectedPrintOptionState;
        s.argsToConsume = 2;
        ExpectPopulation(s);
    }

    void ValueOptionTests::ExpectPopulatePrintOptionWithNonNameValue()
    {
        expectedPrintOptionState.values.push_back(nonNameValue1);
        expectedPrintOptionState.isSpecified = true;

        PopulationTestScenario<ValueOption, ValueOptionState> s;
        s.args = &nonNameValueArgs;
        s.param = printOption.get();
        s.expectedState = &expectedPrintOptionState;
        s.argsToConsume = 2;
        ExpectPopulation(s);

        expectedPrintOptionState.values.push_back(nonNameValue2);
        ExpectPopulation(s);
    }

    void ValueOptionTests::ExpectPopulateEditOption()
    {
        PopulationTestScenario<ValueOption, ValueOptionState> s;
        s.args = &paramValueArgs;
        s.param = editOption.get();
        s.expectedState = &expectedEditOptionState;
        s.argsToConsume = 2;
        ExpectPopulation(s);
    }

    void ValueOptionTests::ExpectPopulateEditOptionWithAlbum()
    {
        expectedEditOptionState.values.push_back(albumNameValuePairArg);
        expectedEditOptionState.isSpecified = true;
        expectedAlbumEditState.isSpecified = true;
        expectedAlbumEditState.value = albumValue;
        ExpectPopulateEditOption();
    }

    void ValueOptionTests::ExpectInvalidArgsDoNotPopulateEditOption()
    {
        PopulationTestScenario<ValueOption, ValueOptionState> s;
        s.args = &emptyArgs;
        s.param = editOption.get();
        s.expectedState = &expectedEditOptionState;
        ExpectNoPopulation(s);

        s.args = &noParamArgs;
        ExpectNoPopulation(s);

        s.args = &nonOptionArgs;
        ExpectNoPopulation(s);
    }

    TEST_F(ValueOptionTests, CreatesValueOptionProperly)
    {
        TestExpectedStates();
    }

    TEST_F(ValueOptionTests, AddsValueParametersProperly)
    {
        OptionParam* nullParam = nullptr;

        // Use mandatoryOption because we never added parameters to it
        EXPECT_NO_THROW(mandatoryOption->Add(songPrintParam.get()));
        EXPECT_THROW(mandatoryOption->Add(dupSongPrintParam.get()), 
            ValueOption::DuplicateOptionParam);
        EXPECT_NO_THROW(mandatoryOption->Add(artistPrintParam.get()));
        EXPECT_NO_THROW(mandatoryOption->Add(albumPrintParam.get()));
        EXPECT_THROW(mandatoryOption->Add(nullParam), 
            ValueOption::NullOptionParam);
    }

    TEST_F(ValueOptionTests, ChecksCanPopulateProperly)
    {
        EXPECT_TRUE(printOption->CanPopulate(noParamValueArgs));
        EXPECT_TRUE(editOption->CanPopulate(paramValueArgs));
        EXPECT_FALSE(printOption->CanPopulate(emptyArgs));
        EXPECT_FALSE(printOption->CanPopulate(noParamArgs));
        EXPECT_FALSE(printOption->CanPopulate(nonOptionArgs));
    }

    TEST_F(ValueOptionTests, PopulatesOptionsProperly)
    {   
        TestExpectedStates();
        ExpectPopulatePrintOptionWithSong();
        ExpectPopulateEditOptionWithAlbum();
        TestExpectedStates();
    }

    TEST_F(ValueOptionTests, PopulatesOptionsWithNonNameValues)
    {
        TestExpectedStates();
        ExpectPopulatePrintOptionWithNonNameValue();
        TestExpectedStates();
    }

    TEST_F(ValueOptionTests, AddsValuesToAlreadyPopulatedOptions)
    {
        TestExpectedStates();
        ExpectPopulateEditOptionWithAlbum();
        ExpectPopulateEditOptionWithArtist();
        TestExpectedStates();
    }

    TEST_F(ValueOptionTests, DoesNotPopulateInvalidArgs)
    {
        TestExpectedStates();
        ExpectInvalidArgsDoNotPopulateEditOption();
        TestExpectedStates();
    }

    TEST_F(ValueOptionTests, DoesNotAddInvalidArgsToAlreadyPopulatedOptions)
    {
        TestExpectedStates();
        ExpectPopulateEditOptionWithAlbum();
        ExpectInvalidArgsDoNotPopulateEditOption();
        TestExpectedStates();
    }

    TEST_F(ValueOptionTests, ConstructorEnforcesInvariants)
    {
        TestOptionInvariants<ValueOption::Definition, ValueOption>();
    }

    TEST_F(ValueOptionTests, GenereatesHelpInfoProperly)
    {
        std::string up = GenerateExpectedUnixPrintOptionHelpInfo();
        std::string upnp = GenerateExpectedUnixPrintOptionHelpInfoNoParams();
        std::string ue = GenerateExpectedUnixEditOptionHelpInfo();
        std::string wp = GenerateExpectedWindowsPrintOptionHelpInfo();

        EXPECT_EQ(printOption->HelpInfo(), up);

        // Mandatory is based on printOption but without OptionParameters.
        EXPECT_EQ(mandatoryOption->HelpInfo(), upnp);

        EXPECT_EQ(editOption->HelpInfo(), ue);
        EXPECT_EQ(windowsPrintOption->HelpInfo(), wp);
    }

    TEST_F(ValueOptionTests, ReportsCorrectNumberOfArgsConsumed)
    {
        EXPECT_EQ(printOption->Consumes(noParamArgs), 2);
        EXPECT_EQ(printOption->Consumes(paramValueArgs), 2);
    }
}
