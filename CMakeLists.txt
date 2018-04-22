project(awtt)

cmake_minimum_required(VERSION 2.6)

set(CMAKE_BUILD_TYPE release)

add_definitions(-Wall -Wextra)

add_executable(bijiao bijiao.cpp)

add_executable(gaimingzi gaimingzi.cpp)
