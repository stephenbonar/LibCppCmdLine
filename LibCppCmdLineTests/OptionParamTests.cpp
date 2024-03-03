// OptionParamTests.cpp - Defines tests for the OptionParam class.
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

#include "OptionParamTests.h"

namespace CmdLine
{
    OptionParamTests::OptionParamTests()
    {
        songDef.name = songOptionParamName;
        songDef.description = songOptionParamDescription;
        songParam = std::make_unique<OptionParam>(songDef);
        expectedSongState = GetInitialState(songDef);

        albumDef.name = albumOptionParamName;
        albumDef.description = albumOptionParamDescription;
        albumParam = std::make_unique<OptionParam>(albumDef);
        expectedAlbumState = GetInitialState(albumDef);

        // Copy the song descriptor for convinience
        mandatoryDef = songDef;
        OptionParam::Definition& m = mandatoryDef;
        m.isMandatory = true;
        mandatoryParam = std::make_unique<OptionParam>(m);
        expectedMandatoryState = GetInitialState(m);
    }

    void OptionParamTests::TestExpectedStates()
    {
        ExpectState(*songParam, expectedSongState);
        ExpectState(*albumParam, expectedAlbumState);
        ExpectState(*mandatoryParam, expectedMandatoryState);
    }

    TEST_F(OptionParamTests, GeneratesHelpInfoProperly)
    {
        std::string expectedHelpInfo{ songOptionParamHelpLine };
        EXPECT_EQ(songParam->HelpInfo(), expectedHelpInfo);
    }

    TEST_F(OptionParamTests, CreatesValueParamProperly)
    {      
        TestExpectedStates();
    }

    TEST_F(OptionParamTests, ChecksCanPopulateProperly)
    {
        EXPECT_EQ(songParam->CanPopulate(songPair), true);
        EXPECT_EQ(songParam->CanPopulate(albumPair), false);
        EXPECT_EQ(albumParam->CanPopulate(albumPair), true);
        EXPECT_EQ(albumParam->CanPopulate(songPair), false);
    }

    TEST_F(OptionParamTests, PopulatesValueParamProperly)
    {
        TestExpectedStates();
        
        expectedSongState.isSpecified = true;
        EXPECT_TRUE(songParam->Populate(songPair));
        
        expectedAlbumState.isSpecified = true;
        expectedAlbumState.value = albumValue;
        EXPECT_TRUE(albumParam->Populate(albumPair));
        
        TestExpectedStates();
    }

    TEST_F(OptionParamTests, DoesNotPopulateNonMatchingName)
    {
        TestExpectedStates();

        EXPECT_FALSE(songParam->Populate(albumPair));
        EXPECT_FALSE(albumParam->Populate(songPair));
        
        TestExpectedStates();
    }

    TEST_F(OptionParamTests, ConstructorEnforcesInvariants)
    {
        TestParamInvariants<OptionParam::Definition, OptionParam>();
    }
}
