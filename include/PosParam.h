// PosParam.h - Declares the PosParam class.
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

#ifndef CMD_LINE_POS_PARAM_H
#define CMD_LINE_POS_PARAM_H

#include <string>
#include "ArgParam.h"
#include "Validation.h"
#include "Help.h"
#include "Option.h"

namespace CmdLine
{
    /// @brief A Positional command line ArgParam.
    /// 
    /// A PosParam is a command line ArgParam that is populated
    /// based on the position of the command line arguments. Exactly one 
    /// argument populates a PosParam by both specifying it and populating
    /// its value. By default, PosParams are populated after all Options have
    /// been parsed. However, if a MultiPosParam is also set on the Parser
    /// with a MultiPosParam::ParsingOrder of AfterOptions, then PosParams
    /// will be populated at the end. An example of when to use a PosParam is
    /// a copy program that has multiple source file paths and a single 
    /// desitination path. The single destination path would populate a 
    /// PosParam while the multile source paths would be captured by a 
    /// MultiPosParam.
    class PosParam : public ArgParam
    {
    public:
        /// @brief This definition is used to construct a PosParam.
        /// 
        /// A PosParam::Definition is passed to the constructor of a
        /// new PosParam to specify its attributes.
        struct Definition : public Param::Definition { };

        /// @brief Constructs a new PosParam.
        /// 
        /// @param d The definition to construct the PosParam with.
        /// @invariant Name must be non-empty.
        /// @invariant Name must contain only alpha numerics or - and _.
        /// @invariant Name must not be longer than 20 characters.
        /// @invariant Name must not start with an option prefix.
        /// @invariant Can only be specified upon successful population.
        /// @invariant Value can only be set upon successful population.
        /// @exception Param::InvalidDefinition Doesn't satisfy invariants.
        PosParam(Definition d);

        /// @brief Gets the value of the PosParam.
        ///
        /// The value of a PosParam always equals the argument that 
        /// populated it.
        /// 
        /// @return The value of the PosParam.
        std::string Value() const 
        { 
            return mValue; 
        }

        /// @brief Gets the name of the PosParam.
        ///
        /// The name of the PosParam is used for generating usage and
        /// help.
        /// 
        /// @return The name of the PosParam.
        virtual std::string Name() const override
        {
            return mDefinition.name;
        }

        /// @brief Gets the description of the PosParam.
        ///
        /// The description of the PosParam is used for generating help.
        ///
        /// @return The description of the PosParam.
        virtual std::string Description() const override
        {
            return mDefinition.description;
        }

        /// @brief Gets help info for the PosParam.
        ///
        /// The help info will include the name and description of the 
        /// PosParam when generating help.
        /// 
        /// @return Help info for the PosParam.
        virtual std::string HelpInfo() const override;

        /// @brief Indicates whether the PosParam has been specified.
        ///
        /// A PosParam will only indicate it was specified if it
        /// has been successfully populated by a command line argument.
        /// The Parser also uses this to determine if a mandatory
        /// PosParam has been specified.
        /// 
        /// @return True if the PosParam is specified, otherwise false.
        virtual bool IsSpecified() const override
        {
            return mIsSpecified;
        }

        /// @brief Indicates whether the PosParam is mandatory.
        ///
        /// The command line Parser uses this to determine if a PosParam
        /// must be specified at the command line for parsing to be successful.
        /// If a mandatory PosParam is not specified, parsing will fail 
        /// indicating the program was supplied with bad command line 
        /// arguments.
        /// 
        /// @return True if the PosParam is mandatory, otherwise false.
        virtual bool IsMandatory() const override
        {
            return mDefinition.isMandatory;
        }

        /// @brief Populates this PosParam from an argument queue.
        ///
        /// Accepts a reference to an argument queue (deque) and attempts to 
        /// populate the PosParam from the next argument in the
        /// queue. Populating the MultiPosParam marks it as specified and
        /// populates it with value from the command line argument. 
        /// Successful population also consumes the argument from the queue 
        /// that populated the PosParam.
        /// 
        /// @param args The arguments to populate the PosParam with.
        /// @return True if population is successful, otherwise false.
        /// @pre Size of arguments >= 1.
        /// @post The PosParam is marked specified.
        /// @post The the next argument in the argument queue is removed.
        /// @post The argument removed populates the the value.
        bool Populate(std::deque<std::string>& args) override;

        /// @brief Determines if arguments can populate this PosParam.
        ///
        /// Accepts a reference to an argument queue (deque) and determines if
        /// the next argument in the queue can populate the PosParam.
        /// 
        /// @param args The argument queue to evaluate.
        /// @return True if the arguments can populate, otherwise false.
        bool CanPopulate(const std::deque<std::string>& args) const override;

        /// @brief Gets the number of arguments the PosParam consumes.
        ///
        /// Each Positional consumes exactly 1 argument.
        /// 
        /// @param arguments The argument queue to evaluate.
        /// @return The number of arguments the PosParam will consume.
        std::size_t Consumes(const std::deque<std::string>& args) 
            const override 
        { 
            return 1; 
        }
    private:
        Definition mDefinition;
        std::string mValue;
        bool mIsSpecified;
    };
}

#endif

