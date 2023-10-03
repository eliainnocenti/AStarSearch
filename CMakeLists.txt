# CMAKE

# cmake instructions for macos operating system

# cmake version
cmake_minimum_required(VERSION 3.26)

# project name
project(AStarSearch)

# c++ version
set(CMAKE_CXX_STANDARD 17)

# header files
set(HEADER_FILES PriorityQueue.h Grid.h Cell.h GraphicInterface.h)

# source files
set(SOURCE_FILES main.cpp Grid.cpp Cell.cpp GraphicInterface.cpp)

# create the AStarSearch project executable using the defined header and source files
add_executable(AStarSearch ${HEADER_FILES} ${SOURCE_FILES})


# SFML graphics

# include header directories for external libraries
include_directories(/usr/local/include)

# find and include the required SFML 2.5 libraries
find_package(SFML 2.5 COMPONENTS system window graphics network audio REQUIRED) # do i need SFML 2.6?

# include SFML library directories
include_directories(${SFML_INCLUDE_DIRS})

# link the SFML libraries to the AStarSearch executable
target_link_libraries(AStarSearch sfml-system sfml-window sfml-graphics sfml-network sfml-audio)

# the libraries are located in the following path: /opt/homebrew/Cellar/sfml/2.6.0