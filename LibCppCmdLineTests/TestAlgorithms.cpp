// TestAlgorithms.cpp - Defines shared test functions.
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

#include "TestAlgorithms.h"

namespace CmdLine
{
    enum class MediaOptionType 
    { 
        UnixPrint,
        UnixPrintNoParams,
        UnixEdit,
        WindowsPrint, 
        WindowsEdit 
    };

    TestNameBundle GenerateTestNames(NameGenerationMode m)
    {
        TestNameBundle b;

        for (int i = 0; i < SCHAR_MAX; i++)
        {
            char current = i;
            std::stringstream namestream;
            namestream << "test" << current << "ing";

            if (std::isalnum(current) || current == '?')
            {
                b.validShortNames.push_back(current);
            }
            else
            {
                b.invalidShortNames.push_back(current);
            }

            if (std::isalnum(current) || current == '-' || current == '_')
            {
                b.validNames.push_back(namestream.str());
            }
            else
            {
                if (m == NameGenerationMode::NameValuePair)
                {
                    if (current != '=')
                    {
                        b.invalidNames.push_back(namestream.str());
                    }
                }
                else
                {
                    b.invalidNames.push_back(namestream.str());
                } 
            }
        }

        std::string unixShort { unixOptionShortPrefix };
        std::string unixLong { unixOptionLongPrefix };
        std::string windowsShort{ windowsOptionShortPrefix };
        std::string windowsLong{ windowsOptionLongPrefix };

        b.invalidNames.push_back(unixShort + "test");
        b.invalidNames.push_back(unixLong + "test");
        b.invalidNames.push_back(windowsShort + "test");
        b.invalidNames.push_back(windowsLong + "test");

        b.invalidNames.push_back("invalid name");
        b.invalidNames.push_back("thisnameistoolongmorethan20chars");
        b.invalidNames.push_back("");

        return b;
    }

    std::string GenerateExpectedMediaOptionHelpInfo(MediaOptionType t)
    {
        std::stringstream helpInfo;

        switch (t)
        {
        case MediaOptionType::UnixPrintNoParams:
            helpInfo << unixPrintOptionHelpLine;
            break;
        case MediaOptionType::UnixPrint:
            helpInfo << unixPrintOptionHelpLine << std::endl;
            break;
        case MediaOptionType::UnixEdit:
            helpInfo << unixEditOptionHelpLine << std::endl;
            break;
        case MediaOptionType::WindowsPrint:
            helpInfo << windowsPrintOptionHelpLine << std::endl;
            break;
        case MediaOptionType::WindowsEdit:
            helpInfo << windowsEditOptionHelpLine << std::endl;
            break;
        }
        
        if (t != MediaOptionType::UnixPrintNoParams)
        {
            helpInfo << std::endl;
            helpInfo << songOptionParamHelpLine << std::endl;
            helpInfo << artistOptionParamHelpLine << std::endl;
            helpInfo << albumOptionParamHelpLine << std::endl;
        }

        return helpInfo.str();
    }

    std::string GenerateExpectedUnixPrintOptionHelpInfo()
    {
        return GenerateExpectedMediaOptionHelpInfo(MediaOptionType::UnixPrint);
    }

    std::string GenerateExpectedUnixPrintOptionHelpInfoNoParams()
    {
        MediaOptionType t = MediaOptionType::UnixPrintNoParams;

        return GenerateExpectedMediaOptionHelpInfo(t);
    }

    std::string GenerateExpectedUnixEditOptionHelpInfo()
    {
        return GenerateExpectedMediaOptionHelpInfo(MediaOptionType::UnixEdit);
    }

    std::string GenerateExpectedWindowsPrintOptionHelpInfo()
    {
        return GenerateExpectedMediaOptionHelpInfo(
            MediaOptionType::WindowsPrint);
    }

    std::string GenerateExpectedPositionalUsage(ProgramInfo i)
    {
        std::stringstream usage;

        for (auto p : i.positionals)
        {
            char openBracket = optionalCloseBracket;
            char closeBracket = optionalOpenBracket;

            if (p->IsMandatory())
            {
                openBracket = mandatoryOpenBracket;
                closeBracket = mandatoryCloseBracket;
            }

            usage << ' ' << openBracket << p->Name() << closeBracket;
        }

        return usage.str();
    }

    std::string GenerateExpectedMultiPositionalUsage(ProgramInfo i)
    {
        std::stringstream usage;

        if (i.multiPosParam != nullptr)
        {
            char openBracket = optionalOpenBracket;
            char closeBracket = optionalCloseBracket;

            if (i.multiPosParam->IsMandatory())
            {
                openBracket = mandatoryOpenBracket;
                closeBracket = mandatoryCloseBracket;
            }

            usage << ' ';
            usage << openBracket << i.multiPosParam->Name() << closeBracket;
            usage << multiPosParamIndicator;
        }

        return usage.str();
    }

