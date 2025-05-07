// ExampleArguments.h - Declares example argument strings as global constants.
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

#ifndef CMD_LINE_EXAMPLE_ARGUMENTS_H
#define CMD_LINE_EXAMPLE_ARGUMENTS_H

namespace CmdLine
{
    /// @brief A program name for a hypothetical multimedia program.
    extern const char* mediaProgramName;

    /// @brief A program name for a hypothetical search program.
    extern const char* searchProgramName;

    /// @brief A program name for a hypothetical copy program.
    extern const char* copyProgramName;

    /// @brief A program name for a hypothetical DNS lookup program.
    extern const char* nameLookupProgramName;

    /// @brief A description for a hypothetical multimedia program.
    extern const char* mediaProgramDescription;

    /// @brief A description for a hypothetical search program.
    extern const char* searchProgramDescription;

    /// @brief A description for a hypothetical copy program.
    extern const char* copyProgramDescription;

    /// @brief A description for a hypothetical DNS lookup program.
    extern const char* nameLookupProgramDescription;

    /// @brief A short name for a print option in a hypothetical program.
    extern const char printOptionShortName;

    /// @brief A short name for an edit option in a hypothetical program.
    extern const char editOptionShortName;

    /// @brief A short name for a verbose option in a hypothetical program.
    extern const char verboseOptionShortName;

    /// @brief A short name for an ignorecase option in a hypothetical program.
    extern const char ignoreCaseOptionShortName;

    /// @brief A short name for the built-in help option.
    extern const char helpShortOptionName;

    /// @brief A short name for a generic option.
    extern const char shortOptionName;

    /// @brief A long name for a print option in a hypothetical program.
    extern const char* printOptionLongName;

    /// @brief A long name for an edit option in a hypothetical program.
    extern const char* editOptionLongName;

    /// @brief A long name for a verbose option in a hypothetical program.
    extern const char* verboseOptionLongName;

    /// @brief A long name for an ignorecase option in a hypothetical program.
    extern const char* ignoreCaseOptionLongName;

    /// @brief A long name for the built-in help option.
    extern const char* helpOptionLongName;

    /// @brief A long name for a generic option.
    extern const char* longOptionName;

    /// @brief A description for a print option in a hypothetical program.
    extern const char* printOptionDescription;

    /// @brief A description for an edit option in a hypothetical program.
    extern const char* editOptionDescription;

    /// @brief A description for a verbose option in a hypothetical program.
    extern const char* verboseOptionDescription;

    /// @brief A description for an ignorecase option in a hypothetical program.
    extern const char* ignoreCaseDescription;

    /// @brief A description for a generic example short option.
    extern const char* shortOptionDescription;

    /// @brief A description for a generic example long option.
    extern const char* longOptionDescription;

    /// @brief A Unix prefixed short name argument for the print option.
    extern const char* unixPrintOptionShortName;

    /// @brief A Unix prefixed long name argument for the print option.
    extern const char* unixPrintOptionLongName;

    /// @brief A Unix prefixed short name argument for the edit option.
    extern const char* unixEditOptionShortName;

    /// @brief A Unix prefixed long name argument for the edit option.
    extern const char* unixEditOptionLongName;

    /// @brief A Unix prefixed short name argument for the verbose option.
    extern const char* unixVerboseOptionShortName;

    /// @brief A Unix prefixed long name argument for the verbose option.
    extern const char* unixVerboseOptionLongName;

    /// @brief A Unix prefixed short name argument for the ignorecase option.
    extern const char* unixIgnoreCaseOptionShortName;

    /// @brief A Unix prefixed long name argument for the ignorecase option.
    extern const char* unixIgnoreCaseOptionLongName;

    /// @brief A Unix prefixed short name argument for the help option.
    extern const char* unixHelpOptionShortName;

    /// @brief A Unix prefixed long name argument for the help option.
    extern const char* unixHelpOptionLongName;

    /// @brief A Unix prefixed short name argument for a generic option.
    extern const char* unixShortOptionName;

    /// @brief A Unix prefixed short name argument for a ageneric option.
    extern const char* unixLongOptionName;

    /// @brief A Windows prefixed short name argument for the print option.
    extern const char* windowsPrintOptionShortName;

    /// @brief A Windows prefixed long name argument for the print option.
    extern const char* windowsPrintOptionLongName;

    /// @brief A Windows prefixed short name argument for the edit option.
    extern const char* windowsEditOptionShortName;

