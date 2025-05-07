// NameValuePairTests.h - Defines tests for the NameValuePair class.
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

#include "NameValuePairTests.h"

namespace CmdLine
{
    NameValuePairTests::NameValuePairTests()
    {
        std::string a = albumNameValuePairArg;
        truePair = std::make_unique<NameValuePair>(a);

        std::string s = songOptionParamName;
        pairWithoutValue = std::make_unique<NameValuePair>(s);
    }

    TEST_F(NameValuePairTests, ProperlyCreatesTruePair)
    {
        EXPECT_EQ(truePair->Name(), albumOptionParamName);
        EXPECT_EQ(truePair->Value(), albumValue);
    }

    TEST_F(NameValuePairTests, ProperlyCreatesPairWithoutValue)
    {
        EXPECT_EQ(pairWithoutValue->Name(), songOptionParamName);
        EXPECT_EQ(pairWithoutValue->Value(), "");
    }

    TEST_F(NameValuePairTests, EnforcesInvariants)
    {
        EXPECT_NO_THROW(NameValuePair{ albumNameValuePairArg });
        EXPECT_NO_THROW(NameValuePair{ songOptionParamName });
        EXPECT_THROW(NameValuePair{ "" }, NameValuePair::InvalidPair);
        EXPECT_THROW(NameValuePair{ missingNameValuePairArg }, 
            NameValuePair::InvalidPair);
        
        TestNameBundle test = GenerateTestNames(
            NameGenerationMode::NameValuePair);

        for (auto name : test.validNames)
            ASSERT_NO_THROW(NameValuePair{ name });

        for (auto name : test.invalidNames)
            ASSERT_THROW(NameValuePair{ name }, NameValuePair::InvalidPair);
    }

    TEST_F(NameValuePairTests, ProperlyChecksNameValuePair)
    {
        EXPECT_EQ(IsNameValuePair(albumNameValuePairArg), true);
        EXPECT_EQ(IsNameValuePair(songOptionParamName), true);
        EXPECT_EQ(IsNameValuePair(""), false);
        EXPECT_EQ(IsNameValuePair(missingNameValuePairArg), false);

        TestNameBundle test = GenerateTestNames(
            NameGenerationMode::NameValuePair);

        for (auto name : test.validNames)
            ASSERT_EQ(IsNameValuePair(name), true);

        for (auto name : test.invalidNames)
            ASSERT_EQ(IsNameValuePair(name), false);
    }
}
