// ParserTests.cpp - Defines the tests for the Parser class.
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

#include "ParserTests.h"

namespace CmdLine
{
    ParserTests::ParserTests()
    {
        DefineProgParams();
        DefineOptions(Option::Style::Unix);
        DefineOptionParams();
        DefinePosParams();

        InitializeExpectedStates();
        InitializeProgParams();
        InitializeOptions();
        InitializeOptionParams();
        InitializePosParams();
        InitializeProgramInfo();
        InitializeParsers(Option::Style::Unix);
        
        AddParamsToOptions();
    }

    void ParserTests::DefineProgParams()
    {
        mediaProgramDef.name = mediaProgramName;
        mediaProgramDef.description = mediaProgramDescription;
        
        searchProgramDef.name = searchProgramName;
        searchProgramDef.description = searchProgramDescription;

        copyProgramDef.name = copyProgramName;
        copyProgramDef.description = copyProgramDescription;

        nameLookupProgramDef.name = nameLookupProgramName;
        nameLookupProgramDef.description = nameLookupProgramDescription;
    }

    void ParserTests::DefineOptions(Option::Style s)
    {
        if (s == Option::Style::Windows)
        {
            mediaPrintDef.style = s;
            mediaEditDef.style = s;
            verboseDef.style = s;
            searchIgnoreCaseDef.style = s;
        }
       
        mediaPrintDef.shortName = printOptionShortName;
        mediaPrintDef.longName = printOptionLongName;
        mediaPrintDef.description = printOptionDescription;
        
        mediaEditDef.shortName = editOptionShortName;
        mediaEditDef.longName = editOptionLongName;
        mediaEditDef.description = editOptionDescription;

        verboseDef.shortName = verboseOptionShortName;
        verboseDef.longName = verboseOptionLongName;
        verboseDef.description = verboseOptionDescription;

        searchIgnoreCaseDef.shortName = ignoreCaseOptionShortName;
        searchIgnoreCaseDef.longName = ignoreCaseOptionLongName;
        searchIgnoreCaseDef.description = ignoreCaseDescription;
    }

    void ParserTests::DefineOptionParams()
    {
        songDef.name = songOptionParamName;
        songDef.description = songOptionParamDescription;

        albumDef.name = albumOptionParamName;
        albumDef.description = albumOptionParamDescription;

        artistDef.name = artistOptionParamName;
        artistDef.description = artistOptionParamDescription;
    }

    void ParserTests::DefinePosParams()
    {
        mediaFilesDef.name = mediaFilesMultiPosName;
        mediaFilesDef.description = mediaFilesMultiPosDescription;
        mediaFilesDef.isMandatory = true;

        copySourceDef.name = copySourceMultiPosName;
        copySourceDef.description = copySourceMultiPosDescription;
        copySourceDef.isMandatory = true;
        copySourceDef.order = MultiPosParam::ParsingOrder::AfterOptions;

        searchFilesDef.name = searchFilesMultiPosName;
        searchFilesDef.description = searchFilesMultiPosDescription;
        searchFilesDef.isMandatory = true;

        searchPatternDef.name = searchPatternPosName;
        searchPatternDef.description = searchPatternPosDescription;
        searchPatternDef.isMandatory = true;

        copyDestinationDef.name = copyDestinationPosName;
        copyDestinationDef.description = copyDestinationPosDescription;
        copyDestinationDef.isMandatory = true;

        hostnameDef.name = hostnamePosName;
        hostnameDef.description = hostnamePosDescription;
        hostnameDef.isMandatory = true;
    }

    void ParserTests::InitializeProgramInfo()
    {
        mediaInfo.program = mediaProgParam.get();
        mediaInfo.options.push_back(mediaPrintOption.get());
        mediaInfo.options.push_back(mediaEditOption.get());
        mediaInfo.options.push_back(mediaVerboseOption.get());
        mediaInfo.multiPosParam = mediaFilesMultiPos.get();

        copyInfo.program = copyProgParam.get();
        copyInfo.options.push_back(copyVerboseOption.get());
        copyInfo.multiPosParam = copySourcePos.get();
        copyInfo.positionals.push_back(copyDestinationPos.get());

        searchInfo.program = searchProgParam.get();
        searchInfo.options.push_back(searchIgnoreCaseOption.get());
        searchInfo.multiPosParam = searchFilesMultiPos.get();
        searchInfo.positionals.push_back(searchPatternPos.get());

        nameLookupInfo.program = nameLookupProgParam.get();
        nameLookupInfo.options.push_back(nameLookupVerboseOption.get());
        nameLookupInfo.positionals.push_back(hostnamePos.get());
    }

