# CMAKE

# cmake version
cmake_minimum_required(VERSION 3.26)

# project name
project(AStarSearch)

# c++ version
set(CMAKE_CXX_STANDARD 17)

# header files
set(HEADER_FILES PriorityQueue.h Grid.h Cell.h GraphicInterface.h FrameOfReference.h)

# source files
set(SOURCE_FILES main.cpp Grid.cpp Cell.cpp GraphicInterface.cpp)

# TODO - put some comments
add_executable(AStarSearch ${HEADER_FILES} ${SOURCE_FILES})

# TODO - put some comments
include_directories(/usr/local/include)

# TODO - put some comments
find_package(SFML 2.5 COMPONENTS system window graphics network audio REQUIRED) # do i need SFML 2.6?
include_directories(${SFML_INCLUDE_DIRS})
target_link_libraries(AStarSearch sfml-system sfml-window sfml-graphics sfml-network sfml-audio)