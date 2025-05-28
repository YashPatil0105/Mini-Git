# # cmake_minimum_required(VERSION 3.10)
# # project(mini_git)

# # # set(CMAKE_CXX_STANDARD 17)
# # # set(CMAKE_CXX_STANDARD_REQUIRED ON)

# # # # Include header files
# # # include_directories(include)

# # # # Collect all source files recursively
# # # file(GLOB_RECURSE SOURCES "src/*.cpp" "main.cpp")

# # # # Define the executable
# # # add_executable(mini_git ${SOURCES})

# cmake_minimum_required(VERSION 3.10)
# project(mini_git)

# set(CMAKE_CXX_STANDARD 17)
# set(CMAKE_CXX_STANDARD_REQUIRED ON)

# # # Include directories
# # include_directories(include)

# # # Gather source files from src directory
# # file(GLOB_RECURSE SOURCES "src/*.cpp")

# # # Create static library from core source
# # add_library(mini_git_lib STATIC ${SOURCES})

# # # Main executable
# # add_executable(mini_git main.cpp)
# # target_link_libraries(mini_git mini_git_lib)

# # # Gather test files
# # file(GLOB TEST_FILES "test/*.cpp")

# # # Create executables for each test file
# # foreach(TEST_FILE ${TEST_FILES})
# #     get_filename_component(TEST_NAME ${TEST_FILE} NAME_WE)
# #     add_executable(${TEST_NAME} ${TEST_FILE})
# #     target_include_directories(${TEST_NAME} PRIVATE include)
# #     target_link_libraries(${TEST_NAME} mini_git_lib)
# #     set_target_properties(${TEST_NAME} PROPERTIES WIN32_EXECUTABLE FALSE)
# # endforeach()

cmake_minimum_required(VERSION 3.10)
project(mini_git)

# Set output directories
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR})
set(CMAKE_TEST_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR})

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Include directories
include_directories(include)

# Add GoogleTest
include(FetchContent)
FetchContent_Declare(
    googletest
    GIT_REPOSITORY https://github.com/google/googletest.git
    GIT_TAG release-1.12.1
)
FetchContent_MakeAvailable(googletest)

# Gather source files from src directory
file(GLOB_RECURSE SOURCES "src/*.cpp")

# Create static library from core source
add_library(mini_git_lib STATIC ${SOURCES})

# Main executable target name (no hyphen)
add_executable(mini_git main.cpp)
target_link_libraries(mini_git mini_git_lib)

# Set output executable filename to 'mini-git' with hyphen
set_target_properties(mini_git PROPERTIES OUTPUT_NAME "mini-git")

# Test executable
add_executable(mini_git_tests
    test/test_blob.cpp
    test/test_tree.cpp
    test/test_commit.cpp
    test/test_diff.cpp
)

target_link_libraries(mini_git_tests
    mini_git_lib
    GTest::gtest_main
)

# Set test output directory
set_target_properties(mini_git_tests PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}
    RUNTIME_OUTPUT_DIRECTORY_DEBUG ${CMAKE_SOURCE_DIR}
    RUNTIME_OUTPUT_DIRECTORY_RELEASE ${CMAKE_SOURCE_DIR}
)

# Enable testing
enable_testing()

# Add test with full path
add_test(
    NAME mini_git_tests
    COMMAND ${CMAKE_SOURCE_DIR}/mini_git_tests
    WORKING_DIRECTORY ${CMAKE_SOURCE_DIR}
)

# Add 'make clean' support
add_custom_target(clean-all
    COMMAND ${CMAKE_COMMAND} -P cmake_clean.cmake
    COMMAND ${CMAKE_COMMAND} --build . --target clean
    COMMENT "Cleaning all build files..."
)
