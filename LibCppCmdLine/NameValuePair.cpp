// NameValuePair.cpp - Defines NameValuePair class memebers and functions.
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

#include "NameValuePair.h"

namespace CmdLine
{
    NameValuePair::NameValuePair(std::string pair)
    {
        if (!IsNameValuePair(pair))
        {
            throw InvalidPair{ nameError };
        }

        if (pair.find('=') != std::string::npos)
        {
            std::stringstream s(pair);
            std::getline(s, mName, '=');
            std::getline(s, mValue, '=');
        }
        else
        {
            mName = pair;
        }
    }

    NameValuePair::InvalidPair::InvalidPair(const char* message) 
        : std::invalid_argument{ message }
    {
    }

    bool IsNameValuePair(std::string pair)
    {
        if (pair.size() == 0)
            return false;

        if (pair.find('=') != std::string::npos)
        {
            std::stringstream s(pair);
            std::string name;
            std::getline(s, name, '=');
            if (!IsValidNonOptionName(name))
                return false;
        }
        else
        {
            if (!IsValidNonOptionName(pair))
                return false;
        }
        
        return true;
    }
}