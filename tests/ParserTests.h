// ParserTests.h - Declares the ParserTests fixture.
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

#ifndef CMD_LINE_PARSER_TESTS_H
#define CMD_LINE_PARSER_TESTS_H

#include <memory>
#include "gtest/gtest.h"
#include "ExampleArguments.h"
#include "TestDataStructures.h"
#include "TestAlgorithms.h"
#include "Parser.h"
#include "ValueOption.h"
#include "Option.h"

namespace CmdLine
{
    /// @brief Test fixture for the Parser tests.
    ///
    /// Shared data and functions for the Parser tests are implemented as part
    /// of the fixture, although functions shared across all fixtures are 
    /// implemented in TestAlgorithms.h. See ParserTests.cpp for the actual 
    /// tests.
    class ParserTests : public ::testing::Test
    {
    protected:
        /// @brief Constructs the Parser fixture.
        ///
        /// Initializes shared data common to all Parser tests. This includes
        /// arg vectors, multiple types of Param definitions, example
        /// program information, multiple types of expected ParamStates, 
        /// multiple types of Param instances, and multiple Parser
        /// instances.
        ParserTests();

        /// @brief Defines each shared ProgParam.
        ///
        /// Sets the properties on each of the ProgParam definitions used
        /// to construct the shared ProgParam instances to what they 
        /// should be.
        /// 
        /// @post All shared ProgParam definitions are defined.
        void DefineProgParams();

        /// @brief Defines each shared Option.
        ///
        /// Sets the properties on each of the Option definitions used
        /// to construct the shared Option instances to what they 
        /// should be.
        /// 
        /// @post All shared Option definitions are defined.
        void DefineOptions(Option::Style s);

        /// @brief Defines each shared OptionParam.
        ///
        /// Sets the properties on each of the OptionParam definitions used
        /// to construct the shared OptionParams instances to what they 
        /// should be.
        /// 
        /// @post All shared OptionParam definitions are defined.
        void DefineOptionParams();

        /// @brief Defines each shared PosParam.
        ///
        /// Sets the properties on each of the PosParam definitions used
        /// to construct the shared PosParam instances to what they 
        /// should be.
        /// 
        /// @post All shared PosParam definitions are defined.
        void DefinePosParams();

        /// @brief Initializes each ProgramInfo.
        ///
        /// @pre All Param definitions should be defined.
        /// @pre All Param instances should be initialized.
        /// @post All shared ProgramInfo instances are initialized.
        void InitializeProgramInfo();

        /// @brief Initializes each expected state.
        ///
        /// @pre All Param definitions should be defined.
        /// @post All expected states are initialized.
        void InitializeExpectedStates();

        /// @brief Initializes each shared ProgParam from definitions.
        ///
        /// @pre DefineProgParams() should be called before this method.
        /// @post All shared ProgParam instances are initialized.
        void InitializeProgParams();
        
        /// @brief Initializes each shared Option from definitions.
        ///
        /// @pre DefineOptions() should be called before this method.
        /// @post All shared Option instances are initialized.
        void InitializeOptions();

        /// @brief Initializes each shared OptionParam from definitions.
        ///
        /// @pre DefineOptionParams() should be called before this method.
        /// @post All shared OptionParams instances are initialized.
        void InitializeOptionParams();

        /// @brief Initializes each shared PosParam from definitions.
        ///
        /// @pre DefinePosParams() should be called before this method.
        /// @post All shared PosParam instances are initialized.
        void InitializePosParams();

        /// @brief Initializes each shared Parser.
        ///
        /// @pre All Param definitions should be defined.
        /// @pre All Param instances should be initialized.
        /// @pre All ProgramInfo instances should be initialized.
        /// @post All shared Parser instances are initialized.
        void InitializeParsers(Option::Style s);

        /// @brief Adds each OptionParam to a ValueOption.
        ///
        /// @pre All OptionParam instances should be initialized.
        /// @pre All Option instances should be initialized.
        /// @post All OptionParam instances are added to Option instances.
        void AddParamsToOptions();

        /// @brief Adds each Param instance to a Parser instance.
        ///
        /// @pre All Param instances should be initialized.
        /// @pre All Parser instances should be initialized.
        void AddParamsToParsers();

        /// @brief Tests all Parser/Parameter instances are in expected states.
        ///
        /// Each shared Parser and Param that's part of the fixture has an 
        /// expected state that each test can adjust. Tests can then call this
        /// function to ensure each instance is in the expected state. If the 
        /// test does not adjust any of the expected states, calling this 
        /// function will test that each shared Option is in its initial state.
        void TestExpectedStates();

