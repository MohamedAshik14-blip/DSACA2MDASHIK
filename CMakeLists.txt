cmake_minimum_required(VERSION 3.29)
project(DSACA2)

set(CMAKE_CXX_STANDARD 20)

# Add GoogleTest as a subdirectory
add_subdirectory(googletest)

# Add your main project files
add_executable(DSACA21 main.cpp
        BinaryTree.h
        BSTNode.h
        TreeMap.h
        Employee.h
)

# Specify the test files
set(TEST_FILES test_main.cpp
        test_main.cpp)

# Create test executable
add_executable(runTests ${TEST_FILES})

# Link GoogleTest and gtest_main to the test executable
target_link_libraries(runTests gtest gtest_main)

# Enable testing
enable_testing()
add_test(NAME MyTests COMMAND runTests)
