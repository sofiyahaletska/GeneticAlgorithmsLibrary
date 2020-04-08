#ifndef PROJECT_CPP_GENETIC_H
#define PROJECT_CPP_GENETIC_H
#include <vector>
#include <random>
#include <algorithm>
#include <bitset>

class Genetic{
public:
    Genetic(int (*f)(std::vector<int>* values), int pop_size, int n_variables);
    std::vector<std::vector<int>*>* initializePopulation();
    std::vector<int>* evaluatePopulation();
    void next_gen();
    std::vector<int>* run();
    int (*f)(std::vector<int>* values);
    int minim;
    int maxim;
    int pop_size;
    int n_variables;
    std::vector<std::vector<int>*>* population;
    std::default_random_engine generator;
};


#endif //PROJECT_CPP_GENETIC_H