    void ParserTests::InitializeExpectedStates()
    {
        expectedMediaProgramState = GetInitialState(mediaProgramDef);
        expectedSearchProgramState = GetInitialState(searchProgramDef);
        expectedCopyProgramState = GetInitialState(copyProgramDef);
        expectedNameLookupProgramState = GetInitialState(nameLookupProgramDef);

        expectedMediaPrintState = GetInitialState(mediaPrintDef);
        expectedDupMediaPrintState = GetInitialState(mediaPrintDef);
        expectedMediaEditState = GetInitialState(mediaEditDef);
        expectedMediaVerboseState = GetInitialState(verboseDef);
        expectedCopyVerboseState = GetInitialState(verboseDef);
        expectedNameLookupVerboseState = GetInitialState(verboseDef);
        expectedSearchIgnoreCaseState = GetInitialState(searchIgnoreCaseDef);

        expectedSongPrintState = GetInitialState(songDef);
        expectedArtistPrintState = GetInitialState(artistDef);
        expectedAlbumPrintState = GetInitialState(albumDef);
        expectedSongEditState = GetInitialState(songDef);
        expectedArtistEditState = GetInitialState(artistDef);
        expectedAlbumEditState = GetInitialState(albumDef);

        expectedMediaFilesState = GetInitialState(mediaFilesDef);
        expectedSearchFilesState = GetInitialState(searchFilesDef);
        expectedSearchPatternState = GetInitialState(searchPatternDef);
        expectedCopySourceState = GetInitialState(copySourceDef);
        expectedCopyDestinationState = GetInitialState(copyDestinationDef);
        expectedDupCopyDestinationState = GetInitialState(copyDestinationDef);
        expectedHostnameState = GetInitialState(hostnameDef);
    }

    void ParserTests::InitializeProgParams()
    {
        mediaProgParam = std::make_unique<ProgParam>(mediaProgramDef);
        searchProgParam = std::make_unique<ProgParam>(searchProgramDef);
        copyProgParam = std::make_unique<ProgParam>(copyProgramDef);
        nameLookupProgParam = std::make_unique<ProgParam>(
            nameLookupProgramDef);
    }

    void ParserTests::InitializeOptions()
    {
        mediaPrintOption = std::make_unique<ValueOption>(mediaPrintDef);
        dupMediaPrintOption = std::make_unique<ValueOption>(mediaPrintDef);

        mediaEditOption = std::make_unique<ValueOption>(mediaEditDef);

        mediaVerboseOption = std::make_unique<Option>(verboseDef);
        copyVerboseOption = std::make_unique<Option>(verboseDef);
        nameLookupVerboseOption = std::make_unique<Option>(verboseDef);

        searchIgnoreCaseOption = std::make_unique<Option>(searchIgnoreCaseDef);
    }

    void ParserTests::InitializeOptionParams()
    {
        songPrintOptionParam = std::make_unique<OptionParam>(songDef);
        songEditOptionParam = std::make_unique<OptionParam>(songDef);
        albumPrintOptionParam = std::make_unique<OptionParam>(albumDef);
        albumEditOptionParam = std::make_unique<OptionParam>(albumDef);
        artistPrintOptionParam = std::make_unique<OptionParam>(artistDef);
        artistEditOptionParam = std::make_unique<OptionParam>(artistDef);
    }

    void ParserTests::InitializePosParams()
    {
        mediaFilesMultiPos = std::make_unique<MultiPosParam>(mediaFilesDef);
        copySourcePos = std::make_unique<MultiPosParam>(copySourceDef);
        searchFilesMultiPos = std::make_unique<MultiPosParam>(searchFilesDef);
        searchPatternPos = std::make_unique<PosParam>(searchPatternDef);
        copyDestinationPos = std::make_unique<PosParam>(copyDestinationDef);
        dupCopyDestinationPos = std::make_unique<PosParam>(copyDestinationDef);
        hostnamePos = std::make_unique<PosParam>(hostnameDef);
    }

