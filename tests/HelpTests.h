// HelpTests.h - Declares the HelpTests test fixture.
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

#ifndef CMD_LINE_HELP_TESTS_H
#define CMD_LINE_HELP_TESTS_H

#include "gtest/gtest.h"
#include "ExampleArguments.h"
#include "ExampleHelp.h"
#include "Help.h"

namespace CmdLine
{
    /// @brief A test fixture for all functions that generate help.
    ///
    /// This empty fixutre is purely implemented for the sake of consistency
    /// and maintenance. Should this fixture be needed, its scaffolding
    /// is already in place. See HelpTests.cpp for the tests.
    class HelpTests : public ::testing::Test
    {
    };
}

#endif
