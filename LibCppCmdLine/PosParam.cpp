// PosParam.cpp - Defines PosParam class members and functions.
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

#include "PosParam.h"

namespace CmdLine
{
    PosParam::PosParam(Definition d) 
        : mDefinition{ d }, mIsSpecified{ false }
    {
        if (!IsValidNonOptionName(mDefinition.name))
            throw InvalidDefinition(nameError);
    }

    std::string PosParam::HelpInfo() const
    {
        return GenerateHelpLine(mDefinition.name, mDefinition.description);
    }

    bool PosParam::Populate(std::deque<std::string>& args)
    {
        if (CanPopulate(args))
        {
            mValue = args.front();
            args.pop_front();
            mIsSpecified = true;
            return true;
        }
        else
        {
            return false;
        }    
    }

    bool PosParam::CanPopulate(const std::deque<std::string>& args) const
    {
        if (mIsSpecified)
            return false;

        if (args.size() > 0)
        {
            if (!IsOption(args.front()))
                return true;
        }

        return false;
    }
}
