// NameValuePairTests.h - Declares the NameValuePairTests fixture.
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

#ifndef CMD_LINE_NAME_VALUE_PAIR_TESTS_H
#define CMD_LINE_NAME_VALUE_PAIR_TESTS_H

#include <memory>
#include "gtest/gtest.h"
#include "ExampleArguments.h"
#include "TestDataStructures.h"
#include "TestAlgorithms.h"
#include "NameValuePair.h"

namespace CmdLine
{  
    /// @brief Test fixture for the NameValuePair tests.
    ///
    /// Shared data and functions for the NameValuePair tests are 
    /// implemented as part of the fixture, although functions shared across
    /// all fixtures are implemented in TestAlgorithms.h. See 
    /// NameValuePairTests.cpp for the actual tests.
    class NameValuePairTests : public ::testing::Test
    {
    protected:
        /// @brief Constructs the NameValuePairTests fixture.
        ///
        /// Initializes shared data common to all NameValuePair tests. This
        /// includes a pair that has a value (a true pair) and a pair that is
        /// just a name without a value.
        NameValuePairTests();

        std::unique_ptr<NameValuePair> truePair;
        std::unique_ptr<NameValuePair> pairWithoutValue;
    };
}


#endif
