# CMakeLists.txt - Builds the LibCppCmd tests.
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

# We add GoogleTest to the project using FetchContent rather than a git
# submodule to avoid target conflicts if other modules of the project
# also use GoogleTest. As long as any other module also uses FetchContent,
# the GoogleTest targets shoudln't be duplicated.
include(FetchContent)
FetchContent_Declare(
    googletest
    URL https://github.com/google/googletest/archive/90a41521142c978131f38c6da07b4eb96a9f1ff6.zip
)

# For Windows: Prevent overriding the parent project's compiler/linker settings.
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)

# Make GoogleTest available at configuration time.
FetchContent_MakeAvailable(googletest)

# Configure the test executable build target.
add_executable(libcppcmdlinetests
               ExampleArguments.cpp
               ExampleHelp.cpp
               HelpTests.cpp
               MultiPosParamTests.cpp
               NameValuePairTests.cpp
               OptionParamTests.cpp
               OptionTests.cpp
               ParserTests.cpp
               PosParamTests.cpp
               ProgParamTests.cpp
               TestAlgorithms.cpp
               ValidationTests.cpp
               ValueOptionTests.cpp)

# Configure the include directories the executable target needs.
target_include_directories(libcppcmdlinetests 
                           PRIVATE 
                           ${PROJECT_SOURCE_DIR}/include)

# Configure the libraries the executable should link with.
target_link_libraries(libcppcmdlinetests 
                      PRIVATE
                      LibCppCmdLine
                      gtest
                      gtest_main
                      gmock)
