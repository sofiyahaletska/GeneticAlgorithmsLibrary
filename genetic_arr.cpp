#include <iostream>
#include <thread>
#include "genetic.h"
#include "additional_functions.h"

int* Genetic::run(){
    /**
    * @brief This function that performs the main part of the algorithm
    * It generates certain amount of generating, finding minimum of the function and the point
    * where this minimum is reached and returning it.
    */
    int min_points[am_of_generations*n_variables];
    int am_of_gens = 0;
    while (am_of_gens < am_of_generations){
        am_of_gens++;
        next_gen();

        for(int j = 0; j < n_variables; j++) {
            min_points[j] = population[j];
        }
    }

    int* res_min_and_point = new int[n_variables+1];
    int* res_point = new int[n_variables];

    for(int j = 1; j < n_variables+1; j++) {
        res_min_and_point[j] = population[j-1];
        res_point[j-1] = population[j-1];
    }

    res_min_and_point[0] = f(res_point);
    
    return res_min_and_point;
}



void Genetic::next_gen(){
    /**
    * @brief This function that generate next generating of individuals.
    * It divides current generation into parts for every thread, calculates new
    * generation children
    */
    int* results = getResults();
//    int* results = new int[pop_size];
//    evaluatePopulation(population, 0, pop_size*n_variables, results);
    int* children = new int[pop_size*n_variables];
    int index = findSmallestElement(results, pop_size);

    for (int i = 0; i < n_variables; i++){
        children[i] = population[index*n_variables+i];

    }
    int* scount = new int[am_of_threads];
    int* displs = new int[am_of_threads];
    displs[0] = n_variables;
    int part = pop_size/am_of_threads ;
    for (int i = 0; i < am_of_threads; i++) {
        int end = part *(i + 1);
        if (i == (am_of_threads - 1)) {
            end = pop_size-1;
        }
        scount[i] = end - part* i;
        if ( i != am_of_threads-1) {
            displs[i + 1] = displs[i] + scount[i];
        }
    }

    int* children_size = new int[1];
    children_size[0] = n_variables;
    std::vector<std::thread> vector_of_threads2;
    vector_of_threads2.reserve(am_of_threads);
    for (int i = 0; i < am_of_threads; i++) {
        vector_of_threads2.emplace_back(&Genetic::calcGeneration, this, results, scount[i], children, displs[i]);
    }
    for (auto &t: vector_of_threads2) {
        t.join();
    }

    for(int j = 0; j < pop_size*n_variables; j++){
        population[j] = children[j];
    }

    delete[] children;

}

int* Genetic::getResults(){
    /**
    * @brief This function calculates the fitness values of gen sequences
    * in certain amount of threads and returns the results
    */
    int* results = new int[pop_size];
    std::vector<std::thread> vector_of_threads1;
    vector_of_threads1.reserve(am_of_threads);
    int part = pop_size/am_of_threads;
    for (int i = 0; i < am_of_threads; i++) {
        int end = part*(i+1);
        if (i == am_of_threads-1){
            end = pop_size;
        }

        vector_of_threads1.emplace_back(&Genetic::evaluatePopulation, this, population, part*i, end, results);
    }
    for (auto &t: vector_of_threads1) {
        t.join();
    }
    return results;
}


void Genetic::calcGeneration(int* results, int amount, int*  children, int displs){
    /**
    * @brief This function is private and used in our library to calculate the generation when one is using
    * std::threads as a type of parallelization.
    * In this function selection of parents, children making and mutation are called.
    * The function has parameters as follows:
    *
    * @param results
    * This is a buffer with the results of calculating the function at certain points,
    * which was calculated in the previous step, to be more precise, in the function evaluatePopulation.
    * The required argument type is int*.
    *
    * @param amount
    * This is a parameter that determines how many children you need to create.
    * The required argument type is int.
    *
    * @param children
    *This is a buffer that is passed to the function as a parameter,
    *and as a result of the function it will be filled with a new generation.
    * The required argument type is int*.
    *
    * @param displs

    */
    int children_index = displs;
    while (amount){

        int* p1 = new int[n_variables];
        int* p2 = new int[n_variables];
        int* pars = new int[2*n_variables];
        int* parents;

        parents = getParent(pars, results);
        el1 = (el1 +1)%100;
        el2 = (el2 +1)%100;

        for (int i = 0; i < n_variables; i++){
            p1[i] = parents[i];
        }
        for (int i = 0; i < n_variables; i++){
            p2[i] = parents[i+n_variables];
        }

        int* signs = get_signs(p1, p2);

        char* binary_p1 = getCipher(p1);
        char* binary_p2 = getCipher(p2);

        int* new_child = getNewChild(binary_p1, binary_p2);
        new_child = mutation(new_child);

        for (int i = 0; i< n_variables; i++){
            if (new_child[i] > maxim || new_child[i] < minim){
                new_child[i] = getRand(minim, maxim);
            }
        }
        for(int i = 0; i < n_variables; i++){
            children[children_index] = new_child[i];
            children_index++;
        }
        delete binary_p1;
        delete binary_p2;
        delete signs;
        amount--;
    }
}
