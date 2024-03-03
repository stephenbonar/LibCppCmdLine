// Option.h - Declares the Option class.
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

#ifndef CMD_LINE_OPTION_H
#define CMD_LINE_OPTION_H

#include <string>
#include <sstream>
#include <iomanip>
#include <stdexcept>
#include <locale>
#include "ArgParam.h"
#include "Help.h"
#include "Constants.h"
#include "Validation.h"

namespace CmdLine
{
    /// @brief An ArgParam that represents an Option.
    /// 
    /// A command line Option is an ArgParam that specifies an Option for the 
    /// program. This is the most simple type of Option since it simply 
    /// indicates whether it is specified when it is populated. Command line 
    /// arguments that populate and specify options begin with an Option prefix
    /// followed by a short name (single character) or long name (multiple 
    /// characters). What prefix is used depends on the Option::Style used 
    /// (Unix or Windows). For instance, some programs have an Option that
    /// tells the program to produce vebose output. With the Unix Option style,
    /// either -v or --verbose could be used to specify such an Option. With 
    /// the Windows Option style, either /v or /verbose could be used. 
    class Option : public ArgParam
    {
    public:
        /// @brief The style of the Option to use.
        /// 
        /// The style of Option determines the style of prefix used to
        /// specify and populate the Option at the command line. Unix
        /// style indicates that a - prefix should be used for short
        /// Option names and -- for long Option names. Windows style
        /// indicates that a / prefix should be used for both short
        /// and long name Options.
        enum class Style { Unix, Windows };

        /// @brief This Definition is used to construct an Option.
        /// 
        /// An Option::Definition is passed to the constructor of a
        /// new Option to specify its attributes.
        struct Definition
        {
            /// @brief The short name of the Option.
            ///
            /// The shortName of an Option is just a single character
            /// representing the Option. Depending on the Option::Style used,
            /// the Option will automatically add the appropreate prefix
            /// (- for Options with the Unix style and / for Options with the
            /// Windows style). If the shortName is 'p', an Option with the 
            /// Unix style will be specified by the "-p" argument at the 
            /// command line and an Option with the Windows style will be 
            /// specified by the "/p" argument.
            char shortName = 0;

            /// @brief The long name of the Option.
            ///
            /// The longName of an Option is a sequence of characters
            /// representing the Option. Depending on the Option::Style used,
            /// the Option will automatically add the appropreate prefix
            /// (-- for Options with the Unix style and / for Options with the
            /// Windows style). If the longName is "print", an Option with the 
            /// Unix style will be specified by the "--print" argument at the 
            /// CommandLine and an Option with the Windows style will be 
            /// specified by the "/print" argument.
            std::string longName;

            /// @brief The description of the Option.
            /// 
            /// @sa Option::Description().
            std::string description;

            /// @brief Determines whether the Option is mandatory.
            ///
            /// @sa Option::IsMandatory().
            bool isMandatory = false;

            /// @brief Determines the Option::Style of the option.
            ///
            /// @sa Option::Style.
            Style style = Style::Unix;
        };

        /// @brief Constructs a new Option.
        ///
        /// @param d The definition used to create the Option.
        /// @invariant Valid short names characters are alpha numerics and ?.
        /// @invariant Valid long name characters are alpha numerics, - and _.
        /// @invariant Long names must not start with the option prefix.
        /// @invariant Long names must not be longer than 20 characters.
        /// @invariant Options must not have both an empty short and long name.
        /// @invariant An option can only be specified by successful population.
        /// @exception Param::InvalidDefinition Doesn't satisfy invariants.
        Option(Definition d);

        /// @brief Gets the name of the Option.
        ///
        /// The name of the Option is used to determine if the Option is
        /// specified at the command line. It is also used by the Parser to
        /// prevent duplicate Options from being added to to it. Finally, the
        /// name is used to generate help info for the option. This name
        /// will always represent the prefixed short name of the Option unless
        /// the Option only has a long name, in which case this function will
        /// return the same value as the LongName() method.
        /// 
        /// @return The prefixed name of the Option.
        /// @sa LongName().
        std::string Name() const override;

        /// @brief Gets the description of the Option.
        ///
        /// The description of the Option is used for generating help.
        ///
        /// @return The description of the Option.
        std::string Description() const override
        {
            return mDefinition.description; 
        }

