cmake_minimum_required(VERSION 3.10)
project(BaseAuth2_Cli)

set(CMAKE_CXX_STANDARD 14)

add_executable(BaseAuth2_Cli ndktool.cpp)
set(CMAKE_C_FLAGS_DEBUG "-ggdb")