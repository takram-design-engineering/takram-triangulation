#
#  CMakeLists.txt
#
#  MIT License
#
#  Copyright (C) 2014 Shota Matsuda
#  Copyright (C) 2014 takram design engineering
#
#  Permission is hereby granted, free of charge, to any person obtaining a
#  copy of this software and associated documentation files (the "Software"),
#  to deal in the Software without restriction, including without limitation
#  the rights to use, copy, modify, merge, publish, distribute, sublicense,
#  and/or sell copies of the Software, and to permit persons to whom the
#  Software is furnished to do so, subject to the following conditions:
#
#  The above copyright notice and this permission notice shall be included in
#  all copies or substantial portions of the Software.
#
#  THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
#  IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
#  FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL
#  THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
#  LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
#  FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER
#  DEALINGS IN THE SOFTWARE.
#

# Project settings
cmake_minimum_required(VERSION 2.8)
project(takram_triangulation CXX C)

# Configuration types
set(CMAKE_CONFIGURATION_TYPES "Debug;Release" CACHE STRING "configs" FORCE)
if (DEFINED CMAKE_BUILD_TYPE)
  set_property(CACHE CMAKE_BUILD_TYPE PROPERTY STRINGS
               ${CMAKE_CONFIGURATION_TYPES})
endif()

# Include directories
include_directories("${${PROJECT_NAME}_SOURCE_DIR}/src")
include_directories("${${PROJECT_NAME}_SOURCE_DIR}/include")
include_directories("${${PROJECT_NAME}_SOURCE_DIR}/lib")

# Compiler flags
set(TRIANGLE_FLAGS "-DTRILIBRARY=1 -DANSI_DECLARATORS=1 -DREAL=double")
set(CMAKE_C_FLAGS "-Wall ${TRIANGLE_FLAGS}")
set(CMAKE_C_FLAGS_DEBUG "-g -O0")
set(CMAKE_C_FLAGS_RELEASE "-Os -DNDEBUG")
set(CMAKE_CXX_FLAGS "-std=c++1y -stdlib=libc++ -Wall ${TRIANGLE_FLAGS}")
set(CMAKE_CXX_FLAGS_DEBUG "-g -O0")
set(CMAKE_CXX_FLAGS_RELEASE "-Os -DNDEBUG")
message(STATUS "")
message(STATUS "Configuration: "
        "${CMAKE_BUILD_TYPE}")
message(STATUS "C++ flags (Release): "
        "${CMAKE_CXX_FLAGS} ${CMAKE_CXX_FLAGS_RELEASE}")
message(STATUS "C++ flags (Debug): "
        "${CMAKE_CXX_FLAGS} ${CMAKE_CXX_FLAGS_DEBUG}")
message(STATUS "C flags (Release): "
        "${CMAKE_C_FLAGS} ${CMAKE_C_FLAGS_RELEASE}")
message(STATUS "C flags (Debug): "
        "${CMAKE_C_FLAGS} ${CMAKE_C_FLAGS_DEBUG}")
message(STATUS "")

# Library
file(GLOB_RECURSE SOURCES "src/*.cc" "src/*.c")
add_library("${PROJECT_NAME}" STATIC ${SOURCES})

# Unit test
file(GLOB_RECURSE TESTS "test/*.cc")
list(LENGTH TESTS TEST_COUNT)
if (TEST_COUNT)
  enable_testing()
  add_subdirectory("gtest")
  include_directories("gtest/include")
  add_executable("${PROJECT_NAME}_test" ${TESTS})
  target_link_libraries("${PROJECT_NAME}_test" "gtest" "gtest_main")
  target_link_libraries("${PROJECT_NAME}_test" "${PROJECT_NAME}")
  add_test("${PROJECT_NAME}" "${PROJECT_NAME}_test")
endif()

# Install settings
install(TARGETS "${PROJECT_NAME}" DESTINATION "lib")
install(DIRECTORY "src/" DESTINATION "src" FILES_MATCHING PATTERN "*.h")
install(DIRECTORY "include/" DESTINATION "include" FILES_MATCHING PATTERN "*.h")
