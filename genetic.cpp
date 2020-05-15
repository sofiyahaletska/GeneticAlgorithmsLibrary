#include <set>
#include <thread>
#include <map>
#include <iostream>
#include "genetic.h"

Genetic::Genetic(int (*func)(std::vector<int>* values), int size_of_p = 100, int n_vars = 2, int am_threads=4){
    f = func;
    minim = -100;
    maxim = 100;
    pop_size = size_of_p;
    n_variables = n_vars;
    population = initializePopulation();
    am_of_threads = am_threads;
}

int Genetic::getRand(int start, int end){
        std::uniform_int_distribution<int> distribution(start, end);
        return distribution(generator);
}


std::vector<std::vector<int>*>* Genetic::initializePopulation(){
    auto* result_arr = new std::vector<std::vector<int>*>();
    for(int i = 0; i < pop_size; i++){
        auto* curr_arr = new std::vector<int>();
        for(int j = 0; j < n_variables; j++) {
            curr_arr->push_back(getRand(minim,maxim));
        }
        result_arr->push_back(curr_arr);
    }
    return result_arr;
}

std::vector<int>* Genetic::evaluatePopulation(int start, int end, std::vector<int> *res){
    for (int i = start; i < end; i++){
        (*res)[i] = (*f)((*population)[i]);
    }
    return res;
}

std::vector<int>* Genetic::mutation(std::vector<int>* individual, int upper_limit, int lower_limit,
                                    std::string method, int muatation_rate, double standard_deviation) {

    std::vector<int> *mutated_individual;
    mutated_individual = new std::vector<int>((*individual));

    if (method == "Reset") {
        for (int x = 0; x < muatation_rate; x++) {
            (*mutated_individual)[x] = getRand(lower_limit, upper_limit);
        }
    }

    if (method == "Gauss") {
        int mean;
        for (int x = 0; x < muatation_rate - 1; x++) {

            mean = ((*individual)[x] - (*individual)[x + 1]) / 2;
            std::normal_distribution<> d{(double)mean, standard_deviation};
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
            (*mutated_individual)[x] = mean;
            delete hist;
        }
    }

    return mutated_individual;
}



std::vector<int>* Genetic::getResults(){
    auto* results = new std::vector<int>();
    results->reserve(population->size());
    for (int i = 0; i < population->size(); i++){
        results->push_back(0);
    }

    std::vector<std::thread> vector_of_threads1;
    vector_of_threads1.reserve(am_of_threads);
    int part = population->size()/am_of_threads;
    for (int i = 0; i < am_of_threads; i++) {
        int end = part*(i+1);
        if (i == am_of_threads-1){
            end = population->size();
        }
        vector_of_threads1.emplace_back(&Genetic::evaluatePopulation, this, part*i, end, results);
    }
    for (auto &t: vector_of_threads1) {
        t.join();
    }
    return results;
}

