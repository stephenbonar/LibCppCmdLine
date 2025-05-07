// NameValuePair.h - Declares the NameValuePair class
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

#ifndef CMD_LINE_NAME_VALUE_PAIR_H
#define CMD_LINE_NAME_VALUE_PAIR_H

#include <string>
#include <stdexcept>
#include <sstream>
#include "Constants.h"
#include "Validation.h"

namespace CmdLine
{
    /// @brief A pair of a name and a value.
    /// 
    /// A name-value pair specified in a CommandLine argument takes the
    /// form "name=value". This class separates the name and the value
    /// and stores them as a single pair with the name and value
    /// individually retrievable. A valid name without a value (i.e. "name"
    /// vs. "name=value") can also represent a name-value pair. In this case
    /// the resulting NameValuePair will have an empty value.
    class NameValuePair
    {
    public:
        /// @brief An exception thrown for invalid NameValuePairs.
        /// 
        /// This exception is thrown by the NameValuePair constructor when the
        /// string used to construct the NameValuePair fails to satisfy
        /// the NameValuePair invariants.
        class InvalidPair : public std::invalid_argument
        {
        public:
            /// @brief Constructs an InvalidPair exception.
            ///
            /// @param message The message to include with the exception.
            InvalidPair(const char* message);
        };

        /// @brief Constructs a new NameValuePair.
        ///
        /// @param pair The string used to construct the pair.
        /// @invariant Name characters must be alpha numerics and - and _.
        /// @invariant Names must not start with the option prefix.
        /// @invariant Names must not be longer than 20 characters.
        /// @invariant The name must not be empty.
        /// @invariant The value will consist of everything after the = sign.
        NameValuePair(std::string pair);

        /// @brief Gets the name from the NameValuePair.
        ///
        /// @return The name from the NameValuePair.
        std::string Name() const { return mName; }

        /// @brief Gets the value from the NameValuePair.
        ///
        /// @return The value from the NameValuePair.
        std::string Value() const { return mValue; }
    private:
        std::string mName;
        std::string mValue;
    };

    /// @brief Determines if the specified string represents a NameValuePair.
    ///
    /// A valid NameValuePair is a non-empty string that, at a minimum,
    /// is comprised of a valid non-option name.
    /// 
    /// @param pair The string to evaluate.
    /// @return True if the string is a name-value pair, otherwise false.
    bool IsNameValuePair(std::string pair);
}

#endif

