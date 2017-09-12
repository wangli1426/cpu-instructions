cmake_minimum_required(VERSION 3.5)
project(cpu-instructions)

SET(CMAKE_CXX_FLAGS "-O3")
SET(CMAKE_CXX_FLAGS "-g")
SET(CMAKE_CXX_FLAGS "-mrtm")

#add_definitions(-DVIRTUAL_FUNCTION_OPTIMIZATION)

set(CMAKE_CXX_STANDARD 11)
find_package(Threads REQUIRED)

# Used to generate lib when there are some cpp files.
set(SOURCE_FILES
        src/main.cc)

# Generate b_tree executable
add_executable(main src/main.cc src/rtm.h include/tsx-cpuid.h)

