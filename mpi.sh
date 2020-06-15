#!/bin/sh
mpic++ main_mpi.cpp function_to_calc.cpp function_to_calc.h genetic.h genetic.cpp get_methods.cpp additional_functions.cpp additional_functions.h genetic_mpi.cpp get_parent.cpp get_child.cpp get_mutation.cpp -o maincpp
mpirun -np 4 maincpp 2 100 0 0 0 0 -2 2 2 2 1000
