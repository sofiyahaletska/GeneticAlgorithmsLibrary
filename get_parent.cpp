#include <iostream>
#include "genetic.h"

int* Genetic::getParentByFitness(int* parents, int* results){

    int cum_sum[pop_size];
    for (int i = 0; i < pop_size; i++) {
        int a = results[i];
        cum_sum[i] = a;
    }
    std::sort(cum_sum, cum_sum+pop_size);

    int ind1 = findElementIndex(results, pop_size, cum_sum[el1]);
    int ind2 = findElementIndex(results, pop_size, cum_sum[el2]);

    for (int i=0; i < n_variables; i++){
        parents[i] = population[ind1*n_variables+i];
        parents[i+n_variables] = population[ind2*n_variables+i];
    }
    return parents;
}

int* Genetic::randomParents(int* parents, const int* results){
    for (int i = 0; i < 2; i++) {
        int randA1 = getRand(0, pop_size - 1);
        int randB1 = getRand(0, pop_size - 1);
        if (results[randA1] < results[randB1]) {
            for (int j = 0; j < n_variables; j++) {
                parents[j+i*n_variables] = population[randA1 * n_variables + j];
            }
        } else {
            for (int j = 0; j < n_variables; j++) {
                parents[j+i*n_variables] = population[randB1 * n_variables + j];
            }
        }
    }
    return parents;
}