    void ParserTests::InitializeParsers(Option::Style s)
    {
        ProgParam* mp = mediaProgParam.get();
        ProgParam* sp = searchProgParam.get();
        ProgParam* cp = copyProgParam.get();
        ProgParam* np = nameLookupProgParam.get();

        if (s == Option::Style::Windows)
        {
            mediaParser = std::make_unique<Parser>(mp, windowsMediaArgs);
            searchParser = std::make_unique<Parser>(sp, windowsSearchArgs);
            copyParser = std::make_unique<Parser>(cp, windowsCopyArgs);
            nameLookupParser = std::make_unique<Parser>(np, 
                windowsNameLookupArgs);
            invalidNameLookupParser = std::make_unique<Parser>(np, 
                windowsInvalidNameLookupArgs);
            shortHelpNameLookupParser = std::make_unique<Parser>(np, 
                windowsNameLookupShortHelpArgs);
            longHelpNameLookupParser = std::make_unique<Parser>(np, 
                windowsNameLookupLongHelpArgs);
        }
        else
        {
            mediaParser = std::make_unique<Parser>(mp, unixMediaArgs);
            searchParser = std::make_unique<Parser>(sp, unixSearchArgs);
            copyParser = std::make_unique<Parser>(cp, unixCopyArgs);
            nameLookupParser = std::make_unique<Parser>(np, 
                unixNameLookupArgs);
            invalidNameLookupParser = std::make_unique<Parser>(np, 
                unixInvalidNameLookupArgs);
            shortHelpNameLookupParser = std::make_unique<Parser>(np, 
                unixNameLookupShortHelpArgs);
            longHelpNameLookupParser = std::make_unique<Parser>(np, 
                unixNameLookupLongHelpArgs);
        }
    }

    void ParserTests::AddParamsToOptions()
    {
        mediaPrintOption->Add(songPrintOptionParam.get());
        mediaPrintOption->Add(artistPrintOptionParam.get());
        mediaPrintOption->Add(albumPrintOptionParam.get());

        mediaEditOption->Add(songEditOptionParam.get());
        mediaEditOption->Add(artistEditOptionParam.get());
        mediaEditOption->Add(albumEditOptionParam.get());
    }

    void ParserTests::AddParamsToParsers()
    {
        mediaParser->Add(mediaPrintOption.get());
        mediaParser->Add(mediaEditOption.get());
        mediaParser->Add(mediaVerboseOption.get());
        mediaParser->Set(mediaFilesMultiPos.get());

        copyParser->Add(copyVerboseOption.get());
        copyParser->Add(copyDestinationPos.get());
        copyParser->Set(copySourcePos.get());

        searchParser->Add(searchIgnoreCaseOption.get());
        searchParser->Add(searchPatternPos.get());
        searchParser->Set(searchFilesMultiPos.get());

        nameLookupParser->Add(nameLookupVerboseOption.get());
        nameLookupParser->Add(hostnamePos.get());

        invalidNameLookupParser->Add(nameLookupVerboseOption.get());
        invalidNameLookupParser->Add(hostnamePos.get());

        shortHelpNameLookupParser->Add(nameLookupVerboseOption.get());
        shortHelpNameLookupParser->Add(hostnamePos.get());

        longHelpNameLookupParser->Add(nameLookupVerboseOption.get());
        longHelpNameLookupParser->Add(hostnamePos.get());
    }

    void ParserTests::TestExpectedStates()
    {
        ExpectState(*mediaProgParam, expectedMediaProgramState);
        ExpectState(*searchProgParam, expectedSearchProgramState);
        ExpectState(*copyProgParam, expectedCopyProgramState);
        ExpectState(*nameLookupProgParam, expectedNameLookupProgramState);
        ExpectState(*mediaPrintOption, expectedMediaPrintState);
        ExpectState(*dupMediaPrintOption, expectedDupMediaPrintState);
        ExpectState(*mediaEditOption, expectedMediaEditState);
        ExpectState(*mediaVerboseOption, expectedMediaVerboseState);
        ExpectState(*searchIgnoreCaseOption, expectedSearchIgnoreCaseState);
        ExpectState(*nameLookupVerboseOption, expectedNameLookupVerboseState);
        ExpectState(*songPrintOptionParam, expectedSongPrintState);
        ExpectState(*artistPrintOptionParam, expectedArtistPrintState);
        ExpectState(*albumPrintOptionParam, expectedAlbumPrintState);
        ExpectState(*songEditOptionParam, expectedSongEditState);
        ExpectState(*artistEditOptionParam, expectedArtistEditState);
        ExpectState(*albumEditOptionParam, expectedAlbumEditState);
        ExpectState(*mediaFilesMultiPos, expectedMediaFilesState);
        ExpectState(*searchFilesMultiPos, expectedSearchFilesState);
        ExpectState(*searchPatternPos, expectedSearchPatternState);
        ExpectState(*copySourcePos, expectedCopySourceState);
        ExpectState(*copyDestinationPos, expectedCopyDestinationState);
        ExpectState(*dupCopyDestinationPos, expectedDupCopyDestinationState);
        ExpectState(*hostnamePos, expectedHostnameState);
    }

