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
set(SOURCE_FILES main.cpp Grid.cpp Cell.cpp GraphicInterface.cpp AStarSearch.cpp)

# creates the AStarSearch project executable with header files and source files
add_executable(AStarSearch ${HEADER_FILES} ${SOURCE_FILES})


# SFML graphics

# FIXME: this is not working, the system accesses the SFML files from /opt/homebrew/include/SFML

# includes header directories for external libraries
#include_directories(./graphics/lib/SFML-2.6.0/include)
#include_directories(./graphics/lib/SFML-2.6.0)
#set(SFML_DIR ./graphics/lib/SFML-2.6.0/include)
set(SFML_INCLUDE_DIRS "/AStarSearch/graphics/lib/SFML-2.6.0/include")

# includes SFML library directories
include_directories(${SFML_INCLUDE_DIRS})

find_path(SFML_INCLUDE_DIRS "SFML/Graphics.hpp" PATHS "/AStarSearch/graphics/lib/SFML-2.6.0/include")

# finds and include the required SFML 2.6 libraries
find_package(SFML 2.6 COMPONENTS system window graphics network audio REQUIRED)

# links the SFML libraries to the AStarSearch executable
target_link_libraries(AStarSearch sfml-system sfml-window sfml-graphics sfml-network sfml-audio)


# TEST

# includes the test directory for unit testing with google test
add_subdirectory(test)