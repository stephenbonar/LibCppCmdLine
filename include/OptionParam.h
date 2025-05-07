// OptionParam.h - Declare the OptionParam class.
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

#ifndef CMD_LINE_OPTION_PARAM_H
#define CMD_LINE_OPTION_PARAM_H

#include <string>
#include "Param.h"
#include "NameValuePair.h"
#include "Help.h"

namespace CmdLine
{
    /// @brief Provides parameters for ValueOption values.
    /// 
    /// An OptionParam provides a way for a program to capture specific
    /// values passed to a ValueOption. OptionParams can be added to 
    /// ValueOptions for this purpose. This is useful for ValueOptions that
    /// have a specific list of possible values when the program needs to
    /// check that one or more of those possible values was specified. The
    /// name of the OptionParam defines the possible Option value.
    /// If the value passed to the ValueOption at the command line is a
    /// NameValuePair, the the OptionParam will not only indicate that
    /// the name was specified as a possible value, it will also have its own
    /// value (the value of the NameValuePair). For example, assume a
    /// ValueOption "--print" instructs a program to print metadata values for
    /// a song. Assume the possible values for the "--print" ValueOption are
    /// "song", "artist", and "album". In this case you would add three 
    /// OptionParams to the "--print" ValueOption. Assume then that the 
    /// user specifies "--print song" at the command line. The OptionParam
    /// "song" would be specified but have no value of its own. Now assume the 
    /// same program has an "--edit" ValueOption to change those same metadata
    /// properties. If the users specified "--edit 'song=Happy Birthday'", the
    /// "song" OptionParam would be specified and have the value 
    /// "Happy Birthday".
    class OptionParam : public Param
    {
    public:
        /// @brief This definition is used to construct an OptionParam.
        /// 
        /// An OptionParam::Definition is passed to the constructor of a
        /// new OptionParam to specify its attributes.
        struct Definition : public Param::Definition { };

        /// @brief Constructs a new OptionParam.
        ///
        /// @param definition The definition to construct the OptionParam.
        /// @invariant Name must be non-empty.
        /// @invariant Name must contain only alpha numerics or - and _.
        /// @invariant Name must not be longer than 20 characters.
        /// @invariant Name must not start with an option prefix.
        /// @invariant Value is only set by successful population.
        /// @invariant Can only be specified upon successful population.
        /// @exception Parame:InvalidDefinition Doesn't satisfy invariants.
        OptionParam(Definition definition);

        /// @brief Gets the name of the OptionParam.
        ///
        /// The name of the OptionParam is used for generating usage and
        /// help.
        /// 
        /// @return The name of the OptionParam.
        std::string Name() const override
        { 
            return mDefinition.name;
        }

        /// @brief Getst the description of the OptionParam.
        ///
        /// The description of the OptionParam is used for generating help.
        ///
        /// @return The description of the OptionParam.
        std::string Description() const override 
        { 
            return mDefinition.description; 
        }

        /// @brief Gets help info for the OptionParam.
        ///
        /// The help info will include the name and description of the 
        /// OptionParam when generating help.
        /// 
        /// @return Help info for the OptionParam.
        std::string HelpInfo() const override;

        /// @brief Indicates whether the OptionParam has been specified.
        ///
        /// An OptionParam will only indicate it was specified if the 
        /// OptionParam has been successfully populated by an OptionValue.
        /// The Parser also uses this to determine if a mandatory OptionParam
        /// has been specified.
        /// 
        /// @return True if the parameter is specified, otherwise false.
        bool IsSpecified() const override
        {
            return mIsSpecified;
        }

        /// @brief Indicates whether the OptionParam is mandatory.
        ///
        /// The command line Parser uses this to determine if an OptionParam
        /// must be specified at the command line for parsing to be successful.
        /// If a mandatory OptionParam is not specified, parsing will fail 
        /// indicating the program was supplied with bad command line 
        /// arguments.
        /// 
        /// @return True if the OptionParam is mandatory, otherwise false.
        bool IsMandatory() const override 
        { 
            return mDefinition.isMandatory;
        }

        /// @brief Gets the value the OptionParam was populated with.
        ///
        /// The value of an OptionParam is the value of a NameValuePair
        /// passed to the ValueOption at the command line. If just a name was
        /// passed, the value will be an empty string.
        /// 
        /// @return The value of the OptionParam.
        std::string Value() const 
        { 
            return mValue;
        }

        /// @brief Populates the OptionParam from a NameValuePair.
        ///
        /// An OptionParam is populated from a NameValuePair that 
        /// represents an argument (value) that was passed to the ValueOption
        /// at the command line. If the NameValuePair itself does not specifiy
        /// a value, population will only mark the OptionParam as specified,
        /// otherwise it will both specify the OptionParam and populate its 
        /// value.
        /// 
        /// @param p The NameValuePair to populate the OptionParam with.
        /// @return True if population was successful, otherwise false.
        /// @pre The pair's name must match the OptionParam's name.
        /// @post The OptionParam is marked as specified.
        /// @post If there was a value, the value will be set.
        bool Populate(NameValuePair p);

        /// @brief Checks if the NameValuePair can populate OptionParam
        ///
        /// @param p The NameValuePair to evaluate.
        /// @return True if it can populate, otherwise false.
        bool CanPopulate(NameValuePair p) const;
    private:
        Definition mDefinition;
        std::string mValue;
        bool mIsSpecified;
    };
}

#endif
