cmake_minimum_required(VERSION 3.29)
project(DSACA2)

set(CMAKE_CXX_STANDARD 20)


add_subdirectory(googletest)


add_executable(DSACA2 main.cpp

)

target_link_libraries(runTests gtest gtest_main)


enable_testing()
add_test(NAME MyTests COMMAND runTests)
