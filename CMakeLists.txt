project(MatrixLib)
cmake_minimum_required(VERSION 2.8.7) # for github Circle CI
add_definitions(-std=c++11)
set(CXX_FLAGS "-Wall" "-Wextra")
set(CMAKE_CXX_FLAGS, "${CXX_FLAGS}")
set(CMAKE_C_COMPILER, "/usr/bin/clang")
set(CMAKE_CXX_COMPILER, "/usr/bin/clang++")

add_subdirectory(Lib)
add_subdirectory(main)
add_subdirectory(Test)

