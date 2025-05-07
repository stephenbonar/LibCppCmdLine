// CmdLine.h - The main LibCppCmdLine library header.
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

/// @mainpage LibCppCmdLine: C++ Command Line Parsing Library
/// 
/// @section releaseSection Current Release
/// 
/// @version 1.0 Beta 15
/// 
/// @section introSection Introduction
/// 
/// LibCppCmdLine is a modern, lightweight, and cross-platform C++ command line 
/// parsing library. It provides a series of classes for parsing command line
/// arguments passed to a program via the main function and populating command
/// line parameters with values as a result of parsing. A program that uses 
/// this library will:
/// 
/// 1. Define and create command line parameters.
/// 2. Create a new command line parser. 
/// 3. Add the command line parameters to the parser.
/// 4. Parse the command line arguments with the parser.
/// 5. Examine the parameters that were populated by the parser.
/// 
/// The library uses the C++ Standard Template Library (STL) and thus has no
/// major external dependencies (see note below). It is lightweight enough
/// that it is designed to be added directly to a program's code base. However,
/// the program can still be precompiled and statically or dynamically linked
/// if desired. This library also uses exceptions, but only for enforcing class
/// invariants to prevent programming errors; the library will only
/// generate exceptions if the programmer defines parameters wrong or
/// adds duplicate parameters, thus no try / catch blocks are necessary for
/// final code.
///
/// @note The tests for this library do have an external dependency: 
/// GoogleTest. However, the tests are only needed for testing changes to the 
/// library code itself and are not needed for a program that will simply 
/// include the library as-is.
/// 
/// @section featuresSection Features
/// 
/// * Lightweight.
/// * Cross-platform.
/// * No external dependencies.
/// * Designed to be added and compiled straight into your program's code base.
/// * Supports two types of options and two types of positional parameters.
/// * Options can have either the Windows or Unix style prefix.
/// * Standard options act like simple switches.
/// * Value options suport multiple values and their own option parameters.
/// * Positional parameters come in single or multi-value varieties.
/// * The parser can generate usage and help info based on the parameters.
/// 
/// @section limitationsSection Limitations
/// 
/// * Only supports ASCII command line arguments.
/// * Not designed for programs with a highly complex command line use case.
/// 
/// @section Available Namespaces
/// 
/// Everything in this library is contained within the CmdLine namespace.
/// 
/// @section classesSection Key Classes
/// 
/// The following classes are necessary to parse command line arguments.
/// 
/// Class (* base)       | Purpose                                                    |
/// ---------------------|------------------------------------------------------------|
/// CmdLine::Parser      | Parses command line arguments                              |
/// CmdLine::Param *     | A variable that stores data from the command line          |
/// CmdLine::ArgParam *  | A CmdLine::Param populated by CommandLine arguments        |
/// CmdLine::ProgParam   | A CmdLine::ArgParam populated by the program name argument |
/// CmdLine::Option      | A CmdLine::ArgParam that represents an option              |
/// CmdLine::ValueOption | A CmdLine::Option populated with values                    |
/// CmdLine::OptionParam | Provides parameters for CmdLine::ValueOption values        |
/// CmdLine::PosParam    | A Positional CmdLine::ArgParam                             |
/// CmdLine::MultiPos    | A multi-value positional CmdLine::ArgParam                 |
/// 
/// @section structsSection Key Structs
/// 
/// The following structs are necessary to define command line parameters.
/// 
/// Struct                             | Purpose                                    |
/// -----------------------------------|--------------------------------------------|
/// CmdLine::ProgParam::Definition     | Used to construct a CmdLine::ProgParam     |
/// CmdLine::Option::Definition        | Used to construct a CmdLine::Option        |
/// CmdLine::ValueOption::Definition   | Used to construct a CmdLine::ValueOption   |
/// CmdLine::OptionParam::Definition   | Used to construct a CmdLine::OptionParam   |
/// CmdLine::PosParam::Definition      | Used to construct a CmdLine::PosParam      |
/// CmdLine::MultiPosParam::Definition | Used to construct a CmdLine::MultiPosParam |
/// 
/// @todo Add example section
/// 
/// @todo Add information about adding to your codebase

/// @namespace CmdLine
/// @brief This namespace represents everthing related to command line parsing.
/// 
/// The CmdLine namespace encapsulates all objects and functions related
/// to command line argument parsing. Command line arguments are the string
/// arguments passed to the main() function in the program from the OS,
/// typically from a command line interfacte (CLI).

#ifndef CMD_LINE_H
#define CMD_LINE_H

#include "MultiPosParam.h"
#include "Option.h"
#include "OptionParam.h"
#include "Parser.h"
#include "PosParam.h"
#include "ProgParam.h"
#include "ValueOption.h"

#endif
