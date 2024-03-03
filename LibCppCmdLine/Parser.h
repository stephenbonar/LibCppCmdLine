// Parser.h - Declares the Parser class.
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

#ifndef CMD_LINE_PARSER_H
#define CMD_LINE_PARSER_H

#include <vector>
#include <string>
#include <deque>
#include <stdexcept>
#include <memory>
#include "Constants.h"
#include "ProgParam.h"
#include "Option.h"
#include "PosParam.h"
#include "MultiPosParam.h"

namespace CmdLine
{
    /// @brief Parses command line arguments.
    /// 
    /// The command line Parser populates command line parameters (Param) from
    /// command line arguments. A Parser is created from a ProgParam and a 
    /// vector containing a list of command line arguments. Prior to parsing 
    /// the arguments, the program must add command line parameters (Param) to
    /// the Parser so it can populate them. Such parameters include Options 
    /// (both Option and ValueOption) and positional parameters (PosParam). The
    /// parser also allows zero or one multi-positional parameters 
    /// (MultiPosParam) to be set (positional parameters that accept multiple
    /// positional arguments). Finally, the Parser can generate command line 
    /// usage and help information for the program based on each Param added to
    /// the Parser.
    class Parser
    {
    public:
        /// @brief Determines the status of the Parser.
        enum class Status 
        {
            /// @brief Indicates parsing was successful.
            ///
            /// When parsing is successful, the program is free to examine
            /// the values that were stored in each command line Param as a
            /// result of parsing the command line arguments. Such values serve
            /// as input to the program from the command line.
            Success,

            /// @brief Indicates parsing failed.
            ///
            /// When parsing failes, it is usually as a result of invalid 
            /// command line arguments being passed to the program (i.e. a 
            /// mandatory Param was not specified, etc.). In such cases,
            /// the program should output usage information.
            Failure 
        };

        /// @brief An exception thrown for adding a duplicate Option.
        /// 
        /// This exception is thrown when the programmer attempts to add
        /// a duplicate Option to the Parser. 
        class DuplicateOption : public std::invalid_argument
        {
        public:
            /// @brief Constructs a DuplicateOption exception.
            ///
            /// @param message The message to include with the exception.
            DuplicateOption(const char* message);
        };

        /// @brief An exception thrown for adding duplicate PosParam.
        /// 
        /// This exception is thrown when the programmer attempts to add
        /// a duplicate PosParam to the Parser. 
        class DuplicatePosParam : public std::invalid_argument
        {
        public:
            /// @brief Constructs an DuplicatePosParam exception.
            ///
            /// @param message The message to include with the exception.
            DuplicatePosParam(const char* message);
        };

        /// @brief An exception thrown for adding null Parameter.
        /// 
        /// This exception is thrown when the programmer attempts to add a
        /// null Parameter to the Parser. 
        class NullParameter : public std::invalid_argument
        {
        public:
            /// @brief Constructs a NullParameter exception.
            ///
            /// @param message The message to include with the exception.
            NullParameter(const char* message);
        };

        /// @brief An exception thrown for a Parser with empty arguments.
        /// 
        /// This exception is thrown when the programmer attempts to create
        /// a new Parser with empty command line arguments. 
        class EmptyArguments : public std::invalid_argument
        {
        public:
            /// @brief Constructs an EmptyArguments exception.
            ///
            /// @param message The message to include with the exception.
            EmptyArguments(const char* message);
        };

        /// @brief Constructs a new Parser.
        ///
        /// @param p The ProgParam to populate with the program name.
        /// @param args The command line arguments to parse.
        /// @invariant There is at least one argument (program name).
        /// @invariant Option, PosParam, and ProgParam are not null.
        /// @invariant Cannot add a duplicate Option or PosParam.
        /// @invariant There can only be zero or one MultiPosParam.
        /// @invariant There must be exactly one ProgParam.
        /// @exception NullParamter The parameter is null.
        /// @exception EmptyArguments The arguments were empty.
        Parser(ProgParam* p, std::vector<std::string> args);

        /// @brief Parses the command line arguments.
        ///
        /// Parsing the command line arguments will populate any command line
        /// Param (ProgParam, Option, ValueOption, PosParam, and 
        /// MultiPosParam) that have been added or set on the Parser and
        /// that could be populated by one of the arguments.
        /// 
        /// @return Success upon successful parsing, otherwise failure.
        Status Parse();