    /// @brief A Windows prefixed long name argument for the edit option.
    extern const char* windowsEditOptionLongName;

    /// @brief A Windows prefixed short name argument for the verbose option.
    extern const char* windowsVerboseOptionShortName;

    /// @brief A Windows prefixed long name argument for the verbose option.
    extern const char* windowsVerboseOptionLongName;

    /// @brief A Windows prefixed short name argument for the ignorecase option.
    extern const char* windowsIgnoreCaseOptionShortName;

    /// @brief A Windows prefixed long name argument for the ignore option.
    extern const char* windowsIgnoreCaseOptionLongName;

    /// @brief A Windows prefixed short name argument for the help option.
    extern const char* windowsHelpOptionShortName;

    /// @brief A Windows prefixed long name argument for the help option.
    extern const char* windowsHelpOptionLongName;

    /// @brief A Windows prefixed short name argument for a generic option.
    extern const char* windowsShortOptionName;

    /// @brief A Windows prefixed long name argument for a generic option.
    extern const char* windowsLongOptionName;

    /// @brief The name of an option parameter representing a song.
    extern const char* songOptionParamName;

    /// @brief The name of an option parameter representing an artist.
    extern const char* artistOptionParamName;

    /// @brief The name of an option parameter representing an album.
    extern const char* albumOptionParamName;

    /// @brief The description of an option parameter representing a song.
    extern const char* songOptionParamDescription;

    /// @brief The description of an option parameter representing an artist.
    extern const char* artistOptionParamDescription;

    /// @brief The description of an option parameter representing an album.
    extern const char* albumOptionParamDescription;

    /// @brief An example value for the artist option parameter.
    extern const char* artistValue;

    /// @brief An example argument representing an artist name value pair.
    extern const char* artistNameValuePairArg;

    /// @brief An example value for the artist option parameter.
    extern const char* albumValue;

    /// @brief An example argument representing an artist name value pair.
    extern const char* albumNameValuePairArg;

    /// @brief A name value pair argument that is missing a name.
    extern const char* missingNameValuePairArg;

    /// @brief The name of a multipositional that accepts media file names.
    extern const char* mediaFilesMultiPosName;

    /// @brief The name of a multipositional that accepts source file paths.
    extern const char* copySourceMultiPosName;

    /// @brief The name of a multipositional that accepts file names to search.
    extern const char* searchFilesMultiPosName;

    /// @brief The name of a positional that accepts a destination path.
    extern const char* copyDestinationPosName;

    /// @brief The name of a positional that accepts a search pattern.
    extern const char* searchPatternPosName;

    /// @brief The name of a positional that accepts a hostname.
    extern const char* hostnamePosName;

    /// @brief The description of a positional that accepts a search pattern.
    extern const char* searchPatternPosDescription;

    /// @brief The description of a positional that accepts a destination path.
    extern const char* copyDestinationPosDescription;

    /// @brief The description of a positional that accepts a hostname.
    extern const char* hostnamePosDescription;

    /// @brief The description of a multipositional that accepts media file names.
    extern const char* mediaFilesMultiPosDescription;

    /// @brief The description of a positional that accepts a search pattern.
    extern const char* searchFilesMultiPosDescription;

    /// @brief The description of a positional that accepts source file paths.
    extern const char* copySourceMultiPosDescription;
    
    /// @brief An example media file name for a hypothetical multimedia program.
    extern const char* mediaFileName1;

    /// @brief An example media file name for a hypothetical multimedia program.
    extern const char* mediaFileName2;

    /// @brief An example file source path for a hypothetical copy program.
    extern const char* copySourceFileName1;

    /// @brief An example file source path for a hypothetical copy program.
    extern const char* copySourceFileName2;

    /// @brief An example destination path for a hypothetical copy program.
    extern const char* copyDestinationFileName;

    /// @brief An example file name for a hypothetical search program.
    extern const char* searchFileName1;

    /// @brief An example file name for a hypothetical search program.
    extern const char* searchFileName2;

    /// @brief An example search pattern for a hypothetical search program.
    extern const char* searchPatternText;

    /// @brief An example hostname for a hypothetical DNS lookup program.
    extern const char* hostname;

    /// @brief An example value that does not meet criteria of param names.
    extern const char* nonNameValue1;

    /// @brief An example value that does not meet criteria of param names.
    extern const char* nonNameValue2;

    /// @brief An example full file path.
    extern const char* fullFilePath;
}

#endif
