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

#
add_executable(AStarSearch ${HEADER_FILES} ${SOURCE_FILES})

#
include_directories(/usr/local/include)

#
find_package(SFML 2.5 COMPONENTS system window graphics network audio REQUIRED) # do i need SFML 2.6?
include_directories(${SFML_INCLUDE_DIRS})
target_link_libraries(AStarSearch sfml-system sfml-window sfml-graphics sfml-network sfml-audio)

#if (WIN32)
#    set(BUILD_SHARED_LIBS OFF)
#
#    # set SFML library
#    set(SFML_STATIC_LIBRARIES TRUE)
#    set(SFML_DIR SFML/lib/cmake/SFML)
#    find_package(SFML COMPONENTS system window graphics audio REQUIRED)
#    include_directories(SFML/include)

#    add_library(core Cell.cpp Cell.h Grid.cpp Grid.h UserInteraction.cpp UserInteraction.h)

#    target_link_libraries(core PUBLIC sfml-system sfml-window sfml-graphics sfml-audio)
#    set(CMAKE_EXE_LINKER_FLAGS "-static")

#    add_executable(AStarSearch main.cpp Grid.cpp Grid.h Cell.cpp Cell.h UserInteraction.cpp UserInteraction.h)
#    target_link_libraries(AStarSearch PUBLIC core)
#endif()