void Genetic::next_gen(){
    auto* results = getResults();

    auto children = new std::vector<std::vector<int>*>();
    auto smallest = std::min_element(results->begin(), results->end());
    int index = std::distance(results->begin(), smallest);
    children->push_back((*population)[index]);

    std::vector<std::thread> vector_of_threads2;
    vector_of_threads2.reserve(am_of_threads);
    for (int i = 0; i < am_of_threads; i++) {
        vector_of_threads2.emplace_back(&Genetic::calcGeneration, this, children, results);
    }
    for (auto &t: vector_of_threads2) {
        t.join();
    }

    population = children;
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

std::vector<int>* Genetic::get_signs(std::vector<int>* p1, std::vector<int>* p2){
    auto signs = new std::vector<int>();
    for(int i = 0; i < n_variables; i++){
        if((*p1)[i] < 0 && (*p2)[i] < 0){
            signs->push_back(-1);
        } else if ((*p1)[i] >= 0 and (*p2)[i] >= 0){
            signs->push_back(1);
        }else{
            {
                std::lock_guard<std::mutex> lg{m_m};
                signs->push_back(getRand(-1,1));
            }
        }
    }
    return signs;
}

std::vector<std::string>* getCipher(std::vector<int>* parent){
    auto* binary_parent = new std::vector<std::string>();
    for(auto i: (*parent)){
        binary_parent->push_back(std::bitset<10>(abs(i)).to_string()); //to binary
    }
    return binary_parent;
}

std::vector<std::string>* Genetic::childSinglePoint(std::vector<std::string>* binary_p1, std::vector<std::string>* binary_p2){
    auto child = new std::vector<std::string>();
    for(int i = 0; i < binary_p1->size(); i++){
        for(int j = 0; j < (*binary_p1)[i].size()/2; j++) {
            std::string s(1, (*binary_p1)[i][j]);
            child->push_back(s);
        }
        for(int l = (*binary_p2)[i].size()/2; l < (*binary_p2)[i].size(); l++) {
            std::string x(1, (*binary_p2)[i][l]);
            child->push_back(x);
        }
    }
    return child;
}

std::vector<std::string>* Genetic::childSemirandomBit(std::vector<std::string>* binary_p1, std::vector<std::string>* binary_p2){
    auto child = new std::vector<std::string>();
    for(int i = 0; i < binary_p1->size(); i++){
        for(int j = 0; j < (*binary_p1)[i].size(); j++){
            if ((*binary_p1)[i][j] == (*binary_p2)[i][j]){
                std::string s(1, (*binary_p1)[i][j]);
                child->push_back(s);
            } else {
                int rand = getRand(0, 1);
                child->push_back(std::to_string(rand));
            }

        }
    }
    return child;
}

std::vector<int>* Genetic::getNewChild(std::vector<std::string>* binary_p1,
        std::vector<std::string>* binary_p2, std::vector<int>* signs, int method){
    std::vector<std::string>* child;
    if (method == 1){
        child = childSinglePoint(binary_p1, binary_p2);
    } else {
        child = childSemirandomBit(binary_p1, binary_p2);
    }



    std::string child_str;
    for (const auto &piece : (*child)) child_str += piece;

    std::vector<std::string> gens;
    int prev = 0;
    int amount_of_bits_in_one_variable = child->size() / n_variables;
    int end = amount_of_bits_in_one_variable;
    for (int i = 1; i < n_variables + 1; i++){
        std::string g = child_str.substr(prev,end-prev);
        gens.push_back(g);
        prev = end;
        end += amount_of_bits_in_one_variable;
    }

    auto new_child = new std::vector<int>();
    for(int i = 0; i < gens.size(); i++){
        new_child->push_back((*signs)[i] * stoi(gens[i], 0, 2));
    }

    return new_child;
}

std::vector<std::vector<int>*>* Genetic::getParent(std::vector<int>* results, int method){
    if (method == 1){
        return getParentByFitness(results);

    }else{
        return randomParents(results);
    }
}

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



void Genetic::calcGeneration(std::vector<std::vector<int>*>* children, std::vector<int>* results){
    int p_size = 0;
    {
        std::lock_guard<std::mutex> lg{m_m};
        p_size = children->size();
    }
    while (p_size < pop_size){
        std::vector<int>* p1;
        std::vector<int>* p2;

        {
            std::lock_guard<std::mutex> lg{m_m};
            std::vector<std::vector<int>*>* parents = getParent(results, 1);
            el1 = (el1 +1)%100;
            el2 = (el2 +1)%100;
            if ((*parents)[1] == NULL){
                std::cout << "Error" << std::endl;
            }
            p1 = (*parents)[0];
            p2 = (*parents)[1];
            delete parents;
        }

        auto signs = get_signs(p1, p2);
        auto* binary_p1 = getCipher(p1);
        auto* binary_p2 = getCipher(p2);

        std::vector<int>* new_child = getNewChild(binary_p1, binary_p2, signs, 1);
        new_child = mutation(new_child, maxim, minim, "Gauss", 2);

        {
            std::lock_guard<std::mutex> lg{m_m};
            children->push_back(new_child);
        }

        delete binary_p1;
        delete binary_p2;
        delete signs;
        {
            std::lock_guard<std::mutex> lg{m_m};
            p_size = children->size();
        }
    }
}



std::vector<int>* Genetic::run(){
    int am_of_gens = 0;
    while (am_of_gens < 2000){
        am_of_gens++;
        next_gen();
    }
    return (*population)[0];
}

Genetic::Genetic(Genetic const &genetic){

}


