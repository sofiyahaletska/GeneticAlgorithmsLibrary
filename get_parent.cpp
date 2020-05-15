#include "genetic.h"

std::vector<std::vector<int>*>* Genetic::getParentByFitness(std::vector<int>* results){
    auto* parents = new std::vector<std::vector<int>*>();
    auto* cum_sum = new std::vector<int>();
    for (int i = 0; i < results->size(); i++) {
        int a = (*results)[i];
        cum_sum->emplace_back(a);
    }
    sort(cum_sum->begin(), cum_sum->end());

    std::vector<int>* p1;
    std::vector<int>* p2;

    auto it1 = std::find(results->begin(), results->end(), (*cum_sum)[el1]);
    int ind1 = std::distance(results->begin(), it1);
    auto it2 = std::find(results->begin(), results->end(), (*cum_sum)[el2]);
    int ind2 = std::distance(results->begin(), it2);

    p1 = (*population)[ind1];
    p2 = (*population)[ind2];

    parents->push_back(p1);
    parents->push_back(p2);
    return parents;
}

std::vector<std::vector<int>*>* Genetic::randomParents(std::vector<int>* results){
    auto* parents = new std::vector<std::vector<int>*>();
    for (int i = 0; i < 2; i++) {
        std::vector<int>* parent;
        int randA1 = getRand(0, pop_size - 1);
        int randB1 = getRand(0, pop_size - 1);
        if ((*results)[randA1] < (*results)[randB1]) {
            parent = (*population)[randA1];
        } else {
            parent = (*population)[randB1];
        }
        parents->push_back(parent);
    }
    return parents;
}