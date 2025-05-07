// Validation.h - Declares functions for performing validation.
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

#ifndef CMD_LINE_VALIDATION_H
#define CMD_LINE_VALIDATION_H

#include <string>
#include "Constants.h"

namespace CmdLine
{
    /// @brief Checks the specified name to determine if it is valid.
    ///
    /// A valid non-option name is one with the following invariants:
    /// 
    /// 1. Name must be non-empty.
    /// 2. Name must contain only alpha numerics or - and _.
    /// 3. Name must not be longer than 20 characters.
    /// 4. Name must not start with an option prefix.
    /// 
    /// @param name The name to evaluate.
    /// @return True if the name is valid, otherwise false.
    bool IsValidNonOptionName(std::string name);
}

#endif