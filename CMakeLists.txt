cmake_minimum_required(VERSION 3.10)


project(closestPair)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

file(GLOB_RECURSE source_list "src/*.cpp")
add_executable(closestPair ${source_list})