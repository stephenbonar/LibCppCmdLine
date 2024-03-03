// Parser.cpp - Defines Parser class members and functions.
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

#include "Parser.h"

namespace CmdLine
{
    Parser::Parser(ProgParam* p, std::vector<std::string> args)
        : mProgParam{ p }, mArgs{ args }, mMultiPosParam{ nullptr }
    {
        if (mProgParam == nullptr)
            throw NullParameter{ nullProgParamError };

        if (args.size() < 1)
            throw EmptyArguments{ emptyArgsError };

        Option::Definition builtInHelpOptionDef;
        builtInHelpOptionDef.shortName = helpOptionShortName;
        builtInHelpOptionDef.longName = helpOptionLongName;
        builtInHelpOptionDef.description = helpOptionDescription;

        mBuiltInHelpOption = std::make_unique<Option>(builtInHelpOptionDef);
        Add(mBuiltInHelpOption.get());
    }

    Parser::Status Parser::Parse()
    {
        if (FillArgQueue() == Status::Failure)
            return Status::Failure;

        FillArgParamVector();

        if (PopulateArgParams() == Status::Failure)
            return Status::Failure;

        return Status::Success;
    }

    std::string Parser::GenerateUsage() const
    {
        std::stringstream usage;
        usage 
            << GeneratePlainUsage()
            << std::endl << std::endl
            << helpMessagePrefix << mProgParam->Name()
            << helpMessagePostfix << std::endl;
        return usage.str();
    }

    std::string Parser::GenerateHelp() const
    {
        std::stringstream usage;
        usage << GeneratePlainUsage();

        usage 
            << std::endl << std::endl << descriptionHeader << std::endl
            << "  " << mProgParam->Description();

        usage << std::endl << std::endl << posParamHeader << std::endl;
        for (auto p : mPosParams)
            usage << p->HelpInfo() << std::endl;

        if (mMultiPosParam != nullptr)
            usage << mMultiPosParam->HelpInfo() << std::endl;

        usage << std::endl << optionsHeader << std::endl;
        for (auto o : mOptions)
            usage << o->HelpInfo() << std::endl;

        return usage.str();
    }

    void Parser::Add(Option* o)
    {
        if (o == nullptr)
            throw NullParameter{ nullOptionError };

        for (const auto& option : mOptions)
        {
            const bool shortNamesMatch = option->Name() == o->Name();
            const bool longNamesMatch = option->LongName() == o->LongName();
            if (shortNamesMatch || longNamesMatch)
                throw DuplicateOption{ duplicateOptionError };
        }

        mOptions.push_back(o);
    }

    void Parser::Add(PosParam* p)
    {
        if (p == nullptr)
            throw NullParameter{ nullPosParamError };

        for (const auto& positional : mPosParams)
        {
            if (positional->Name() == p->Name())
                throw DuplicatePosParam{ duplicatePosParamError };
        }

        mPosParams.push_back(p);
    }

    Parser::Status Parser::FillArgQueue()
    {
        std::deque<std::string> workingArgQueue;

        // Re-initialize the argument queue in case it has already been filled.
        mArgQueue = std::deque<std::string>();

        // Shorten the name of the argument list to reduce line length.
        std::vector<std::string>& a = mArgs;

        // We need a working copy of the argument vector in queue form so we
        // can more easily move arguments from the working argument queue
        // into the Parser's internal argument queue, mArgQueue.
        workingArgQueue.insert(workingArgQueue.begin(), a.begin(), a.end());

        // The program argument is always first so it's the first to move into
        // the mArgQueue.
        std::string programArg = workingArgQueue.front();
        workingArgQueue.pop_front();
        mArgQueue.push_back(programArg);

        // Options should be parsed second so move all option arguments into
        // mArgQueue next.
        if (MoveOptionsToArgQueue(workingArgQueue) == Status::Failure)
            return Status::Failure;

        // Positional arguments (both single-value and multi-value) should be
        // moved last. Which type moves first depends on the parsing order.
        if (mMultiPosParam != nullptr)
        {
            MultiPosParam::ParsingOrder o = mMultiPosParam->Order();

            if (o == MultiPosParam::ParsingOrder::AfterOptions)
                ReverseMovePosArgsToArgQueue(workingArgQueue);
            else
                MovePosArgsToArgQueue(workingArgQueue);
        }
        else
        {
            MovePosArgsToArgQueue(workingArgQueue);
        }

        return Status::Success;
    }

    void Parser::FillArgParamVector()
    {
        // Shorten the name of mArgParams to reduce line length.
        std::vector<ArgParam*>& v = mArgParams;

        // Re-initialize the vector in case it was already filled.
        v = std::vector<ArgParam*>();

        // We need to know the size of all argument parameters combined so we
        // can reserve enough memory for the combining process. +1 is for
        // the ProgParam.
        std::size_t combinedSize = mOptions.size() + mPosParams.size() + 1;
        if (mMultiPosParam != nullptr)
            combinedSize++;

        v.reserve(combinedSize);

        // Fill the vector with argument parameters in the correct order so
        // they can be parsed in the correct order.
        v.push_back(mProgParam);
        v.insert(v.end(), mOptions.begin(), mOptions.end());
        v.insert(v.end(), mPosParams.begin(), mPosParams.end());
        if (mMultiPosParam != nullptr)
        {
            v.push_back(mMultiPosParam);
        }
    }

    Parser::Status Parser::PopulateArgParams()
    {
        while (!mArgQueue.empty())
        {
            bool argumentPopulated = false;

            // Successful population should always reduce the queue size
            std::size_t previousQueueSize = mArgQueue.size();

            for (auto* p : mArgParams)
            {
                if (p->CanPopulate(mArgQueue))
                {
                    argumentPopulated = p->Populate(mArgQueue);
                    break;
                }
            }

            // If the queue size was not reduced, we could have an endless
            // loop. We should return failure in this situation to break
            // out of the loop. 
            bool endlessLoop = mArgQueue.size() == previousQueueSize;

            if (!argumentPopulated || endlessLoop)
            {
                return Status::Failure;
            }
        }

        return Status::Success;
    }

