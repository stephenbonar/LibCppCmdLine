// ArgParam.h - Declares the ArgParam base class.
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

#ifndef CMD_LINE_ARG_PARAM_H
#define CMD_LINE_ARG_PARAM_H

#include <string>
#include <deque>
#include "Param.h"

namespace CmdLine 
{
    /// @brief A parameter populated by command line arguments (base class).
    /// 
    /// An ArgParam is a variable that the CmdLine::Parser will populate 
    /// with data from one or more command line arguments. It provides methods
    /// for populating the parameter, as well as determining how many arguments
    /// population consumes and whether the next arguments in an argument queue
    /// (deque) can populate the parameter.
    class ArgParam : public Param
    {
    public:
        /// @brief Destructs an ArgParam.
        virtual ~ArgParam() = default;

        /// @brief Populates the ArgParam from an argument queue.
        ///
        /// Accepts a reference to an argument queue (deque) and attempts to 
        /// populate the ArgParam with data from the next n arguments in the
        /// queue, where n is the number of arguments the ArgParam
        /// consumes. Populating the ArgParam, at a minimum, marks
        /// it as specified and may also populate it with values
        /// (depending on the implementation). Successful population also
        /// consumes the arguments from the queue that populated the 
        /// ArgParam.
        /// 
        /// @param args The argument queue to populate from.
        /// @return True if population is successful, otherwise false.
        /// @pre Size of arguments > 0.
        /// @pre Size of arguments >= result of Consumes().
        /// @post The ArgParam is marked specified.
        /// @post Removes the number of arguments from the queue = Consumes().
        virtual bool Populate(std::deque<std::string>& args) = 0;

        /// @brief Determines if the specified args can populate the ArgParam.
        ///
        /// Accepts a reference to an argument queue (deque) and determines if
        /// the next n arguments in the queue can populate the ArgParam.
        /// 
        /// @param args The argument queue to evaluate.
        /// @return True if the arguments can populate, otherwise false.
        virtual bool CanPopulate(const std::deque<std::string>& args) 
            const = 0;

        /// @brief Gets the number of arguments the ArgParam consumes.
        ///
        /// Each ArgParam consumes a certain number of arguments from an 
        /// argument queue upon successful population. This number is
        /// implementation defined.
        /// 
        /// @param args The argument queue to evaluate.
        /// @return The number of arguments the ArgParam will consume.
        virtual std::size_t Consumes(const std::deque<std::string>& args)
            const = 0;
    };
}

#endif
