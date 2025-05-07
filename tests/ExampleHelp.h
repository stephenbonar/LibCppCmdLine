// ExampleHelp.h - Declares example help strings as global constants.
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

#ifndef CMD_LINE_EXAMPLE_HELP_H
#define CMD_LINE_EXAMPLE_HELP_H

namespace CmdLine
{
    /// @brief Help text that describes a hypothetical multimedia program.
    extern const char* mediaProgramParamHelpLine;

    /// @brief Help text that describes a hypothetical search program.
    extern const char* searchProgramParamHelpLine;

    /// @brief Help text that describes a hypothetical copy program.
    extern const char* copyProgramParamHelpLine;

    /// @brief Help that describes a search pattern positional.
    extern const char* searchPatternPosHelpLine;

    /// @brief Help text that describes a search file multipositional.
    extern const char* searchFilesMultiPosHelpLine;

    /// @brief Help text that describes a copy source file multipositional.
    extern const char* copySourceMultiPosHelpLine;

    /// @brief Help text that describes a copy desitination file positional.
    extern const char* copyDestPosHelpLine;

    /// @brief Help text that describes a Unix style print option.
    extern const char* unixPrintOptionHelpLine;

    /// @brief Help text that describes a Unix style edit option.
    extern const char* unixEditOptionHelpLine;

    /// @brief Help text that describes a Unix style verbose option.
    extern const char* unixVerboseOptionHelpLine; 

    /// @brief Help text that describes a Unix style ignorecase option.
    extern const char* unixIgnoreCaseHelpLine;

    /// @brief Help text that describes a Unix style generic short only option.
    extern const char* unixShortOptionHelpLine;

    /// @brief Help text that describes a Unix style generic long only option.
    extern const char* unixLongOptionHelpLine;

    /// @brief Help text that describes a Windows style short only option.
    extern const char* windowsShortOptionHelpLine;

    /// @brief Help text that describes a Windows style long only option.
    extern const char* windowsLongOptionHelpLine;

    /// @brief Help text that describes a Windows style print option.
    extern const char* windowsPrintOptionHelpLine;

    /// @brief Help text that describes a Windows style edit option.
    extern const char* windowsEditOptionHelpLine;

    /// @brief Help text that describes a Windows style verbose option.
    extern const char* windowsVerboseOptionHelpLine;

    /// @brief Help text that describes a Windows style ignorecase option.
    extern const char* windowsIgnoreCaseHelpLine;

    /// @brief Help text that describes a song option parameter.
    extern const char* songOptionParamHelpLine;

    /// @brief Help text that describes an artist option parameter.
    extern const char* artistOptionParamHelpLine;

    /// @brief Help text that describes an album option parameter.
    extern const char* albumOptionParamHelpLine;
}

#endif
