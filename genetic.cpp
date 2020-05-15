#include <set>
#include <thread>
#include <map>
#include <iostream>
#include "genetic.h"
#include "vizualization.h"

Genetic::Genetic(Genetic const &genetic){}

Genetic::Genetic(int (*func)(std::vector<int>* values), int size_of_p = 100, int n_vars = 2, int am_threads=4){
    f = func;
    minim = -11;
    maxim = 11;
    pop_size = size_of_p;
    n_variables = n_vars;
    population = initializePopulation();
    am_of_threads = am_threads;
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

std::vector<int>* Genetic::run(){
    auto min_points = new std::vector<std::vector<int>*>();
    int am_of_gens = 0;
    while (am_of_gens < 1000){
        am_of_gens++;
        next_gen();
        min_points->push_back((*population)[0]);
    }
    std::cout << "Minimum found      X = " << (*(*population)[0])[0] // << " Y = " << (*(*population)[0])[1]
              //            <<" Z = " << (*minim)[2]<<" Z = " << (*minim)[3]<<" Z = " << (*minim)[4]
              <<std::endl;
    visualization(f, 2, min_points);
    return (*population)[0];
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

std::vector<int>* Genetic::evaluatePopulation(int start, int end, std::vector<int> *res){
    for (int i = start; i < end; i++){
        (*res)[i] = (*f)((*population)[i]);
    }
    return res;
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
            std::vector<std::vector<int>*>* parents = getParent(results, 0);
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

        std::vector<int>* new_child = getNewChild(binary_p1, binary_p2, signs, 0);
        new_child = mutation(new_child, maxim, minim, 0, 2);

        {
            std::lock_guard<std::mutex> lg{m_m};
            for (int i = 0; i< new_child->size(); i++){
                if ((*new_child)[i] > maxim || (*new_child)[i] < minim){
                    (*new_child)[i] = getRand(minim, maxim);
                }
            }
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

std::vector<std::vector<int>*>* Genetic::getParent(std::vector<int>* results, int method){
    if (method == 1){
        return getParentByFitness(results);

    }else{
        return randomParents(results);
    }
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


std::vector<std::string>* Genetic::getCipher(std::vector<int>* parent){
    auto* binary_parent = new std::vector<std::string>();
    for(auto i: (*parent)){
        binary_parent->push_back(std::bitset<10>(abs(i)).to_string()); //to binary
    }
    return binary_parent;
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

std::vector<int>* Genetic::mutation(std::vector<int>* individual, int upper_limit, int lower_limit,
                                    int method, int muatation_rate, double standard_deviation) {
    if(method == 1){
        return gaussMutation(individual, lower_limit, upper_limit);
    }else{
        return resetMutation(individual, lower_limit, upper_limit);
    }
}

int Genetic::getRand(int start, int end){
        std::uniform_int_distribution<int> distribution(start, end);
        return distribution(generator);
}
