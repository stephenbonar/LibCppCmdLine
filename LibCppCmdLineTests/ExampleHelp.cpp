// ExampleHelp.cpp - Defines example help strings as global constants.
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

#include "ExampleHelp.h"

namespace CmdLine
{
    const char* mediaProgramParamHelpLine
    { 
        "  prints and edits tags in media files" 
    };
    const char* searchProgramParamHelpLine
    { 
        "  searches files for lines that contain a search pattern" 
    };
    const char* copyProgramParamHelpLine
    { 
        "  copies one or more files to the specified destination" 
    };

    const char* searchPatternPosHelpLine
    { 
        "  pattern                     the file search pattern" 
    };
    const char* searchFilesMultiPosHelpLine
    { 
        "  filenames                   the files to search" 
    };
    const char* copySourceMultiPosHelpLine
    { 
        "  source                      the files to copy" 
    };
    const char* copyDestPosHelpLine
    { 
        "  destination                 the destination file path" 
    };

    const char* unixPrintOptionHelpLine
    { 
        "  -p, --print                 prints the specified fields" 
    };
    const char* unixEditOptionHelpLine
    { 
        "  -e, --edit                  edits the specified fields" 
    };
    const char* unixVerboseOptionHelpLine
    { 
        "  -v, --verbose               prints verbose info" 
    };
    const char* unixIgnoreCaseHelpLine
    { 
        "  -i, --ignore-case           ignores case when searching" 
    };
    const char* unixHelpOptionHelpLine
    { 
        "  -h, --help                  prints detailed help info" 
    };

    const char* unixShortOptionHelpLine
    { 
        "  -s                          short option only example" 
    };
    const char* unixLongOptionHelpLine
    { 
        "  --long                      long option only example" 
    };

    const char* windowsShortOptionHelpLine
    { 
        "  /s                          short option only example" 
    };
    const char* windowsLongOptionHelpLine
    { 
        "  /long                       long option only example" 
    };
    
    const char* windowsPrintOptionHelpLine
    { 
        "  /p, /print                  prints the specified fields" 
    };
    const char* windowsEditOptionHelpLine
    { 
        "  /e, /edit                   edits the specified fields"
    };
    const char* windowsVerboseOptionHelpLine
    {
        "  /v, /verbose                prints verbose info"
    };
    const char* windowsIgnoreCaseHelpLine
    {
        "  /i, /ignore-case            ignores case when searching"
    };
    const char* windowsHelpOptionHelpLine
    {
        "  /h, /help                   prints detailed help info"
    };

    const char* songOptionParamHelpLine
    { 
        "  song                        the title of the song" 
    };
    const char* artistOptionParamHelpLine
    { 
        "  artist                      the song artist"
    };
    const char* albumOptionParamHelpLine
    {
        "  album                       the album of the song"
    };
}