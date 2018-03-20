cmake_minimum_required(VERSION 3.9)
project(OMP_task)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fopenmp")

add_executable(OMP_task main.cpp)