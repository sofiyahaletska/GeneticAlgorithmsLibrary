#include <map>
#include "genetic.h"

int* Genetic::resetMutation(int* individual){
    /**
   * @brief This function perform mutation of gens by replacing certain amount
   * of individual's gens (relying on mutation_rate) by random generated gen
   *
   * @param individual
   * Gens of the individual that is going to mutate
    */
    for (int x = 0; x < mutation_rate; x++) {
        individual[x] = getRand(minim, maxim); // generating random gen
    }
    return individual;
}

int* Genetic::gaussMutation(int *individual) {
    /**
    * @brief This function perform mutation in which the gene that
    * goes through mutation is replaced with a number that is generated
    * according to gauss distribution around the original gene.
    *
    * @param individual
    * Gens of the individual that is going to mutate
    */
    for (int x = 0; x < mutation_rate; x++) {
        int mean;

        if (x == n_variables - 1) {
            mean = getRand(minim, maxim);
        } else {
            mean = (individual[x] - individual[x + 1]) / 2;
        }
        // making Gauss distribution
        std::normal_distribution<> d{(double) mean, (double)standard_deviation};
        auto *hist = new std::map<int, int>();
        for (int n = 0; n < 100; ++n) {
            int rand = d(generator);
            (*hist)[std::round(rand)]++;
        }

        // finding the pick of distribution
        int currentMax = 0;
        int LocMax = 0;
        for (auto it : *hist) {
            if (it.second > currentMax) {
                if (minim < it.first < maxim) {
                    LocMax = it.first;
                }
            }
        }
        individual[x] = LocMax; // replacing mutated gen
        delete hist;
    }
    return individual;
}


int* Genetic::swapMutation(int* individual) {
    /**
    * @brief This function perform mutation of gens by swapping gens at
    * extreme ends of gens sequence
    * IMPORTANT! This mutation is for the sequences with big amount of gens
    *
    * @param individual
    * Gens of the individual that is going to mutate
    */
    if (n_variables != 1) {  // swapping gens
        int a = individual[0] ;
        int b = individual[n_variables-1];
        individual[0] = b;
        individual[n_variables-1] = a;
    }
    return individual;
}



int* Genetic::inversionMutation(int* individual) {
    /**
    * @brief This function perform mutation of gens by inverting
    * the middle part of the gens sequence
    * IMPORTANT! This mutation is for the sequences with big amount of gens
    *
    * @param individual
    * Gens of the individual that is going to mutate
    */
    if (n_variables > 3) { 
        int middle = n_variables/2;
        for (int i = 1; i < middle; i++) { // inverting middle gen sequence
            int a = individual[i] ;
            int b = individual[n_variables-1-i];
            individual[i] = b;
            individual[n_variables-1-i] = a;
        }
    }
    return individual;
}
