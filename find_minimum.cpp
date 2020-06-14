#include <cstdio>      /* printf */
#include <cstdlib>     /* system, NULL, EXIT_FAILURE */
#include <iostream>
#include <bits/unique_ptr.h>
#include "genetic.h"
#include "function_to_calc.h"

std::string GetStdoutFromCommand(std::string cmd) {
    std::string data;
    FILE * stream;
    const int max_buffer = 256;
    char buffer[max_buffer];
    cmd.append(" 2>&1");
    stream = popen(cmd.c_str(), "r");
    if (stream) {
        while (!feof(stream))
            if (fgets(buffer, max_buffer, stream) != NULL) data.append(buffer);
        pclose(stream);
    }
    return data;
}

int* find_global_min(int type_of_parallelism=0, int (*f)(int values[])=nullptr, int number_of_variables=1,
        int amount_of_threads_or_cores=1, int lower_limit=-200, int upper_limit=200, int population_size=100,
        int selection_method=0, int mating_method=0, int mutation_type=0, int mutation_rate=1,
        int standard_deviation=2, int am_of_generations=1000) {
    int *minim = new int[number_of_variables+1];
    if (f == nullptr){
        f = &func;
    }
    if (type_of_parallelism == 1) {
        if (amount_of_threads_or_cores < 2){
            amount_of_threads_or_cores = 2;
        }
        if (system(NULL));
        else exit(EXIT_FAILURE);
        system("bash ../build_mpi.sh");
        std::string com = "mpirun -np " + std::to_string(amount_of_threads_or_cores) + " maincpp "
                          + std::to_string(number_of_variables) + " "
                          + std::to_string(population_size) + " "
                          + std::to_string(selection_method) + " "
                          + std::to_string(mating_method) + " "
                          + std::to_string(mutation_type) + " "
                          + std::to_string(lower_limit) + " "
                          + std::to_string(upper_limit) + " "
                          + std::to_string(mutation_rate) + " "
                          + std::to_string(standard_deviation) + " "
                          + std::to_string(am_of_generations) + " ";
        std::string line = GetStdoutFromCommand(com.c_str());
        std::string delimiter = " ";

        size_t pos = 0;
        std::string token;
        int index = 0;
        while ((pos = line.find(delimiter)) != std::string::npos) {
            token = line.substr(0, pos);
            minim[index] = std::stoi(token);
            index++;
            line.erase(0, pos + delimiter.length());
        }
    }else{
        Genetic gen = Genetic(f, number_of_variables, population_size, amount_of_threads_or_cores,
                              selection_method, mating_method, mutation_type, lower_limit, upper_limit,
                              mutation_rate, standard_deviation, am_of_generations);
        minim = gen.run();
    }
    return minim;
}