        /// @brief Gets help info for the Option.
        ///
        /// The help info will include names (short and / or long) and 
        /// description of the Option when generating help.
        /// 
        /// @return Help info for the Option.
        std::string HelpInfo() const override;

        /// @brief Indicates whether the Option has been specified.
        ///
        /// An Option will only indicate it was specified if the Option
        /// has been successfully populated by a command line argument. The 
        /// parser also uses this to determine if a mandatory Option has been
        /// specified.
        /// 
        /// @return True if the Option is specified, otherwise false.
        bool IsSpecified() const override
        {
            return mIsSpecified; 
        }

        /// @brief Indicates whether the Option is mandatory.
        ///
        /// The command line Parser uses this to determine if an Option must
        /// be specified at the command line for parsing to be successful. If
        /// a mandatory Option is not specified i.e. the correct command line
        /// argument necessary to populate the Option was not supplied,
        /// parsing will fail indicating the program was supplied with bad
        /// command line arguments.
        /// 
        /// @return True if the Option is mandatory, otherwise false.
        bool IsMandatory() const override 
        {
            return mDefinition.isMandatory; 
        }

        /// @brief Populates this Option from an argument queue.
        ///
        /// Accepts a reference to an argument queue (deque) and attempts to 
        /// populate the Option from the next argument in the queue. 
        /// Populating the Option marks it as specified. Successful population 
        /// also consumes the argument from the queue that populated the
        /// Option.
        /// 
        /// @param args The argument queue to populate the Option with.
        /// @return True if population is successful, otherwise false.
        /// @pre Size of arguments > 0.
        /// @pre Next argument must be Option's prefixed short or long name.
        /// @post Option is marked as specified.
        /// @post Next argument is removed from the queue.
        bool Populate(std::deque<std::string>& args) override;

        /// @brief Determines if arguments can populate this Option.
        ///
        /// Accepts a reference to an argument queue (deque) and determines if
        /// the next argument in the queue can populate the Option.
        /// 
        /// @param args The argument queue to evaluate.
        /// @return True if the arguments can populate, otherwise false.
        bool CanPopulate(const std::deque<std::string>& args) const override;

        /// @brief Gets the number of arguments the Option consumes.
        ///
        /// An Option should consume exactly 1 argument.
        /// 
        /// @param args The argument queue to evaluate.
        /// @return The number of arguments the Option will consume.
        std::size_t Consumes(const std::deque<std::string>& args) const 
            override
        {
            return 1; 
        }

        /// @brief Sets the Option::Style of the Option.
        ///
        /// Allows the program to change the Option::Style of the Option after
        /// it has been created. Alternatively, the Option::Style is set upon
        /// construction in the Option::Definition.
        /// 
        /// @param s The Option::Style to set
        void Set(Style s)
        {
            mDefinition.style = s;
        }

        /// @brief Gets the long name of the Option.
        ///
        /// The long name of the Option is used to determine if the Option is
        /// specified at the command line. It is also used by the Parser to
        /// prevent duplicate Options from being added to to it. Finally, the
        /// long name is used to generate help info for the Option. This name
        /// will always represent the prefixed long name of the option unless
        /// the option has no long name, in which case this function will
        /// return an empty string.
        /// 
        /// @return The prefixed long name of the Option.
        std::string LongName() const 
        {
            return PrefixLongName();
        }
    private:
        Definition mDefinition;
        bool mIsSpecified;

        /// @brief Generates a prefixed version of the short name.
        ///
        /// The prefix will be either a Unix or Windows option prefix depending
        /// on the Option::Style.
        /// 
        /// @return The prefixed version of the short name.
        std::string PrefixShortName() const;

        /// @brief Genereates a prefixed version of the long name.
        ///
        /// The prefix will be either a Unix or Windows option prefix depending
        /// on the Option::Style.
        /// 
        /// @return The prefixed version of the long name.
        std::string PrefixLongName() const;

        /// @brief Adds the specified prefix to the specified name.
        ///
        /// @param prefix The prefix to add to the name.
        /// @param name The name to add the prefix to.
        /// @return The prefixed name.
        std::string PrependPrefix(std::string prefix, std::string name) const;
    };

    /// @brief Determines if the specified argument represents an Option.
    ///
    /// A command line argument represents an Option if it begins with a valid
    /// Option prefix and a valid Option name. 
    /// 
    /// @param arg The argument to evaluate.
    /// @return True if the argument represents an Option, otherwise false.
    bool IsOption(std::string arg);
}

#endif
