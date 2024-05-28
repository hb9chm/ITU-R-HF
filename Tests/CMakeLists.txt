# Set the minimum required version of CMake
cmake_minimum_required(VERSION 3.10)

# Set the project name
project ("Tests")

#set language to C++
enable_language(CXX)

#set C++ version to 20
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# Download and build GoogleTest
include(FetchContent)
FetchContent_Declare(
    googletest
    GIT_REPOSITORY https://github.com/google/googletest.git
    GIT_TAG        v1.14.0
)

# Set the options for GoogleTest
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)

# Fetch GoogleTest
FetchContent_MakeAvailable(googletest)

include(googletest)

# Create an executable for the tests
add_executable(${PROJECT_NAME} tests.cpp)

# Link the GoogleTest library to the test executable
target_link_libraries(${PROJECT_NAME} gtest gtest_main)

message(STATUS "CXX Standard: ${CMAKE_CXX_STANDARD}")

# Enable testing
enable_testing()

# Add a test
gtest_add_tests(TARGET ${PROJECT_NAME})