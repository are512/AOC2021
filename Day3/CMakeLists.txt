cmake_minimum_required(VERSION 3.28)
project(Day3)

set(CMAKE_CXX_STANDARD 23)

file(GLOB text_files "*.txt")
file(COPY ${text_files} DESTINATION ${CMAKE_CURRENT_BINARY_DIR})

add_executable(Day3 main.cpp)
