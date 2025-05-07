// Help.h - Declares functions for generating help content.
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

#ifndef CMD_LINE_HELP_H
#define CMD_LINE_HELP_H

#include <string>
#include <sstream>
#include <iomanip>
#include "Constants.h"

namespace CmdLine
{
    /// @brief Generates a formatted line of help information.
    ///
    /// Accepts a Param name and description and indents both in a uniform way.
    /// This ensures each Param can have its name and description output in 
    /// alignment with each other.
    /// 
    /// @param name The name of the Param.
    /// @param description The description of the Param.
    /// @return The formatted help line.
    std::string GenerateHelpLine(std::string name, std::string description);
}

#endif
