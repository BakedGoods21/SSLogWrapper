include(CMakeHelpers/GetExternalLibs.cmake)

cmake_minimum_required(VERSION 3.31)

project(
    SSLogWrapper
    VERSION 0.0.0
    LANGUAGES CXX
)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

option(BUILD_EXAMPLES "Build the examples as reference" OFF)

add_subdirectory(SSLogger)
    
if (BUILD_EXAMPLES)
    add_subdirectory(Examples)
endif()

