cmake_minimum_required(VERSION 3.5)
project(cpu-instructions)

SET(CMAKE_CXX_FLAGS "-pthread -mrtm -O3")

#add_definitions(-DVIRTUAL_FUNCTION_OPTIMIZATION)
#add_definitions(-DFORCE_SOFTWARE_TRANSACTION)

set(CMAKE_CXX_STANDARD 11)
#find_package(Threads REQUIRED)

# Used to generate lib when there are some cpp files.
#set(SOURCE_FILES
#        src/main.cc)

# Generate b_tree executable
add_executable(main src/main.cc)

