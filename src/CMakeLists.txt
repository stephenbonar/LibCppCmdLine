# CMakeLists.txt - Builds the LibCppCmdLine library.
#
# Copyright (C) 2024 Stephen Bonar
#
# Licensed under the Apache License, Version 2.0 (the "License");
# you may not use this file except in compliance with the License.
# You may obtain a copy of the License at
#
# http ://www.apache.org/licenses/LICENSE-2.0
# 
# Unless required by applicable law or agreed to in writing, software
# distributed under the License is distributed on an "AS IS" BASIS,
# WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
# See the License for the specific language governing permissionsand
# limitations under the License.

# cmake v3.12 is the minimum needed for the library.
cmake_minimum_required(VERSION 3.12)

# Configure the library build target.
add_library(LibCppCmdLine
            Constants.cpp
            Help.cpp
            MultiPosParam.cpp
            NameValuePair.cpp
            Option.cpp
            OptionParam.cpp
            Param.cpp
            Parser.cpp
            PosParam.cpp
            ProgParam.cpp
            Validation.cpp
            ValueOption.cpp)

# Override the default behavior of prefixing "lib" on the library binary so
# we end up with LibCppCmdLine.a isntead of libLibCppCmdLine.a.
set_target_properties(LibCppCmdLine PROPERTIES PREFIX "")

# Configure both the library itself and any other target that links with
# the library is able to resolve the library header files.
target_include_directories(LibCppCmdLine 
                           PUBLIC 
                           ${PROJECT_SOURCE_DIR}/include)
