cmake_minimum_required(VERSION 3.13)
set(CMAKE_BUILD_TYPE Release)
set(CMAKE_CXX_FLAGS "-Werror -Wall -Wextra -O3")
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_EXPORT_COMPILE_COMMANDS 1)

project(pomocpp)
add_executable(pomocpp main.cpp pomo.cpp database.cpp)
