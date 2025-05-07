// Option.cpp - Defines Option class members and functions.
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

#include "Option.h"

namespace CmdLine
{
    Option::Option(Definition d)
        : mIsSpecified{ false }, mDefinition{ d }
    {
        if (mDefinition.shortName == 0 && mDefinition.longName == "")
            throw InvalidDefinition(optionEmptyNameError);

        if (mDefinition.shortName != 0)
        {
            bool isAlphaNumeric = std::isalnum(mDefinition.shortName);
            if (!isAlphaNumeric && mDefinition.shortName != '?')
                throw InvalidDefinition(optionShortNameError);
        }
        
        if (mDefinition.longName != "")
        {
            if (!IsValidNonOptionName(mDefinition.longName))
                throw InvalidDefinition(optionLongNameError);
        }
    }

    std::string Option::Name() const
    {
        if (mDefinition.shortName != 0 && mDefinition.longName != "")
            return PrefixShortName();
        else if (mDefinition.longName == "")
            return PrefixShortName();
        else
            return PrefixLongName();
    }

    std::string Option::HelpInfo() const
    {
        std::stringstream name;
        if (mDefinition.shortName != 0 && mDefinition.longName != "")
            name << PrefixShortName() << ", " << PrefixLongName();
        else if (mDefinition.shortName == 0)
            name << PrefixLongName();
        else
            name << PrefixShortName();

        return GenerateHelpLine(name.str(), mDefinition.description);
    }

    bool Option::Populate(std::deque<std::string>& args)
    {
        if (CanPopulate(args))
        {
            args.pop_front();
            mIsSpecified = true;
            return true;
        }

        return false;
    }

    bool Option::CanPopulate(const std::deque<std::string>& args) const
    {
        if (args.size() > 0)
        {
            std::string a = args.front();
            if (a == PrefixShortName() || a == PrefixLongName())
                return true;
        }
        
        return false;
    }

    std::string Option::PrefixShortName() const
    {
        // PrependPrefix works with strings so convert the char to a string.
        std::string shortName{ mDefinition.shortName };

        if (mDefinition.style == Option::Style::Windows)
            return PrependPrefix(windowsOptionShortPrefix, shortName);
        else
            return PrependPrefix(unixOptionShortPrefix, shortName);
    }

    std::string Option::PrefixLongName() const
    {
        if (mDefinition.longName == "")
            return "";

        std::string prefix = "";
        if (mDefinition.style == Option::Style::Windows)
            prefix = windowsOptionLongPrefix;
        else
            prefix = unixOptionLongPrefix;
        
        return PrependPrefix(prefix, mDefinition.longName);
    }

    std::string Option::PrependPrefix(std::string prefix, std::string name) 
        const
    {
        std::stringstream prefixedName;
        prefixedName << prefix << name;
        return prefixedName.str();
    }

    bool StartsWithOptionPrefix(std::string arg)
    {
        bool s = arg.rfind(unixOptionShortPrefix, 0) == 0;
        s = s || arg.rfind(unixOptionLongPrefix, 0) == 0;
        s = s || arg.rfind(windowsOptionShortPrefix, 0) == 0;
        return s || arg.rfind(windowsOptionLongPrefix, 0) == 0;
    }

    bool IsOption(std::string arg)
    {
        if (!StartsWithOptionPrefix(arg))
            return false;

        if (arg.length() <= 1)
            return false;

        std::string argWithoutPrefix = arg.substr(1);

        // Account for the Unix long option where 2 chars need to be removed
        if (StartsWithOptionPrefix(argWithoutPrefix))
            argWithoutPrefix = argWithoutPrefix.substr(1);

        if (!IsValidNonOptionName(argWithoutPrefix))
            return false;

        return true;
    }
}
