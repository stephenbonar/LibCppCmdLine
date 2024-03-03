// Constants.cpp - Defines global constants for the library.
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

#include "Constants.h"

namespace CmdLine
{
    const int helpIndentWidth{ 2 };
    const int helpNameFieldWidth{ 28 };
    const int minNameSize{ 1 };
    const int maxNameSize{ 20 };

    const char optionalOpenBracket{ '[' };
    const char optionalCloseBracket{ ']' };
    const char mandatoryOpenBracket{ '<' };
    const char mandatoryCloseBracket{ '>' };

    const char* multiPosParamIndicator{ "..." };

    const char* unixOptionShortPrefix{ "-" };
    const char* unixOptionLongPrefix{ "--" };
    const char* windowsOptionShortPrefix{ "/" };
    const char* windowsOptionLongPrefix{ "/" };

    const char helpOptionShortName{ 'h' };
    const char* helpOptionLongName{ "help" };
    const char* helpOptionDescription{ "prints detailed help info" };

    const char* usageHeader{ "Usage:" };
    const char* descriptionHeader{ "Description:" };
    const char* posParamHeader{ "Positional Parameters:" };
    const char* optionsHeader{ "Options:" };

    const char* optionsLabel{ "options" };

    const char* helpMessagePrefix{ "Try '" };
    const char* helpMessagePostfix{ " --help' for more info" };

    const char* optionShortNameError
    { 
        "must be an alphanumeric character or ?" 
    };
    const char* optionLongNameError
    { 
        "20 chars max: alphanumeric, _ or -. No option prefix."
    };
    const char* optionEmptyNameError
    { 
        "at least one option name (short or long) must not be empty."
    };
    const char* emptyArgsError{ "Command line arguments can't be empty" };
    const char* nameError
    { 
        "20 chars max > 0 min: alphanumeric, _ or -. No option prefix." 
    };
    const char* nullOptionError{ "cannot add a null Option to the Parser" };
    const char* nullOptionParamError
    { 
        "cannot add null OptionParam to Option" 
    };
    const char* nullPosParamError
    { 
        "cannot add a null PosParam to the Parser"
    };
    const char* nullProgParamError
    { 
        "cannot add null ProgParam to the Parser" 
    };
    const char* duplicateOptionError
    { 
        "cannot add a duplicate Option to the Parser" 
    };
    const char* duplicateOptionParamError
    { 
        "cannot add a duplicate OptionParam to Option" 
    };
    const char* duplicatePosParamError
    { 
        "cannot add a duplicate PosParam to the Parser" 
    };
}
