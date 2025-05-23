cmake_minimum_required(VERSION 3.10)
project(mini_git)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Include header files
include_directories(include)

# Collect all source files recursively
file(GLOB_RECURSE SOURCES "src/*.cpp" "main.cpp")

# Define the executable
add_executable(mini_git ${SOURCES})
