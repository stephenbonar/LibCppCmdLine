// Constants.h - Declares the global constants for the library.
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

#ifndef CMD_LINE_CONSTANTS_H
#define CMD_LINE_CONSTANTS_H

namespace CmdLine
{
    /// @brief The number of spaces to lefthand indent Param names in help.
    extern const int helpIndentWidth;

    /// @brief The size the name field should be in help for alignment.
    extern const int helpNameFieldWidth;

    /// @brief Indicates the minimum size a valid Param name can be.
    extern const int minNameSize;

    /// @brief Indicates the maximum size a valid Param name can be.
    extern const int maxNameSize;

    /// @brief The open bracket used to show a Param is optional in help.
    extern const char optionalOpenBracket;

    /// @brief The close bracket used to show a Param is optional in help.
    extern const char optionalCloseBracket;

    /// @brief The open bracket used to show a Param is mandatory in help.
    extern const char mandatoryOpenBracket;

    /// @brief The close bracket used to show a Param is mandatory in help.
    extern const char mandatoryCloseBracket;

    /// @brief A string that indicates a Param is a MultiPosParam in help. 
    extern const char* multiPosParamIndicator;

    /// @brief The short option prefix used with Option::Style::Unix.
    extern const char* unixOptionShortPrefix;

    /// @brief The long option prefix used with Option::Style::Unix.
    extern const char* unixOptionLongPrefix;

    /// @brief The short option prefix used with Option::Style::Unix.
    extern const char* windowsOptionShortPrefix;

    /// @brief The long option prefix used with Option::Style::Windows.
    extern const char* windowsOptionLongPrefix;

    /// @brief The short option name for the built-in help option.
    extern const char helpOptionShortName;

    /// @brief The long option name for the built-in help option.
    extern const char* helpOptionLongName;

    /// @brief The description for the built-in help option.
    extern const char* helpOptionDescription;

    /// @brief The header indicating the Usage section of help.
    extern const char* usageHeader;

    /// @brief The header indicating the Description section of help.
    extern const char* descriptionHeader;

    /// @brief The header indicating the Positional Parameters section of help.
    extern const char* posParamHeader;

    /// @brief The header indicating the Options section of help.
    extern const char* optionsHeader;

    /// @brief The label that indicates where Options go in the usage info.
    extern const char* optionsLabel;

    /// @brief The first part of the message indicating how to get help.
    extern const char* helpMessagePrefix;

    /// @brief The second part of the message indicating how to get help.
    extern const char* helpMessagePostfix;

    /// @brief An error message for invalid Option short names.
    extern const char* optionShortNameError;

    /// @brief An error message for invalid Option long names.
    extern const char* optionLongNameError;

    /// @brief An error message for empty Option names.
    extern const char* optionEmptyNameError;

    /// @brief An error message for empty command line arguments.
    extern const char* emptyArgsError;

    /// @brief An error message for invalid Parameter names.
    extern const char* nameError;

    /// @brief An error message for adding a null Option.
    extern const char* nullOptionError;

    /// @brief An error message for adding a null OptionParam.
    extern const char* nullOptionParamError;

    /// @brief An error message for adding a null PosParam.
    extern const char* nullPosParamError;

    /// @brief An error message for adding a null ProgParam.
    extern const char* nullProgParamError;
    
    /// @brief An error message for adding a duplicate Option.
    extern const char* duplicateOptionError;

    /// @brief An error message for adding a duplicate PosParam.
    extern const char* duplicatePosParamError;

    /// @brief An error message for adding a duplicate 
    /// CommandLine::OptionParameter.
    extern const char* duplicateOptionParamError;
}

#endif
