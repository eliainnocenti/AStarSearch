# CMAKE

# cmake instructions

# cmake version
cmake_minimum_required(VERSION 3.26)

# project name
project(AStarSearch)

# c++ version
set(CMAKE_CXX_STANDARD 17)

# header files
set(HEADER_FILES Grid.h Cell.h GraphicInterface.h AStarSearch.h)

# source files
set(SOURCE_FILES Grid.cpp Cell.cpp GraphicInterface.cpp AStarSearch.cpp)

# creates a library with header files and source files
add_library(core ${HEADER_FILES} ${SOURCE_FILES})

# creates the AStarSearch project executable
add_executable(AStarSearch main.cpp)

# links the executable with the header files and source files
target_link_libraries(AStarSearch core)


# SFML graphics

# includes header directories for external libraries
include_directories(./graphics/lib/SFML-2.6.0)

# finds and include the required SFML 2.5 libraries
find_package(SFML 2.5 COMPONENTS system window graphics network audio REQUIRED) # do i need SFML 2.6?

# includes SFML library directories
include_directories(${SFML_INCLUDE_DIRS})

# links the SFML libraries to the AStarSearch executable
target_link_libraries(AStarSearch sfml-system sfml-window sfml-graphics sfml-network sfml-audio)


# TEST

# includes the test directory for unit testing with google test
add_subdirectory(test)