cmake_minimum_required(VERSION 3.15)
project(gal)

set(CMAKE_CXX_STANDARD 14)
find_package(PythonLibs 2.7)
find_package(Threads REQUIRED)
find_package(MPI REQUIRED)

add_executable(gal
        main.cpp
        genetic.h
        genetic.cpp
#        vizualization.cpp
#        vizualization.h
#        matplotlibcpp.h
        get_parent.cpp
        get_child.cpp
        get_mutation.cpp
        )
include_directories(${MPI_INCLUDE_PATH})

target_include_directories(gal PRIVATE ${PYTHON_INCLUDE_DIRS})
target_link_libraries(gal Threads::Threads)
target_link_libraries(gal ${PYTHON_LIBRARIES} ${MPI_C_LIBRARIES})