        /// @brief Generates program usage info.
        ///
        /// Generates program usage info from each command line Param 
        /// (ProgParam, Option, ValueOption, PosParam, and MultiPosParam) that
        /// has been added or set on the Parser. Usage information is
        /// typically shown when the user supplies invalid command line
        /// arguments, or no arguments, to the program.
        /// 
        /// @return The program usage information.
        std::string GenerateUsage() const;

        /// @brief Generates program help info.
        ///
        /// Generates program help info from each command line Param
        /// (ProgParam, Option, ValueOption, PosParam, and MultiPosParam) that
        /// has been added or set on the Parser. Help info is the detailed
        /// help information that programs typically show when a help option
        /// (-h, --help, -?, /h, /help, etc.) is specified.
        /// 
        /// @return The program help information.
        std::string GenerateHelp() const;

        /// @brief Determines if the built-in help Option has been specified.
        ///
        /// Since the built-in help Option is not defined outside of the
        /// parser, use this method to determine if it has been specified.
        /// 
        /// @return True if it has been specified, otherwise false.
        bool BuiltInHelpOptionIsSpecified() const
        {
            return mBuiltInHelpOption->IsSpecified();
        }

        /// @brief Adds an Option to the Parser.
        ///
        /// Adds an Option pointer to the Parser so that the Parser can
        /// populate the Option if the user specifies it at the command line.
        /// This method will also accept pointers of the derived class 
        /// ValueOption.
        /// 
        /// @param o The Option pointer to add to the Parser.
        /// @pre The Option pointer must not be null.
        /// @pre The Option must not be a duplicate.
        /// @post The Option is added to the Parser.
        /// @exception DuplicateOption Tried to add a duplicate Option.
        void Add(Option* o);

        /// @brief Adds a PosParam to the Parser.
        ///
        /// Adds a PosParam pointer to the Parser so that the Parser can
        /// populate the PosParam if the user specifies it at the 
        /// command line.
        /// 
        /// @param p The PosParam pointer to add to the Parser.
        /// @pre The PosParam pointer must not be null.
        /// @pre The PosParam must not be a duplicate.
        /// @post The PosParam is added to the Parser.
        /// @exception DuplicatePosParam Tried to add duplicate PosParam.
        void Add(PosParam* p);

        /// @brief Sets a MultiPosParam on the Parser.
        ///
        /// A Parser can only have zero or one MultiPosParam at a time. By
        /// default, the Parser has no MultiPosParams unless a pointer to one
        /// is set. If the pointer is null, the Parser does not process the
        /// MultiPosParam. 
        /// 
        /// @param p The pointer to the MultiPosParam to set on the Parser.
        /// @post Parser MultiPosParam is either set or cleared (nulltpr).
        void Set(MultiPosParam* p) { mMultiPosParam = p; }

        /// @brief Sets the Option::Style on all options added to the Parser.
        ///
        /// An Option usually has its Style set during creation in its 
        /// Option::Definition. However, it may be more convenient / less
        /// error prone to set the Option::Style for all options after they
        /// have been added to the Parser for the sake of consistency. That
        /// is the purpose of this method.
        /// 
        /// @param s The Option::Style to set on each Option.
        /// @pre All Options must already be added to the Parser
        /// @post All Options have their Option::Style changed.
        void Set(Option::Style s);

        /// @brief Checks that all mandatory Param were specified.
        /// 
        /// @return True if all are specified, otherwise false.
        bool AllMandatoryParamsSpecified();
    private:
        /// @brief Fills the internal argument queue in the correct order.
        ///
        /// The command line argument vector the parser is created with should
        /// have the arguments in the order they were specified in at the
        /// command line. However, to allow for situations where some Options
        /// are specified after PosParam or where the 
        /// MultiPosParam::ParsingOrder is AfterOptions instead of End,
        /// this method fills the argument queue in the correct order
        /// needed for parsing.
        /// 
        /// @return Status::Success if successful, otherwise Status::Failure.
        /// @pre All option arguments have a corresponding Option.
        /// @pre There are enough arguments for each Option.
        /// @post The argument queue is filled in the correct order. 
        Status FillArgQueue();