    void Parser::Set(Option::Style s)
    {
        for (auto option : mOptions)
            option->Set(s);
    }

    bool Parser::AllMandatoryParamsSpecified()
    {
        for (const auto* p : mArgParams)
        {
            if (p->IsMandatory() && !p->IsSpecified())
                return false;
        }

        return true;
    }

    Parser::Status Parser::MoveOptionsToArgQueue(std::deque<std::string>& 
        source)
    {
        auto i = source.begin();
        while (i != source.end())
        {
            std::string argument = *i;

            // Move onto the next argument if it's not an Option.
            if (!IsOption(argument))
            {
                i++;
                continue;
            }

            // If the curret iteration of the loop has made it this far, it 
            // means we're currently dealing with an option argument and need 
            // to find out how many arguments the corresponding Option will 
            // consume so we know how many arguments to push into the queue on
            // this current iteration.
            std::size_t argsToConsume = 0;

            for (auto* o : mOptions)
            {
                if (o->CanPopulate(source))
                {
                    argsToConsume = o->Consumes(source);
                    break;
                }
            }

            // If there was not a corresponding Option, it means the user 
            // supplied a bogus option and parsing will fail. Also, if there 
            // are not enough arguments for the Option to consume, parsing will
            // also fail.
            if (argsToConsume == 0 || argsToConsume > source.size())
            {
                return Status::Failure;
            }

            if (argsToConsume == 2)
            {
                // Must be a value option because it consumes two arguments. We
                // need to obtain the second argument representing the value by
                // dereferencing iterator + 1.
                std::string argument2 = *(i + 1);

                mArgQueue.push_back(argument);
                mArgQueue.push_back(argument2);
                i = source.erase(i);
                i = source.erase(i);
            }
            else
            {
                mArgQueue.push_back(argument);
                i = source.erase(i);
            }
        }

        return Status::Success;
    }

    void Parser::MovePosArgsToArgQueue(std::deque<std::string>& source)
    {
        auto i = source.begin();
        while (i != source.end())
        {
            std::string argument = *i;
            mArgQueue.push_back(argument);
            i = source.erase(i);
        }
    }

    void Parser::ReverseMovePosArgsToArgQueue(std::deque<std::string>& source)
    {
        // Create separate working queues for arguments that populate 
        // single-value PosParams and the mMultiPosParam so they can be
        // parsed in the correct order
        std::deque<std::string> posArgs;
        std::deque<std::string> mulPosArgs;

        // Shorten the name of mArgQueue to reduce line size.
        std::deque<std::string>& dest = mArgQueue;

        // Since arguments that populate mMultiPosParam are first when
        // the ParsingOrder is AfterOptions, we need to determine how
        // many there are so we know when to stop filling the mulPosArgs queue
        // and start filling posArgs.
        std::size_t numMulPos = source.size() - mPosParams.size();

        int mulPosEncountered = 0;
        auto i = source.begin();
        while (i != source.end())
        {
            std::string argument = *i;

            if (mulPosEncountered < numMulPos)
            {
                mulPosEncountered++;
                mulPosArgs.push_back(argument);
            }
            else
            {
                posArgs.push_back(argument);
            }

            i = source.erase(i);
        }

        dest.insert(dest.end(), posArgs.begin(), posArgs.end());

        // Arguments that populate mMultiPosParam need to be parsed at
        // the end even if the program has the user specify them before
        // the single-value positional arguments.
        dest.insert(dest.end(), mulPosArgs.begin(), mulPosArgs.end());
    }

    std::string Parser::GenerateBracketedUsageLabel(ArgParam* p) const
    {
        std::stringstream label;

        if (p->IsMandatory())
        {
            label << mandatoryOpenBracket << p->Name();
            label << mandatoryCloseBracket;
        }
        else
        {
            label << optionalOpenBracket << p->Name();
            label << optionalCloseBracket;
        }

        return label.str();
    }

    std::string Parser::GeneratePlainUsage() const
    {
        std::stringstream usage;
        usage 
            << usageHeader << std::endl
            << "  " << mProgParam->Name() << ' '
            << optionalOpenBracket << optionsLabel << optionalCloseBracket;

        if (mMultiPosParam != nullptr)
        {
            if (mMultiPosParam->Order() != MultiPosParam::ParsingOrder::End)
            {
                usage 
                    << ' ' << GenerateBracketedUsageLabel(mMultiPosParam)
                    << multiPosParamIndicator;

                for (auto* p : mPosParams)
                    usage << ' ' << GenerateBracketedUsageLabel(p);
            }
            else
            {
                for (auto* p : mPosParams)
                    usage << ' ' << GenerateBracketedUsageLabel(p);

                usage 
                    << ' ' << GenerateBracketedUsageLabel(mMultiPosParam)
                    << multiPosParamIndicator;
            }
        }
        else
        {
            for (auto* p : mPosParams)
                usage << ' ' << GenerateBracketedUsageLabel(p);
        }

        return usage.str();
    }

    Parser::DuplicateOption::DuplicateOption(const char* message)
        : invalid_argument(message)
    {
    }

    Parser::DuplicatePosParam::DuplicatePosParam(const char* message)
        : invalid_argument(message)
    {
    }

    Parser::NullParameter::NullParameter(const char* message)
        : invalid_argument(message)
    {
    }

    Parser::EmptyArguments::EmptyArguments(const char* message)
        : invalid_argument(message)
    {
    }
}