    void ParserTests::ReconfigForWindowsIfNeeded(Option::Style s)
    {
        if (s == Option::Style::Windows)
        {
            InitializeParsers(s);
            DefineOptions(s);
            InitializeExpectedStates();
        }
    }

    void ParserTests::SetParsersWithWindowsOptionsIfNeeded(Option::Style s)
    {
        if (s == Option::Style::Windows)
        {
            mediaParser->Set(s);
            searchParser->Set(s);
            copyParser->Set(s);
            nameLookupParser->Set(s);
            invalidNameLookupParser->Set(s);
            shortHelpNameLookupParser->Set(s);
            longHelpNameLookupParser->Set(s);

            dupMediaPrintOption->Set(s);
            ExpectState(*mediaEditOption, expectedMediaEditState);
            ExpectState(*mediaVerboseOption, expectedMediaVerboseState);
            ExpectState(*searchIgnoreCaseOption, expectedSearchIgnoreCaseState);
            ExpectState(*nameLookupVerboseOption, expectedNameLookupVerboseState);
        }
    }

    void ParserTests::ExpectMediaArgsParsed(Option::Style s)
    {
        ReconfigForWindowsIfNeeded(s);
        AddParamsToParsers();
        SetParsersWithWindowsOptionsIfNeeded(s);

        TestExpectedStates();
        
        EXPECT_EQ(mediaParser->Parse(), Parser::Status::Success);

        expectedMediaProgramState.isSpecified = true;
        expectedMediaProgramState.value = mediaProgramName;
        expectedMediaPrintState.isSpecified = true;
        expectedMediaPrintState.values.push_back(songOptionParamName);
        expectedMediaPrintState.values.push_back(artistOptionParamName);
        expectedSongPrintState.isSpecified = true;
        expectedArtistPrintState.isSpecified = true;
        expectedMediaEditState.isSpecified = true;
        expectedMediaEditState.values.push_back(albumNameValuePairArg);
        expectedAlbumEditState.isSpecified = true;
        expectedAlbumEditState.value = albumValue;
        expectedMediaVerboseState.isSpecified = true;
        expectedMediaFilesState.isSpecified = true;
        expectedMediaFilesState.values.push_back(mediaFileName1);
        expectedMediaFilesState.values.push_back(mediaFileName2);

        TestExpectedStates();
    }

    void ParserTests::ExpectCopyArgsParsed(Option::Style s)
    {
        ReconfigForWindowsIfNeeded(s);
        AddParamsToParsers();
        SetParsersWithWindowsOptionsIfNeeded(s);

        TestExpectedStates();

        EXPECT_EQ(copyParser->Parse(), Parser::Status::Success);

        expectedCopyProgramState.isSpecified = true;
        expectedCopyProgramState.value = copyProgramName;
        expectedCopyVerboseState.isSpecified = true;
        expectedCopySourceState.isSpecified = true;
        expectedCopySourceState.values.push_back(copySourceFileName1);
        expectedCopySourceState.values.push_back(copySourceFileName2);
        expectedCopyDestinationState.isSpecified = true;
        expectedCopyDestinationState.value = copyDestinationFileName;

        TestExpectedStates();
    }

