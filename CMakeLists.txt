cmake_minimum_required(VERSION 3.15)
project(gal)

set(CMAKE_CXX_STANDARD 14)
find_package(Threads REQUIRED)
add_executable(gal main.cpp genetic.h genetic.cpp)
target_link_libraries(gal Threads::Threads)