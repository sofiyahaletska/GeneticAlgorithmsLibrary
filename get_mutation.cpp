#include <map>
#include "genetic.h"

int* Genetic::resetMutation(int* individual){
    for (int x = 0; x < mutation_rate; x++) {
        individual[x] = getRand(minim, maxim);
    }
    return individual;
}

int* Genetic::gaussMutation(int *individual) {
    for (int x = 0; x < mutation_rate; x++) {
        int mean;

        if (x == n_variables - 1) {
            mean = getRand(minim, maxim);
        } else {
            mean = (individual[x] - individual[x + 1]) / 2;
        }
        std::normal_distribution<> d{(double) mean, (double)standard_deviation};
        auto *hist = new std::map<int, int>();
        for (int n = 0; n < 100; ++n) {
            int rand = d(generator);
            (*hist)[std::round(rand)]++;
        }

        int currentMax = 0;
        int LocMax = 0;
        for (auto it : *hist) {
            if (it.second > currentMax) {
                if (minim < it.first < maxim) {
                    LocMax = it.first;
                }
            }
        }
        individual[x] = LocMax;
        delete hist;
    }
    return individual;
}

// mutation for simpler genoms with small amount of gens
int* Genetic::swapMutation(int* individual) {
    if (n_variables != 1) {
        int a = individual[0] ;
        int b = individual[n_variables-1];
        individual[0] = b;
        individual[n_variables-1] = a;
    }
    return individual;
}

// mutation for complicated genoms with more than 3 gens
int* Genetic::inversionMutation(int* individual) {
    if (n_variables > 3) {
        int middle = n_variables/2;
        for (int i = 1; i < middle; i++) {
            int a = individual[i] ;
            int b = individual[n_variables-1-i];
            individual[i] = b;
            individual[n_variables-1-i] = a;
        }
    }
    return individual;
}
