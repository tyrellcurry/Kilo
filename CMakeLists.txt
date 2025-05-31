# Minimum required version of CMake
cmake_minimum_required(VERSION 3.10)

# Project name and version
project(Kilo VERSION 1.0)

# Set C standard
set(CMAKE_C_STANDARD 99)
set(CMAKE_C_STANDARD_REQUIRED ON)

# Add executable target
add_executable(Kilo
    kilo.c
)

# Include directories (for header files)
target_include_directories(Kilo PRIVATE .)

# Optional: Set compiler flags for debugging
set(CMAKE_C_FLAGS_DEBUG "-g -Wall -Wextra")

# Optional: Set build type to Debug by default
if(NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE Debug)
endif()
