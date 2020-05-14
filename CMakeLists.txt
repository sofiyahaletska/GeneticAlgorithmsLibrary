cmake_minimum_required(VERSION 3.15)
project(project_cpp)

set(CMAKE_CXX_STANDARD 14)
find_package(Threads REQUIRED)
add_executable(project_cpp main.cpp genetic.h genetic.cpp)
target_link_libraries(project_cpp Threads::Threads)