    void ParserTests::ExpectSearchArgsParsed(Option::Style s)
    {
        ReconfigForWindowsIfNeeded(s);
        AddParamsToParsers();
        SetParsersWithWindowsOptionsIfNeeded(s);

        TestExpectedStates();

        EXPECT_EQ(searchParser->Parse(), Parser::Status::Success);

        expectedSearchProgramState.isSpecified = true;
        expectedSearchProgramState.value = searchProgramName;
        expectedSearchIgnoreCaseState.isSpecified = true;
        expectedSearchPatternState.isSpecified = true;
        expectedSearchPatternState.value = searchPatternText;
        expectedSearchFilesState.isSpecified = true;
        expectedSearchFilesState.values.push_back(searchFileName1);
        expectedSearchFilesState.values.push_back(searchFileName2);

        TestExpectedStates();
    }

    void ParserTests::ExpectNameLookupArgsParsed(Option::Style s)
    {
        ReconfigForWindowsIfNeeded(s);
        AddParamsToParsers();
        SetParsersWithWindowsOptionsIfNeeded(s);

        TestExpectedStates();

        EXPECT_EQ(nameLookupParser->Parse(), Parser::Status::Success);

        expectedNameLookupProgramState.isSpecified = true;
        expectedNameLookupProgramState.value = nameLookupProgramName;
        expectedNameLookupVerboseState.isSpecified = true;
        expectedHostnameState.isSpecified = true;
        expectedHostnameState.value = hostname;

        TestExpectedStates();
    }

    TEST_F(ParserTests, ConstructorEnforcesInvariants)
    {
        // Invariants enforced:
        // @invariant There is at least one argument (program name)
        // @invariant Options, Positionals and ProgramParameters can't be null

        std::vector<std::string> empty;
        std::vector<std::string>& a = unixMediaArgs;
        ProgParam* p = mediaProgParam.get();

        EXPECT_NO_THROW(Parser(p, a));
        EXPECT_THROW(Parser(p, empty), Parser::EmptyArguments);
        EXPECT_THROW(Parser(nullptr, a), Parser::NullParameter);
        EXPECT_THROW(Parser(nullptr, empty), Parser::NullParameter);
    }

    TEST_F(ParserTests, AddMethodEnforcesInvariantsWithOptions)
    {
        // Invariants enforced:
        // @invariant Options, Positionals and ProgramParameters can't be null
        // @invariant There are no duplicate Options or Positionals

        Option* nullOption = nullptr;

        EXPECT_NO_THROW(mediaParser->Add(mediaPrintOption.get()));
        EXPECT_THROW(mediaParser->Add(dupMediaPrintOption.get()), Parser::DuplicateOption);
        EXPECT_NO_THROW(mediaParser->Add(mediaEditOption.get()));
        EXPECT_NO_THROW(mediaParser->Add(mediaVerboseOption.get()));
        EXPECT_THROW(mediaParser->Add(nullOption), Parser::NullParameter);
    }

    TEST_F(ParserTests, AddMethodEnforcesInvariantsWithPosParams)
    {
        // Invariants enforced:
        // @invariant Options, Positionals and ProgramParameters can't be null
        // @invariant There are no duplicate Options or Positionals

        PosParam* nullPositional = nullptr;

        EXPECT_NO_THROW(copyParser->Add(copyDestinationPos.get()));
        EXPECT_THROW(copyParser->Add(dupCopyDestinationPos.get()), Parser::DuplicatePosParam);
        EXPECT_NO_THROW(searchParser->Add(searchPatternPos.get()));
        EXPECT_THROW(searchParser->Add(nullPositional), Parser::NullParameter);
    }

    TEST_F(ParserTests, ParsesUnixMediaArgumentsProperly)
    {
        ExpectMediaArgsParsed(Option::Style::Unix);
    }

    TEST_F(ParserTests, ParsesWindowsMediaArgumentsProperly)
    {
        ExpectMediaArgsParsed(Option::Style::Windows);
    }

    TEST_F(ParserTests, ParsesUnixCopyArgumentsProperly)
    {
        ExpectCopyArgsParsed(Option::Style::Unix);
    }

    TEST_F(ParserTests, ParsesWindowsCopyArgumentsProperly)
    {
        ExpectCopyArgsParsed(Option::Style::Windows);
    }

    TEST_F(ParserTests, ParsesUnixSearchArgumentsProperly)
    {
        ExpectSearchArgsParsed(Option::Style::Unix);
    }

    TEST_F(ParserTests, ParsesWindowsSearchArgumentsProperly)
    {
        ExpectSearchArgsParsed(Option::Style::Windows);
    }

