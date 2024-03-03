// ExampleArguments.cpp - Defines example argument strings as global constants.
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

#include "ExampleArguments.h"

namespace CmdLine
{
    const char* mediaProgramName{ "mediaedit" };
    const char* searchProgramName{ "filesearch" };
    const char* copyProgramName{ "copy" };
    const char* nameLookupProgramName{ "namelookup" };

    const char* mediaProgramDescription
    { 
        "prints and edits tags in media files"
    };
    const char* searchProgramDescription
    { 
        "searches files for lines that contain a search pattern"
    };
    const char* copyProgramDescription
    { 
        "copies one or more files to the specified destination"
    };
    const char* nameLookupProgramDescription
    { 
        "looks up the IP address of the specified hostname"
    };

    const char printOptionShortName{ 'p' };
    const char editOptionShortName{ 'e' };
    const char verboseOptionShortName{ 'v' };
    const char ignoreCaseOptionShortName{ 'i' };
    const char helpShortOptionName{ 'h' };
    const char shortOptionName{ 's' };

    const char* printOptionLongName{ "print" };
    const char* editOptionLongName{ "edit" };
    const char* verboseOptionLongName{ "verbose" };
    const char* ignoreCaseOptionLongName{ "ignore-case" };
    const char* helpLongOptionName{ "help" };
    const char* longOptionName{ "long" };

    const char* printOptionDescription{ "prints the specified fields" };
    const char* editOptionDescription{ "edits the specified fields" };
    const char* verboseOptionDescription{ "prints verbose info" };
    const char* ignoreCaseDescription{ "ignores case when searching" };
    const char* shortOptionDescription{ "short option only example" };
    const char* longOptionDescription{ "long option only example" };

    const char* unixPrintOptionShortName{ "-p" };
    const char* unixPrintOptionLongName{ "--print" };
    const char* unixEditOptionShortName{ "-e" };
    const char* unixEditOptionLongName{ "--edit" };
    const char* unixVerboseOptionShortName{ "-v" };
    const char* unixVerboseOptionLongName{ "--verbose" };
    const char* unixIgnoreCaseOptionShortName{ "-i" };
    const char* unixIgnoreCaseOptionLongName{ "--ignore-case" };
    const char* unixHelpOptionShortName{ "-h" };
    const char* unixHelpOptionLongName{ "--help" };
    const char* unixShortOptionName{ "-s" };
    const char* unixLongOptionName{ "--long" };

    const char* windowsPrintOptionShortName{ "/p" };
    const char* windowsPrintOptionLongName{ "/print" };
    const char* windowsEditOptionShortName{ "/e" };
    const char* windowsEditOptionLongName{ "/edit" };
    const char* windowsVerboseOptionShortName{ "/v" };
    const char* windowsVerboseOptionLongName{ "/verbose" };
    const char* windowsIgnoreCaseOptionShortName{ "/i" };
    const char* windowsIgnoreCaseOptionLongName{ "/ignore-case" };
    const char* windowsHelpOptionShortName{ "/h" };
    const char* windowsHelpOptionLongName{ "/help" };
    const char* windowsShortOptionName{ "/s" };
    const char* windowsLongOptionName{ "/long" };

    const char* songOptionParamName{ "song" };
    const char* artistOptionParamName{ "artist" };
    const char* albumOptionParamName{ "album" };

    const char* songOptionParamDescription{ "the title of the song" };
    const char* artistOptionParamDescription{ "the song artist" };
    const char* albumOptionParamDescription{ "the album of the song" };

    const char* artistValue{ "The Testers" };
    const char* artistNameValuePairArg{ "artist=The Testers" };

    const char* albumValue{ "Testing the Testers" };
    const char* albumNameValuePairArg{ "album=Testing the Testers" };

    const char* missingNameValuePairArg = "=value";

    const char* mediaFilesMultiPosName{ "filenames" };
    const char* copySourceMultiPosName{ "source" };
    const char* searchFilesMultiPosName{ "filenames" };

    const char* copyDestinationPosName{ "destination" };
    const char* searchPatternPosName{ "pattern" };
    const char* hostnamePosName{ "hostname" };

    const char* searchPatternPosDescription{ "the file search pattern" };
    const char* copyDestinationPosDescription{ "the destination file path" };
    const char* hostnamePosDescription{ "the hostname to look up" };

    const char* mediaFilesMultiPosDescription{ "the media files to process" };
    const char* searchFilesMultiPosDescription{ "the files to search" }; 
    const char* copySourceMultiPosDescription{ "the files to copy" };

    const char* mediaFileName1{ "Test1.mp3" };
    const char* mediaFileName2{ "Test2.mp3" };

    const char* copySourceFileName1{ "Source1.txt" };
    const char* copySourceFileName2{ "Source2.txt" };
    const char* copyDestinationFileName{ "Destination.txt" };

    const char* searchFileName1{ "FileToSearch1.txt" };
    const char* searchFileName2{ "FileToSearch2.txt" };

    const char* searchPatternText{ "test_pattern" };

    const char* hostname{ "test.example.com" };

    const char* nonNameValue1{ "Is,valid,value,but,not,valid,name" };
    const char* nonNameValue2{ "ThisValueIsWayTooLongToBeValidName" };

    const char* fullFilePath{ "/tmp/test/file" };
}