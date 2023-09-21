cmake_minimum_required(VERSION 3.26)

# project name
project(AStarSearch)

# c++ version
set(CMAKE_CXX_STANDARD 17)

set(HEADER_FILES PriorityQueue.h Grid.h Cell.h FrameOfReference.h)
set(SOURCE_FILES main.cpp Grid.cpp Cell.cpp)

add_executable(AStarSearch ${HEADER_FILES} ${SOURCE_FILES})

include_directories(/usr/local/include)

find_package(SFML 2.6 COMPONENTS system window graphics network audio REQUIRED)
include_directories(${SFML_INCLUDE_DIRS})
target_link_libraries(AStarSearch sfml-system sfml-window sfml-graphics sfml-network sfml-audio)