    TEST_F(ParserTests, ParsesUnixNameLookupArgumentsProperly)
    {
        ExpectNameLookupArgsParsed(Option::Style::Unix);
    }

    TEST_F(ParserTests, ParsesWindowsNameLookupArgumentsProperly)
    {
        ExpectNameLookupArgsParsed(Option::Style::Windows);
    }

    TEST_F(ParserTests, ParserIndicatesWhenMandatoryOptionsAreNotSpecifed)
    {
        AddParamsToParsers();

        TestExpectedStates();

        EXPECT_EQ(invalidNameLookupParser->Parse(), Parser::Status::Success);

        expectedNameLookupProgramState.isSpecified = true;
        expectedNameLookupProgramState.value = nameLookupProgramName;
        expectedNameLookupVerboseState.isSpecified = true;

        TestExpectedStates();

        EXPECT_FALSE(invalidNameLookupParser->AllMandatoryParamsSpecified());
    }

    TEST_F(ParserTests, ParserIndicatesWhenMandatoryOptionsAreAllSpecifed)
    {
        AddParamsToParsers();

        TestExpectedStates();

        EXPECT_EQ(nameLookupParser->Parse(), Parser::Status::Success);

        expectedNameLookupProgramState.isSpecified = true;
        expectedNameLookupProgramState.value = nameLookupProgramName;
        expectedNameLookupVerboseState.isSpecified = true;
        expectedHostnameState.isSpecified = true;
        expectedHostnameState.value = hostname;

        TestExpectedStates();

        EXPECT_TRUE(nameLookupParser->AllMandatoryParamsSpecified());
    }

    TEST_F(ParserTests, GereratesUsageProperly)
    {
        AddParamsToParsers();

        std::string mediaUsage = GenerateExpectedUsageWithMessage(mediaInfo);
        std::string copyUsage = GenerateExpectedUsageWithMessage(copyInfo);
        std::string searchUsage = GenerateExpectedUsageWithMessage(searchInfo);
        std::string nameLookupUsage = GenerateExpectedUsageWithMessage(
            nameLookupInfo);

        EXPECT_EQ(mediaParser->GenerateUsage(), mediaUsage);
        EXPECT_EQ(copyParser->GenerateUsage(), copyUsage);
        EXPECT_EQ(searchParser->GenerateUsage(), searchUsage);
        EXPECT_EQ(nameLookupParser->GenerateUsage(), nameLookupUsage);
    }

    TEST_F(ParserTests, GeneratesHelpInfoProperly)
    {
        AddParamsToParsers();

        std::string mediaHelp = GenerateExpectedProgramHelp(mediaInfo);
        std::string copyHelp = GenerateExpectedProgramHelp(copyInfo);
        std::string searchHelp = GenerateExpectedProgramHelp(searchInfo);
        std::string nameLookupHelp = GenerateExpectedProgramHelp(
            nameLookupInfo);

        EXPECT_EQ(mediaParser->GenerateHelp(), mediaHelp);
        EXPECT_EQ(copyParser->GenerateHelp(), copyHelp);
        EXPECT_EQ(searchParser->GenerateHelp(), searchHelp);
        EXPECT_EQ(nameLookupParser->GenerateHelp(), nameLookupHelp);
    }

    TEST_F(ParserTests, BuiltInHelpOptionParsesShortNameProperly)
    {
        AddParamsToParsers();

        EXPECT_EQ(shortHelpNameLookupParser->Parse(), Parser::Status::Success);
        EXPECT_TRUE(shortHelpNameLookupParser->BuiltInHelpOptionIsSpecified());
    }

    TEST_F(ParserTests, BuiltInHelpOptionParsesLongNameProperly)
    {
        AddParamsToParsers();

        EXPECT_EQ(longHelpNameLookupParser->Parse(), Parser::Status::Success);
        EXPECT_TRUE(longHelpNameLookupParser->BuiltInHelpOptionIsSpecified());
    }

    TEST_F(ParserTests, DoesNotParseBuiltInHelpOptionWhenNotSpecified)
    {
        AddParamsToParsers();

        EXPECT_EQ(nameLookupParser->Parse(), Parser::Status::Success);
        EXPECT_FALSE(nameLookupParser->BuiltInHelpOptionIsSpecified());
    }
}