    std::string GenerateExpectedUsage(ProgramInfo i)
    {
        std::stringstream usage;
        usage << usageHeader << std::endl;
        usage << "  " << i.program->Name() << ' ';
        usage << optionalOpenBracket << optionsLabel << optionalCloseBracket;

        auto afterOptions = MultiPosParam::ParsingOrder::AfterOptions;

        if (i.multiPosParam == nullptr)
        {
            usage << GenerateExpectedPositionalUsage(i);
        }
        else if (i.multiPosParam->Order() == afterOptions)
        {
            usage << GenerateExpectedMultiPositionalUsage(i);
            usage << GenerateExpectedPositionalUsage(i);
        }
        else
        {
            usage << GenerateExpectedPositionalUsage(i);
            usage << GenerateExpectedMultiPositionalUsage(i);
        }

        return usage.str();
    }

    std::string GenerateExpectedProgramHelp(ProgramInfo i)
    {
        std::stringstream usage;
        usage << GenerateExpectedUsage(i);

        usage << std::endl << std::endl << descriptionHeader << std::endl;
        usage << "  " << i.program->Description() << std::endl;
        
        usage << std::endl << posParamHeader << std::endl;
        
        for (auto p : i.positionals)
        {
            usage << p->HelpInfo() << std::endl;
        }
        
        if (i.multiPosParam != nullptr)
        {
            usage << i.multiPosParam->HelpInfo() << std::endl;
        }

        usage << std::endl << optionsHeader << std::endl;

        Option::Definition expectedHelpOptionDef;
        expectedHelpOptionDef.shortName = helpOptionShortName;
        expectedHelpOptionDef.longName = helpOptionLongName;
        expectedHelpOptionDef.description = helpOptionDescription;
        Option expectedHelpOption{ expectedHelpOptionDef };

        usage << expectedHelpOption.HelpInfo() << std::endl;

        for (auto o : i.options)
        {
            usage << o->HelpInfo() << std::endl;
        }

        return usage.str();
    }

    std::string GenerateExpectedUsageWithMessage(ProgramInfo i)
    {
        std::stringstream usage;
        usage << GenerateExpectedUsage(i);
        usage << std::endl << std::endl;
        usage << helpMessagePrefix << i.program->Name() << helpMessagePostfix;
        usage << std::endl;

        return usage.str();
    }

    void ExpectParameterState(const Param* p, const ParamState* s)
    {
        EXPECT_EQ(p->Name(), s->name);
        EXPECT_EQ(p->Description(), s->description);
        EXPECT_EQ(p->IsMandatory(), s->isMandatory);
        EXPECT_EQ(p->IsSpecified(), s->isSpecified);
    }

    OptionState GetInitialState(Option::Definition d)
    {
        return GetInitialOptionState<Option::Definition, OptionState>(d);
    }

    ValueOptionState GetInitialState(ValueOption::Definition d)
    {
        return GetInitialOptionState<ValueOption::Definition, ValueOptionState>(
            d);
    }

    MultiPosParamState GetInitialState(MultiPosParam::Definition d)
    {
        MultiPosParamState s;
        s.name = d.name;
        s.description = d.description;
        s.isMandatory = d.isMandatory;
        s.order = d.order;
        return s;
    }

    PosParamState GetInitialState(PosParam::Definition d)
    {
        return GetInitialParamState<PosParam::Definition, PosParamState>(d);
    }

    OptionParamState GetInitialState(OptionParam::Definition d)
    {
        return GetInitialParamState<OptionParam::Definition, OptionParamState>(
            d);
    }

    ProgParamState GetInitialState(ProgParam::Definition d)
    {
        return GetInitialParamState<ProgParam::Definition, ProgParamState>(d);
    }

    void ExpectState(const Option& o, const OptionState& s)
    {
        ExpectParameterState(&o, &s);
        EXPECT_EQ(o.LongName(), s.longName);
    }

    void ExpectState(const ValueOption& o, const ValueOptionState& s)
    {
        ExpectParameterState(&o, &s);
        EXPECT_EQ(o.LongName(), s.longName);
        EXPECT_EQ(o.Values(), s.values);
    }

    void ExpectState(const OptionParam& p, const OptionParamState& s)
    {
        ExpectParameterState(&p, &s);
        EXPECT_EQ(p.Value(), s.value);
    }

    void ExpectState(const ProgParam& p, const ProgParamState& s)
    {
        ExpectParameterState(&p, &s);
        EXPECT_EQ(p.Value(), s.value);
    }

    void ExpectState(const PosParam& p, const PosParamState& s)
    {
        ExpectParameterState(&p, &s);
        EXPECT_EQ(p.Value(), s.value);
    }

    void ExpectState(const MultiPosParam& p, const MultiPosParamState& s)
    {
        ExpectParameterState(&p, &s);
        EXPECT_EQ(p.Values(), s.values);
        EXPECT_EQ(p.Order(), s.order);
    }
}