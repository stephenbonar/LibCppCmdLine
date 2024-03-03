// Validation.h - Defines functions for performing validation.
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

#include "Validation.h"

bool CmdLine::IsValidNonOptionName(std::string name)
{
    if (name.size() > maxNameSize || name.size() < minNameSize)
        return false;

    for (auto c : name)
    {
        if (!std::isalnum(c) && c != '-' && c != '_')
            return false;
    }

    if (name.rfind(unixOptionShortPrefix, 0) == 0)
        return false;
    else if (name.rfind(unixOptionLongPrefix, 0) == 0)
        return false;
    else if (name.rfind(windowsOptionShortPrefix, 0) == 0)
        return false;
    else if (name.rfind(windowsOptionLongPrefix, 0) == 0)
        return false;
    else
        return true;
}
