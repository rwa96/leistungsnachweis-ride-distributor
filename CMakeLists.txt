cmake_minimum_required (VERSION 3.8)
project (RideDistributor)

# The project version number.
set(VERSION_MAJOR 0)
set(VERSION_MINOR 0)
set(VERSION_PATCH 1)
mark_as_advanced(VERSION_MAJOR VERSION_MINOR VERSION_PATCH)

# Compiler standart
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# Windows stuff
if(MSVC)
    set(CMAKE_CXX_FLAGS ${CMAKE_CXX_FLAGS} "/std:c++17")
endif(MSVC)

# Unit tests
enable_testing()

# Code location
add_subdirectory(src)
add_subdirectory(test)
add_subdirectory(docs)
