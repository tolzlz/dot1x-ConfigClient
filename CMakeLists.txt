cmake_minimum_required(VERSION 3.10)
project(client)

set(CMAKE_CXX_STANDARD 11)

add_executable(client main.cpp)
find_package(Threads REQUIRED)
target_link_libraries(client Threads::Threads)
target_link_libraries(client ${CMAKE_THREAD_LIBS_INIT})

#添加编译选项
TARGET_LINK_LIBRARIES(client pthread)
set(CMAKE_CXX_FLAGS_DEBUG  " -ggdb ")