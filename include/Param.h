// Param.h - Declares the Param base class.
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

#ifndef CMD_LINE_PARAM_H
#define CMD_LINE_PARAM_H

#include <string>
#include <deque>
#include <stdexcept>

namespace CmdLine
{
    /// @brief A parameter that stores data from the command line (base class).
    /// 
    /// A command line Param is a variable that stores data specified at the 
    /// command line. How this is achieved is defined by the implemntation of
    /// each class that inherits from this one. This base class declares the 
    /// the minimum attributes all types of Param are expected  to have: a 
    /// name, description, help information to print on help and usage screens,
    /// whether the Param was specified at the command line, and whether the 
    /// Param is mandatory.
    class Param
    {
    public:
        /// @brief Defines a command line Param.
        /// 
        /// All classes that inherit from Param can use this struct (or 
        /// a descendant of it) to construct a new Param.
        struct Definition
        {
            /// @brief The name of the Param.
            ///
            /// @sa Name().
            std::string name;

            /// @brief The description of the Param.
            ///
            /// @sa Description().
            std::string description;

            /// @brief Determines if the Param is mandatory.
            ///
            /// @sa IsMandatory().
            bool isMandatory = false;
        };

        /// @brief An exception thrown for invalid Param definitions.
        /// 
        /// An invalid command line Param::Definition is a definition that
        /// fails to satisfy the invariants for a Param. For instance,
        /// a blank name should cause a Param constructor to throw this
        /// exception.
        class InvalidDefinition : public std::invalid_argument
        {
        public:
            /// @brief Constructs an InvalidDefinition exception.
            ///
            /// @param message The message to include with the exception.
            InvalidDefinition(const char* message);
        };

        /// @brief Destructs a Param.
        virtual ~Param() = default;

        /// @brief Gets the name of the Param.
        ///
        /// The name of the Param is used for generating usage and
        /// help.
        /// 
        /// @return The name of the Param.
        virtual std::string Name() const = 0;

        /// @brief Getst the description of the Param.
        ///
        /// The description of the Param is used for generating help.
        ///
        /// @return The description of the Param.
        virtual std::string Description() const = 0;

        /// @brief Gets help info for the Param.
        ///
        /// The help info will include the name and description of the 
        /// Param when generating help.
        /// 
        /// @return Help info for the Param.
        virtual std::string HelpInfo() const = 0;

        /// @brief Indicates whether the Param has been specified.
        ///
        /// A Param will only indicate it was specified if the it
        /// has been successfully populated by data from a command line
        /// argument. This is particularly useful to determine if a particular
        /// command line Option (also a type of Param) has been specified
        /// at the command line, etc. The comand line Parser also uses this to 
        /// determine if a mandatory parameter has been specified.
        /// 
        /// @return True if the Param is specified, otherwise false.
        virtual bool IsSpecified() const = 0;

        /// @brief Indicates whether the Param is mandatory.
        ///
        /// The command line Parser uses this to determine if a Param must
        /// be specified at the command line for parsing to be successful. If
        /// a mandatory Param is not specified i.e. the correct command
        /// line argument necessary to populate the Param was not supplied,
        /// parsing will fail indicating the program was supplied with bad
        /// command line arguments.
        /// 
        /// @return True if the Param is mandatory, otherwise false.
        virtual bool IsMandatory() const = 0;
    };
}

#endif
