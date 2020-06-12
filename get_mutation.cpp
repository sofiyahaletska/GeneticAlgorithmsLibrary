#include <map>
#include "genetic.h"

int* Genetic::resetMutation(int* individual,
        int lower_limit, int upper_limit, int muatation_rate){
    for (int x = 0; x < muatation_rate; x++) {
        individual[x] = getRand(lower_limit, upper_limit);
    }
    return individual;
}

int* Genetic::gaussMutation(int *individual, int lower_limit,
        int upper_limit, int muatation_rate, double standard_deviation) {
    muatation_rate = n_variables;
    for (int x = 0; x < muatation_rate; x++) {
        int mean;

        if (x == n_variables - 1) {
            mean = getRand(lower_limit, upper_limit);
        } else {
            mean = (individual[x] - individual[x + 1]) / 2;
        }
        std::normal_distribution<> d{(double) mean, standard_deviation};
        auto *hist = new std::map<int, int>();
        for (int n = 0; n < 100; ++n) {
            int rand = d(generator);
            (*hist)[std::round(rand)]++;
        }

        int currentMax = 0;
        int LocMax = 0;
        for (auto it : *hist) {
            if (it.second > currentMax) {
                if (lower_limit < it.first < upper_limit) {
                    LocMax = it.first;
                }
            }
        }
        individual[x] = LocMax;
        delete hist;
    }
    return individual;
}

