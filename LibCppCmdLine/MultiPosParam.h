// MultiPosParam.h - Declares the MultiPosParam class.
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

#ifndef CMD_LINE_MULTI_POS_PARAM_H
#define CMD_LINE_MULTI_POS_PARAM_H

#include <string>
#include <vector>
#include "Param.h"
#include "ArgParam.h"
#include "Option.h"
#include "Validation.h"
#include "Help.h"

namespace CmdLine
{
    /// @brief A multi-value PosParam.
    /// 
    /// A MultiPosParam is a multi-value PosParam that is populated by multiple
    /// command line arguments rather than a single argument. MultiPosParam
    /// arguments are parsed by the command line Parser either immediately
    /// after the last Option is parsed or after the last single-value PosParam
    /// is parsed, depending on what MultiPosParam::ParsingOrder the 
    /// MultiPosParam was created with. A MultiPosParam consumes a variable 
    /// number of arguments based on how many arguments are left in the parser 
    /// internal argument queue. Each argument consumed adds a single value to
    /// the values of the MultiPosParam. For example, a program that copies 
    /// files might accept mutiple source file arguments and a single 
    /// destination path argument. In this case, the program would use a 
    /// MultiPosParam to capture the source files.
    class MultiPosParam : public ArgParam
    {
    public:
        /// @brief Determines the MultiPosParam parsing order.
        ///
        /// The command line Parser will examine the parsing order of the 
        /// MultiPosParam to determine when it should be parsed.
        enum class ParsingOrder
        {
            /// @brief Parse the MultiPosParam at the very end.
            ///
            /// Instructs the command line Parser to parse the MultiPosParam
            /// at the end, after the last single-value PosParam has been 
            /// parsed. This is the default value.
            End,

            /// @brief Parse the MultiPosParam after the last Option.
            ///
            /// Instructs the command line Parser to parse the MultiPosParam
            /// immediately after the last Option has been parsed but before
            /// the first single-value PosParam.
            AfterOptions  
        };

        /// @brief This definition is used to construct a MutiPosParam.
        /// 
        /// A MultiPosParam::Definition is passed to the MultiPosParam
        /// constructor to create a new instance with the specified
        /// properties.
        struct Definition
        {
            /// @brief The name of the MultiPosParam.
            ///
            /// @sa Name().
            std::string name;

            /// @brief The description of the MultiPosParam.
            ///
            /// @sa Description().
            std::string description;

            /// @brief Determines if the MultiPosParam is mandatory.
            ///
            /// @sa IsMandatory().
            bool isMandatory = false;

            /// @brief Determines the MultiPosParam::ParsingOrder.
            ///
            /// @sa Order().
            ParsingOrder order = ParsingOrder::End;
        };

        /// @brief Constructs a new MultiPosParam.
        ///
        /// @param d The Definition used to create the MultiPosParam.
        /// @invariant Name must be non-empty.
        /// @invariant Name must contain only alpha numerics or - and _.
        /// @invariant Name must not be longer than 20 characters.
        /// @invariant Name must not start with an option prefix.
        /// @invariant Can only be specified upon successful population.
        /// @invariant Values can only be added upon successful population.
        /// @exception Param::InvalidDefinition Doesn't satisfy invariants.
        MultiPosParam(Definition d);

        /// @brief Gets the name of the MultiPosParam.
        ///
        /// The name of the MultiPosParam is used for generating usage and
        /// HelpInfo().
        /// 
        /// @return The name of the MultiPosParam.
        std::string Name() const override 
        { 
            return mDefinition.name; 
        }

        /// @brief Getst the description of the MultiPosParam.
        ///
        /// The description of the MultiPosParam is used for generating 
        /// HelpInfo().
        ///
        /// @return The description of the MultiPosParam.
        std::string Description() const override
        {
            return mDefinition.description;
        }

        /// @brief Gets help information for the MultiPosParam.
        ///
        /// The help info will include the Name() and Description() of the 
        /// MultiPosParam when generating help.
        /// 
        /// @return Help information for the MultiPosParam.
        std::string HelpInfo() const override;

        /// @brief Indicates whether the MultiPosParam has been specified.
        ///
        /// A MultiPosParam will only indicate it is specified if it
        /// has been successfully populated by command line arguments.
        /// The MultiPosParam must be populated by at least one argument to
        /// be specified. The command line Parser also uses this to determine 
        /// if a mandatory MultiPosParam has been specified.
        /// 
        /// @return True if the MultiPosParam is specified, otherwise false.
        bool IsSpecified() const override
        {
            return mIsSpecified;
        }

        /// @brief Indicates whether the MultiPosParam is mandatory.
        ///
        /// The command line Parser uses this to determine if a MultiPosParam
        /// must be specified at the command line for parsing to be successful.
        /// If a mandatory MultiPosParam is not specified, parsing will fail 
        /// indicating the program was supplied with bad command line 
        /// arguments.
        /// 
        /// @return True if the MultiPosParam is mandatory, otherwise false.
        bool IsMandatory() const override
        {
            return mDefinition.isMandatory;
        }

        /// @brief Populates the MultiPosParam from an argument queue.
        ///
        /// Accepts a reference to an argument queue (deque) and attempts to 
        /// populate the MultiPosParam from the remaining arguments in the
        /// queue. Populating the MultiPosParam marks it as specified and
        /// populates it with values from the command line arguments. 
        /// Successful population also consumes the remaining arguments in
        /// the queue.
        /// 
        /// @param args The arguments to populate the MultiPosParam.
        /// @return True if population is successful, otherwise false.
        /// @pre Size of arguments > 0.
        /// @pre All arguments are non-options.
        /// @post The MultiPosParam is marked specified.
        /// @post The argument queue, arguments, is emtpied.
        /// @post Consumed arguments are added to the MultiPosParam values.
        bool Populate(std::deque<std::string>& args) override;

        /// @brief Determines if arguments can populate this MultiPosParam.
        ///
        /// Accepts a reference to an argument queue (deque) and determines if
        /// all the arguments in the queue can populate the MultiPosParam.
        /// 
        /// @param args The argument queue to evaluate.
        /// @return True if the arguments can populate, otherwise false.
        bool CanPopulate(const std::deque<std::string>& args) const override;

        /// @brief Gets the number of arguments the MultiPosParam consumes.
        ///
        /// Each MultiPosParam consumes a certain number of arguments
        /// from an argument queue upon successful population. The number of
        /// arguments the MultiPosParam consumes is equal to the number of
        /// non-option arguments remaining in the queue.
        /// 
        /// @param args The argument queue to evaluate.
        /// @return The number of arguments the MultiPosParam will consume.
        std::size_t Consumes(const std::deque<std::string>& args) const 
            override;

        /// @brief Gets the values the MultiPosParam has been populated with.
        ///
        /// With MultiPosParams, each value corresponds to exactly one 
        /// command line argument and is populated in the order (position) of
        /// each argument.
        /// 
        /// @return The values the MultiPosParam was populated with.
        std::vector<std::string> Values() const 
        { 
            return mValues; 
        }

        /// @brief Gets the ParsingOrder of the MultiPosParam. 
        ///
        /// The ParsingOrder determines whether a command line
        /// MultiPosParam is parsed imediately after the the last Option
        /// or at the end when the last single-value PosParam has been 
        /// parsed.
        /// 
        /// @return The ParsingOrder of the MultiPosParam.
        ParsingOrder Order() const
        { 
            return mDefinition.order; 
        }
    private:
        Definition mDefinition;
        bool mIsSpecified;
        std::vector<std::string> mValues;
        ParsingOrder mOrder;
    };
}

#endif
