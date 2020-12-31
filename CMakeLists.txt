cmake_minimum_required(VERSION 3.17)
project(covid2019)

set(CMAKE_CXX_STANDARD 14)
include_directories(include)

add_executable(covid2019 main.cpp
        src/connection.cpp
        src/connectionLinear.cpp
        src/connectionSI.cpp
        src/node.cpp
)


add_subdirectory(tests)