        /// @brief Reconfigures for Windows style Options and arguments.
        ///
        /// By default, the Parsers are initialized with Unix arguments.
        /// Calling this method will reconfigure them in the Windows style
        /// by re-initializing them with Windows arguments if the Option::Style
        /// is set to Windows.
        /// 
        /// @param s Determines if the instances should be reconfigured.
        void ReconfigForWindowsIfNeeded(Option::Style s);

        /// @brief Sets the parsers for Windows style Options and arguments.
        ///
        /// By default, the Parsers are initialized to parse Unix arguments.
        /// Calling this method will set the Parsers to parse Windows 
        /// arguments instead if the Option::Style is set to Windows.
        ///
        /// @param s Determines if the parsers should be set for Windows.
        void SetParsersWithWindowsOptionsIfNeeded(Option::Style s);

        /// @brief Tests the media args with the mediaParser.
        ///
        /// Allows the media arguments, which represent arguments to a 
        /// hypothetical multimedia program, to be parsed and tested using 
        /// either the Windows or Unix style Option arguments.
        /// 
        /// @param s The style of Option used for testing.
        void ExpectMediaArgsParsed(Option::Style s);

        /// @brief Tests the copy args with the copyParser.
        ///
        /// Allows the copy arguments, which represent arguments to a 
        /// hypothetical copy program, to be parsed and tested using 
        /// either the Windows or Unix style Option arguments.
        /// 
        /// @param s The style of Option used for testing.
        void ExpectCopyArgsParsed(Option::Style s);

        /// @brief Tests the search args with the searchParser.
        ///
        /// Allows the search arguments, which represent arguments to a 
        /// hypothetical search program, to be parsed and tested using 
        /// either the Windows or Unix style Option arguments.
        /// 
        /// @param s The style of Option used for testing.
        void ExpectSearchArgsParsed(Option::Style s);

        /// @brief Tests the name lookup args with the nameLookkupParser.
        ///
        /// Allows the name lookup arguments, which represent arguments to a 
        /// hypothetical DNS lookup program, to be parsed and tested using 
        /// either the Windows or Unix style Option arguments.
        /// 
        /// @param s The style of Option used for testing.
        void ExpectNameLookupArgsParsed(Option::Style s);

        std::vector<std::string> unixMediaArgs
        {
            mediaProgramName,
            unixPrintOptionShortName,
            songOptionParamName,
            unixPrintOptionLongName,
            artistOptionParamName,
            unixEditOptionLongName,
            albumNameValuePairArg,
            unixVerboseOptionShortName,
            mediaFileName1,
            mediaFileName2
        };

        std::vector<std::string> unixCopyArgs
        {
            copyProgramName,
            unixVerboseOptionShortName,
            copySourceFileName1,
            copySourceFileName2,
            copyDestinationFileName
        };

        std::vector<std::string> unixSearchArgs
        {
            searchProgramName,
            unixIgnoreCaseOptionShortName,
            searchPatternText,
            searchFileName1,
            searchFileName2
        };

        std::vector<std::string> unixNameLookupArgs
        {
            nameLookupProgramName,
            unixVerboseOptionShortName,
            hostname
        };

        std::vector<std::string> unixNameLookupShortHelpArgs
        {
            nameLookupProgramName,
            unixHelpOptionShortName
        };

        std::vector<std::string> unixNameLookupLongHelpArgs
        {
            nameLookupProgramName,
            unixHelpOptionLongName
        };

        std::vector<std::string> windowsNameLookupShortHelpArgs
        {
            nameLookupProgramName,
            windowsHelpOptionShortName
        };

        std::vector<std::string> windowsNameLookupLongHelpArgs
        {
            nameLookupProgramName,
            windowsHelpOptionLongName
        };

        std::vector<std::string> unixInvalidNameLookupArgs
        {
            nameLookupProgramName,
            unixVerboseOptionShortName
        };

        std::vector<std::string> windowsInvalidNameLookupArgs
        {
            nameLookupProgramName,
            unixVerboseOptionShortName
        };

        std::vector<std::string> windowsMediaArgs
        {
            mediaProgramName,
            windowsPrintOptionShortName,
            songOptionParamName,
            windowsPrintOptionLongName,
            artistOptionParamName,
            windowsEditOptionLongName,
            albumNameValuePairArg,
            windowsVerboseOptionShortName,
            mediaFileName1,
            mediaFileName2
        };

        std::vector<std::string> windowsCopyArgs
        {
            copyProgramName,
            windowsVerboseOptionShortName,
            copySourceFileName1,
            copySourceFileName2,
            copyDestinationFileName
        };

