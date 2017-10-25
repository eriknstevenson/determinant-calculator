cmake_minimum_required(VERSION 3.2)
project(determinant)

set(CMAKE_CXX_STANDARD 14)

file(GLOB SOURCE_FILES src/*)
add_executable(determinant ${SOURCE_FILES})
