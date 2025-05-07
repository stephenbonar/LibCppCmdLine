// MultiPosParam.cpp - Defines MultiPosParam class members and functions.
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

#include "MultiPosParam.h"

namespace CmdLine
{
    MultiPosParam::MultiPosParam(Definition d)
        : mDefinition{ d }, mIsSpecified{ false }, mOrder{ ParsingOrder::End }
    {
        if (!IsValidNonOptionName(mDefinition.name))
            throw InvalidDefinition{ nameError };
    }

    std::string MultiPosParam::HelpInfo() const
    {
        return GenerateHelpLine(mDefinition.name, mDefinition.description);
    }

    bool MultiPosParam::Populate(std::deque<std::string>& args)
    {
        if (CanPopulate(args))
        {
            mIsSpecified = true;

            while (args.size() > 0)
            {
                mValues.push_back(args.front());
                args.pop_front();
            }

            return true;
        }
        else
        {
            return false;
        }
    }

    bool MultiPosParam::CanPopulate(const std::deque<std::string>& args) const
    {
        if (args.size() == 0)
            return false;
        
        for (const auto& a : args)
        {
            if (IsOption(a))
                return false;
        }

        return true;
    }

    std::size_t MultiPosParam::Consumes(const std::deque<std::string>& args)
        const
    {
        std::size_t numOptions = 0;
        for (const auto& a : args)
        {
            if (IsOption(a))
                numOptions++;
        }
        
        return args.size() - numOptions;
    }
}