        std::vector<std::string> windowsSearchArgs
        {
            searchProgramName,
            windowsIgnoreCaseOptionShortName,
            searchPatternText,
            searchFileName1,
            searchFileName2
        };

        std::vector<std::string> windowsNameLookupArgs
        {
            nameLookupProgramName,
            windowsVerboseOptionShortName,
            hostname
        };

        ProgParam::Definition mediaProgramDef;
        ProgParam::Definition searchProgramDef;
        ProgParam::Definition copyProgramDef;
        ProgParam::Definition nameLookupProgramDef;

        ValueOption::Definition mediaPrintDef;
        ValueOption::Definition mediaEditDef;

        Option::Definition verboseDef;
        Option::Definition searchIgnoreCaseDef;

        OptionParam::Definition songDef;
        OptionParam::Definition albumDef;
        OptionParam::Definition artistDef;

        MultiPosParam::Definition mediaFilesDef;
        MultiPosParam::Definition copySourceDef;
        MultiPosParam::Definition searchFilesDef;

        PosParam::Definition searchPatternDef;
        PosParam::Definition copyDestinationDef;
        PosParam::Definition hostnameDef;

        ProgParamState expectedMediaProgramState;
        ProgParamState expectedSearchProgramState;
        ProgParamState expectedCopyProgramState;
        ProgParamState expectedNameLookupProgramState;

        ValueOptionState expectedMediaPrintState;
        ValueOptionState expectedDupMediaPrintState;
        ValueOptionState expectedMediaEditState;

        OptionState expectedMediaVerboseState;
        OptionState expectedCopyVerboseState;
        OptionState expectedNameLookupVerboseState;
        OptionState expectedSearchIgnoreCaseState;

        OptionParamState expectedSongPrintState;
        OptionParamState expectedArtistPrintState;
        OptionParamState expectedAlbumPrintState;

        OptionParamState expectedSongEditState;
        OptionParamState expectedArtistEditState;
        OptionParamState expectedAlbumEditState;

        MultiPosParamState expectedMediaFilesState;
        MultiPosParamState expectedCopySourceState;
        MultiPosParamState expectedSearchFilesState;

        PosParamState expectedSearchPatternState;
        PosParamState expectedCopyDestinationState;
        PosParamState expectedDupCopyDestinationState;
        PosParamState expectedHostnameState;

        ProgramInfo mediaInfo;
        ProgramInfo copyInfo;
        ProgramInfo searchInfo;
        ProgramInfo nameLookupInfo;

        std::unique_ptr<ProgParam> mediaProgParam;
        std::unique_ptr<ProgParam> searchProgParam;
        std::unique_ptr<ProgParam> copyProgParam;
        std::unique_ptr<ProgParam> nameLookupProgParam;

        std::unique_ptr<ValueOption> mediaPrintOption;
        std::unique_ptr<ValueOption> dupMediaPrintOption;
        std::unique_ptr<ValueOption> mediaEditOption;
        std::unique_ptr<Option> mediaVerboseOption;
        std::unique_ptr<Option> copyVerboseOption;
        std::unique_ptr<Option> nameLookupVerboseOption;
        std::unique_ptr<Option> searchIgnoreCaseOption;

        std::unique_ptr<OptionParam> songPrintOptionParam;
        std::unique_ptr<OptionParam> artistPrintOptionParam;
        std::unique_ptr<OptionParam> albumPrintOptionParam;

        std::unique_ptr<OptionParam> songEditOptionParam;
        std::unique_ptr<OptionParam> artistEditOptionParam;
        std::unique_ptr<OptionParam> albumEditOptionParam;

        std::unique_ptr<MultiPosParam> mediaFilesMultiPos;
        std::unique_ptr<MultiPosParam> copySourcePos;
        std::unique_ptr<MultiPosParam> searchFilesMultiPos;

        std::unique_ptr<PosParam> searchPatternPos;
        std::unique_ptr<PosParam> copyDestinationPos;
        std::unique_ptr<PosParam> dupCopyDestinationPos;
        std::unique_ptr<PosParam> hostnamePos;
        
        std::unique_ptr<Parser> mediaParser;
        std::unique_ptr<Parser> copyParser;
        std::unique_ptr<Parser> searchParser;
        std::unique_ptr<Parser> nameLookupParser;
        std::unique_ptr<Parser> invalidNameLookupParser;
        std::unique_ptr<Parser> shortHelpNameLookupParser;
        std::unique_ptr<Parser> longHelpNameLookupParser;
    };
}

#endif
