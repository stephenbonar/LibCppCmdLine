// ProgParam.h - Declares the ProgParam class.
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

#ifndef CMD_LINE_PROG_PARAM_H
#define CMD_LINE_PROG_PARAM_H

#include <string>
#include <deque>
#include <stdexcept>
#include "ArgParam.h"

namespace CmdLine
{
    /// @brief A command line ArgParam populated by the program name.
    /// 
    /// A ProgramParameter is a CommandLine ArgumentParameter that is
    /// populated by the program name argument, which is the first CommandLine
    /// argument the OS passes to the program by convention. Upon successful
    /// population, the ProgramParameter's value will be populated by the
    /// program name argument, which will also mark the ProgramParameter as
    /// specified. Even if the value of the program argument is not important
    /// to the program, the ProgramParameter's name is still used to represent
    /// the program when the parser generates help and usage info.
    class ProgParam : public ArgParam
    {
    public:
        /// @brief This definition is used to construct a ProgParam.
        /// 
        /// A ProgParam definition is passed to the constructor of a
        /// new ProgParam to specify its attributes.
        struct Definition : public Param::Definition { };

        /// @brief Constructs a new ProgParam.
        ///
        /// @param d The definition to construct the ProgParam with.
        /// @invariant Name must be non-empty.
        /// @invariant Can only be specified upon successful population.
        /// @invariant Value can only be set upon successful population.
        /// @exception Param::InvalidDefinition Doesn't satisfy invariants.
        ProgParam(Definition d);

        /// @brief Gets the name of the ProgParam.
        ///
        /// The name of the ProgParam is used for generating usage and
        /// help.
        /// 
        /// @return The name of the ProgParam.
        std::string Name() const override 
        {
            return mDefinition.name;
        }

        /// @brief Gets the description of the ProgParam.
        ///
        /// The description of the ProgParam is used for generating 
        /// help.
        ///
        /// @return The description of the ProgParam.
        std::string Description() const override 
        { 
            return mDefinition.description;
        }

        /// @brief Indicates whether the ProgParam has been specified.
        ///
        /// A ProgParam will only indicate it was specified if the 
        /// parameter has been successfully populated by the program name 
        /// command line argument. The Parser also uses this to determine
        /// if a mandatory ProgParam has been specified.
        /// 
        /// @return True if the ProgParam is specified, otherwise false.
        bool IsSpecified() const override 
        { 
            return mIsSpecified;
        }

        /// @brief Indicates whether the ProgParam is mandatory.
        ///
        /// The command line Parser uses this to determine if the
        /// program name argument must be specified at the command line for 
        /// parsing to be successful. If a mandatory ProgParam is not 
        /// specified i.e. the correct command line argument necessary to 
        /// populate the ProgParam was not supplied, parsing will fail
        /// indicating the program was supplied with bad command line arguments.
        /// 
        /// @return True if the ProgParam is mandatory, otherwise false.
        bool IsMandatory() const override 
        { 
            return mDefinition.isMandatory;
        }

        /// @brief Gets help info for the ProgParam.
        ///
        /// The help info will include the name and description of the 
        /// ProgParam when generating help.
        /// 
        /// @return Help info for the ProgParam.
        std::string HelpInfo() const override 
        {
            return "  " + mDefinition.description;
        }

        /// @brief Populates this ProgParam from an argument queue.
        ///
        /// Accepts a reference to an argument queue (deque) and attempts to 
        /// populate the ProgParam from the first argument in the
        /// queue. Populating the ProgParam marks it as specified and 
        /// will also populate the ProgParam value with the argument. 
        /// Successful population also consumes the argument from the queue 
        /// that populated the argument.
        /// 
        /// @param args The argument queue to populate the parameter with.
        /// @return True if population is successful, otherwise false.
        /// @pre Size of arguments >= 1.
        /// @post The ProgParam is marked specified.
        /// @post The the next argument in the argument queue is removed.
        /// @post The argument removed populates the the value.
        bool Populate(std::deque<std::string>& args) override;

        /// @brief Determines if arguments can populate this ProgParam.
        ///
        /// Accepts a reference to an argument queue (deque) and determines if
        /// the first argument in the queue can populate the ProgParam.
        /// 
        /// @param arguments The argument queue to evaluate.
        /// @return True if the arguments can populate, otherwise false.
        bool CanPopulate(const std::deque<std::string>& args) const override;

        /// @brief Gets the number of arguments the ProgParam consumes.
        ///
        /// Each ProgParam consumes exactly 1 argument from the argument
        /// queue upon successful population. 
        /// 
        /// @param arguments The argument queue to evaluate.
        /// @return The number of arguments the parameter will consume.
        std::size_t Consumes(const std::deque<std::string>& args) 
            const override 
        {
            return 1;
        }

        /// @brief Gets the value of the ProgParam.
        ///
        /// The value of the ProgParam will be the same as the first
        /// command line argument, which by convention is the program name
        /// most operating systems pass to the program by convention. 
        /// 
        /// @return The value of the ProgParam.
        std::string Value() const 
        { 
            return mValue;
        }
    private:
        Definition mDefinition;
        bool mIsSpecified;
        std::string mValue;
    };
}

#endif

