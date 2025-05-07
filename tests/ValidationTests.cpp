// ValidationTests.cpp - Defines Validation function tests.
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

#include "ValidationTests.h"

namespace CmdLine
{
    TEST_F(ValidationTests, ProperlyValidatesNames)
    {
        // Should properly validate these invariants:
        // 1. Acceptable characters for names are alpha numerics and - and _
        // 2. Names must not start with the option prefix
        // 3. Names must not be empty

        TestNameBundle test = GenerateTestNames(NameGenerationMode::PlainName);

        for (auto name : test.validNames)
            ASSERT_EQ(IsValidNonOptionName(name), true);

        for (auto name : test.invalidNames)
            ASSERT_EQ(IsValidNonOptionName(name), false);
    }
}
