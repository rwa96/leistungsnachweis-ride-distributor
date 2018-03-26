cmake_minimum_required (VERSION 2.6)
project (RideDistributor)

# Compiler standart
set (CMAKE_CXX_STANDARD 17)
set (CMAKE_CXX_STANDARD_REQUIRED ON)
set (CMAKE_CXX_EXTENSIONS OFF)
if(MSVC)
    set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /std:c++17")
endif(MSVC)

# The version number.
set (RideDistributor_VERSION_MAJOR 0)
set (RideDistributor_VERSION_MINOR 1)

# Code location
add_subdirectory(src)
add_subdirectory(test)

#enable_testing()
#add_test (NAME MyTest COMMAND Test)
