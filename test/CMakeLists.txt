# CMAKE

# cmake instructions for unit testing with google test

# cmake version
cmake_minimum_required(VERSION 3.26)

# adds the subdirectory containing Google Test
add_subdirectory(./lib/googletest-main)

# sets the gtest_SOURCE_DIR variable with the path to the Google Test directory
set(gtest_SOURCE_DIR, ./lib/googletest-main/)

# specifies the include directories for Google Test
include_directories(${gtest_SOURCE_DIR}/include ${gtest_SOURCE_DIR})

# list of test files to include in the test executable
set(SOURCE_TEST_FILES runAllTest.cpp GridTest.cpp CellTest.cpp AStarSearchTest.cpp)

# sets a list of source files for the 'core' library, specifying their relative paths
set(SOURCE_FILES ../AStarSearch.h ../AStarSearch.cpp ../Grid.h ../Grid.cpp ../Cell.h ../Cell.cpp ../GraphicInterface.h ../GraphicInterface.cpp)

# creates a library named 'core' using the specified source files
add_library(test ${SOURCE_FILES})

# links the 'core' target with the required SFML libraries
target_link_libraries(core sfml-system sfml-window sfml-graphics sfml-network sfml-audio)

# creates the test executable and specifies the source files to use
add_executable(runAllTest ${SOURCE_TEST_FILES})

# links the test executable to the Google Test libraries (gtest and gtest_main) and project classes
target_link_libraries(runAllTest gtest gtest_main test)