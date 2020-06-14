cmake_minimum_required(VERSION 3.13.4)
project(gal)

set(CMAKE_CXX_STANDARD 14)
find_package(PythonLibs 2.7)
find_package(Threads REQUIRED)
add_executable(gal
#        main_mpi.cpp
        try_lib.cpp
        genetic.h
        genetic.cpp
        get_parent.cpp
        get_child.cpp
        get_mutation.cpp
        genetic_arr.cpp find_minimum.cpp function_to_calc.cpp function_to_calc.h find_minimum.h)
target_include_directories(gal PRIVATE ${PYTHON_INCLUDE_DIRS})
target_link_libraries(gal Threads::Threads)
target_link_libraries(gal ${PYTHON_LIBRARIES})