        /// @brief Fills the internal ArgParam vector.
        ///
        /// The internal ArgParam vector contains pointers to each
        /// ArgParam that was added to the Parser of type
        /// Option, ValueOption, PosParam, and MultiPosParam. All of these 
        /// types inherit from ArgParam. This function combines these
        /// separate types into a single vector of pointers to their
        /// parent class so they can all be processed together in the
        /// same way.
        /// 
        /// @post The ArgParam vector is filled.
        void FillArgParamVector();

        /// @brief Populates all ArgParams.
        ///
        /// This function processes the internal argument queue and attempts
        /// to populate an ArgParam with each argument in the queue.
        /// 
        /// @return Status::Success if successful, otherwise Status::Failure.
        /// @pre All arguments must be able to populate an ArgParam.
        /// @post All ArgParams that can be populated are populated.
        /// @post The argument queue is emptied.
        Status PopulateArgParams();

        /// @brief Moves all options from the source queue to mArgQueue.
        ///
        /// Moves all option arguments from the source argument queue
        /// to the internal argument queue, mArgQueue. The idea is to
        /// take a working copy of the original argument list as a queue
        /// and move all the options from the working queue to the
        /// internal argument queue so that all the options are together
        /// in the internal argument queue.
        ///
        /// @param source The arugment queue to move options from.
        /// @return Status::Success if successful, otherwise Status::Failure.
        /// @pre The elements of source queue are copied from mArgs.
        /// @post The option arguments are moved from source to mArgQueue.
        Status MoveOptionsToArgQueue(std::deque<std::string>& source);

        /// @brief Moves positional args from the source queue to mArgQueue.
        ///
        /// Moves all positional arguments (including arguments that populate
        /// both PosParam and MultiPosParam) from the source argument queue to
        /// the internal argument queue, mArgQueue. The idea is to take a 
        /// working copy of the original argument list as a queue *after* all
        /// option arguments have been moved out of it into the internal 
        /// argument queue. This ensures options arguments are processed first,
        /// followed by the arguments that populate PosParams, followed by the 
        /// arguments that populate MultiPos. Call this function if 
        /// mMultiPosParam has a MultiPosParam::ParsingOrder of End or is
        /// null, otherwise call ReverseMovePosArgsToArgQueue().
        /// 
        /// @param source The argument queue to move positional args from.
        /// @pre The elements of source queue were copied from mArgs.
        /// @pre The option arguments were moved out of source queue.
        /// @post The elements of source are moved into mArgQueue.
        /// @post The source queue is emptied.
        void MovePosArgsToArgQueue(std::deque<std::string>& source);

        /// @brief Moves positional args from source to mArgQueue in reverse.
        ///
        /// Performs the same action as MovePosArgsToArgQueue() but in
        /// reverse order (arguments that populate MultiPosParam are moved out
        /// of the source queue into the internal argument queue, mArgQueue 
        /// first, followed by arguments that populate PosParam). Call this 
        /// function if mMultiPosParam has a MultiPosParam::ParsingOrder of 
        /// AfterOptions.
        /// 
        /// @param source The argument queue to move positional args from.
        /// @pre The elements of source queue were copied from mArgs.
        /// @pre The option arguments were moved out of source queue.
        /// @post The elementsof source are moved into mArgQueue.
        /// @post The source queue is emptied.
        void ReverseMovePosArgsToArgQueue(std::deque<std::string>& source);

        /// @brief Generates a label for usage info surrounded by brackets.
        ///
        /// A bracketed usage label is one surrounded by brackets which
        /// indicate whether the label is for a mandatory or optional 
        /// command line ArgParam.
        /// 
        /// @param p The ArgParam to generate a label for.
        /// @return A string representing the bracketed label.
        std::string GenerateBracketedUsageLabel(ArgParam* p) const;

        /// @brief Generates usage info without any help messages.
        /// 
        /// The full usage info includes both the usage and messages
        /// instructing the user how to see detailed help. This method simply
        /// generates the usage portion.
        /// 
        /// @return A string with the plain usage text.
        std::string GeneratePlainUsage() const;

        std::vector<std::string> mArgs;
        std::vector<ArgParam*> mArgParams;
        std::vector<Option*> mOptions;
        std::vector<PosParam*> mPosParams;
        std::deque<std::string> mArgQueue;
        MultiPosParam* mMultiPosParam;
        ProgParam* mProgParam;
        std::unique_ptr<Option> mBuiltInHelpOption;
    };
}

#endif
