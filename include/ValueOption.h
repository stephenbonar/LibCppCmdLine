// ValueOption.h - Declares the ValueOption class.
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

#ifndef CMD_LINE_VALUE_OPTION_H
#define CMD_LINE_VALUE_OPTION_H

#include <vector>
#include <string>
#include <memory>
#include <algorithm>
#include "Option.h"
#include "OptionParam.h"

namespace CmdLine
{
    /// @brief A command line Option that is populated with values.
    /// 
    /// A command line ValueOption is an ArgParam that not only 
    /// specifies an Option for the program but also captures one or more 
    /// values associated with that option. Command line arguments that
    /// populate and specify Options begin with an Option prefix followed by a
    /// short name (single character) or long name (multiple characters). What
    /// prefix is used depends on the Option::Style used (Unix or Windows). For
    /// instance, a media program might have an Option that prints song 
    /// metadata. Wit the Unix Option style, either "-p" or "--print" could be
    /// used to specify such an Option. With the Windows Option::Style, either
    /// "/p" or "/print" could be used. Using that same example, to print the 
    /// album of a song using a hypothetical "--print" Option, one might 
    /// specify "--print album" at the command line. In this case, not only 
    /// would the "--print" Option be specified, but it would be populated with
    /// the value "album". Assuming there was a specific list of possible 
    /// values for "--print", ValueOption supports adding OptionParams 
    /// which are specified by a specific Option value. For instance, one might
    /// add OptionParams for "song", "album", "artist", etc. For an Option 
    /// that sets such a value, you could have an "--edit" option. For example,
    /// "--edit 'artist=The Beatles'". In this case the value is a 
    /// NameValuePair and an "artist" OptionParam could extract the value
    /// from the pair. Finally, a ValueOption may be specified multiple times
    /// to populate it with multiple values.
    class ValueOption : public Option
    {
    public:
        /// @brief This definition is used to construct a ValueOption.
        /// 
        /// A ValueOption::Definition is passed to the constructor of a
        /// new ValueOption to specify its attributes.
        struct Definition : public Option::Definition { };

        /// @brief An exception thrown for adding duplicate OptionParams.
        /// 
        /// This exception is thrown when the programmer attempts to add
        /// a duplicate OptionParam to the ValueOption. 
        class DuplicateOptionParam : public std::invalid_argument
        {
        public:
            /// @brief Constructs an DuplicateOptionParam exception.
            ///
            /// @param message The message to include with the exception.
            DuplicateOptionParam(const char* message);
        };

        /// @brief An exception thrown for adding null OptionParam.
        /// 
        /// This exception is thrown when the programmer attempts to add
        /// a null OptionParam to the ValueOption. 
        class NullOptionParam : public std::invalid_argument
        {
        public:
            /// @brief Constructs an NullOptionParam exception.
            ///
            /// @param message The message to include with the exception.
            NullOptionParam(const char* message);
        };

        /// @brief Constructs a new ValueOption
        /// 
        /// @param d The definition used to create the Option.
        /// @invariant Valid short names characters are alpha numerics and ?.
        /// @invariant Valid long name characters are alpha numerics, - and _.
        /// @invariant Long names must not start with the option prefix.
        /// @invariant Long names must not be longer than 20 characters.
        /// @invariant Options must not have both an empty short and long name.
        /// @invariant An option can only be specified by successful population.
        /// @invariant By extension, so are OptionParams and values.
        /// @invariant Must not have duplicate OptionParams.
        /// @exception Param::InvalidDefinition Doesn't satisfy invariants.
        ValueOption(Definition d);

        /// @brief Populates this ValueOption from an argument queue.
        ///
        /// Accepts a reference to an argument queue (deque) and attempts to 
        /// populate the ValueOption from the next two arguments in the queue.
        /// Populating the ValueOption marks it as specified. Successful
        /// population also consumes the two arguments from the queue that 
        /// populated the ValueOption.
        /// 
        /// @param args The argument queue to populate the Option with.
        /// @return True if population is successful, otherwise false.
        /// @pre Size of arguments >= 2
        /// @post The ValueOption is marked specified.
        /// @post The next two arguments are removed from the queue.
        /// @post Consumed arguments are added to the ValueOption values.
        bool Populate(std::deque<std::string>& args) override;

        /// @brief Determines if arguments can populate this ValueOption.
        ///
        /// Accepts a reference to an argument queue (deque) and determines if
        /// the next two arguments in the queue can populate the ValueOption.
        /// 
        /// @param args The arguments queue to evaluate.
        /// @return True if the arguments can populate, otherwise false.
        bool CanPopulate(const std::deque<std::string>& args) const override;

        /// @brief Gets the number of arguments the ValueOption consumes.
        ///
        /// A ValueOption should consume exatly 2 arguments.
        /// 
        /// @param args The argument queue to evaluate.
        /// @return The number of arguments the Option will consume.
        std::size_t Consumes(const std::deque<std::string>& args) 
            const override
        {
            return 2;
        }

        /// @brief Gets help info for the ValueOption.
        ///
        /// The help info will include names (short and / or long) and 
        /// description of the Option when generating help. It will also
        /// include the help info of any OptionParams that were
        /// added to the ValueOption.
        /// 
        /// @return Help info for the ValueOption.
        std::string HelpInfo() const override;

        /// @brief Gets the values the ValueOption is populated with.
        ///
        /// ValueOptions are populated with the command line argument that is
        /// passed to the ValueOtion by the user. This argument can either be a
        /// single value or a NameValuePair.
        /// 
        /// @return The values the ValueOption is populated with.
        std::vector<std::string> Values() const { return mValues; }

        /// @brief Adds the specified OptionParam to the ValueOption.
        ///
        /// Each OptionParam pointer added to the ValueOption can be 
        /// populated by a ValueOption value (or name-value pair) that matches 
        /// the OptionParam's name. Adding OptionParams to the 
        /// ValueOption can be a way of constraining the ValueOption to a list 
        /// of possible values that will indicate whether or not they were 
        /// specified. 
        /// 
        /// @param p The OptionParam pointer to add
        /// @return True if the add operation was successful, otherwise false.
        /// @pre The OptionParam pointer must not be null.
        /// @pre A duplicate OptionParam must not have already been added.
        /// @post The OptionParam is added to the ValueOption.
        /// @exception DuplicateOptionParam Tried to add duplicate OptionParam.
        void Add(OptionParam* p);
    private:
        std::vector<std::string> mValues;
        std::vector<OptionParam*> mParams;
    };
}

#endif
