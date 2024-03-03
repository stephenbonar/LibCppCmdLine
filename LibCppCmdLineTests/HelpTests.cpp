// HelpTests.cpp - Defines tests for the Help functions.
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

#include "HelpTests.h"

namespace CmdLine
{
    TEST_F(HelpTests, ProperlyGeneratesHelpLine)
    {
        std::string label{ songOptionParamName };
        std::string description{ songOptionParamDescription };
        std::string expectedHelpLine{ songOptionParamHelpLine };
        EXPECT_EQ(GenerateHelpLine(label, description), expectedHelpLine);
    }
}
