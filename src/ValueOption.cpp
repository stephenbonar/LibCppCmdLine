// ValueOption.cpp - Defines ValueOption class members and functions.
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

#include "ValueOption.h"

namespace CmdLine
{
    ValueOption::ValueOption(Definition d)
        : Option{ d }
    {
    }

    bool ValueOption::Populate(std::deque<std::string>& args)
    {
        if (CanPopulate(args))
        {
            Option::Populate(args);
            std::string value = args.front();
            args.pop_front();
            mValues.push_back(value);

            try
            {
                // We know the ValueOption has populated successfully at this
                // point, so now we try to parse the value as a name-value
                // pair. 
                auto pair = std::make_unique<NameValuePair>(value);
                for (auto p : mParams)
                {
                    if (p->CanPopulate(*pair))
                    {
                        p->Populate(*pair);

                        // Once we've found an OptionParam to populate, we can
                        // return true to end the loop early to save cycles. 
                        return true;
                    }
                }

                // Even if no OptionParams were populated, the ValueOption
                // itself was so we can still return true. 
                return true;
            }
            catch (NameValuePair::InvalidPair& e)
            {
                // Even if the option's value does not represent a 
                // NameValuePair, we can still return true because the 
                // ValueOption was successfully populated with the value.
                return true;
            }
        }
        else
        {
            return false;
        }
    }

    bool ValueOption::CanPopulate(const std::deque<std::string>& args) const
    {
        if (Option::CanPopulate(args))
        {
            if (args.size() >= 2)
                return true;
        }
        
        return false;
    }

    std::string ValueOption::HelpInfo() const
    {
        std::stringstream help;
        help << Option::HelpInfo();

        if (mParams.size() > 0)
        {
            help << std::endl << std::endl;
            for (auto p : mParams)
                help << p->HelpInfo() << std::endl;
        }

        return help.str();
    }

    void ValueOption::Add(OptionParam* p)
    {
        if (p == nullptr)
            throw NullOptionParam{ nullOptionParamError };

        for (auto param : mParams)
        {
            if (param->Name() == p->Name())
                throw DuplicateOptionParam{ duplicateOptionParamError };
        }

        mParams.push_back(p);
    }

    ValueOption::DuplicateOptionParam::DuplicateOptionParam(
        const char* message) : std::invalid_argument(message)
    {
    }

    ValueOption::NullOptionParam::NullOptionParam(const char* message)
        : std::invalid_argument(message)
    {
    }
}

