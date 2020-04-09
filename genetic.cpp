
#include "genetic.h"

Genetic::Genetic(int (*func)(std::vector<int>* values), int size_of_p = 100, int n_vars = 2){
    f = func;
    minim = -100;
    maxim = 100;
    pop_size = size_of_p;
    n_variables = n_vars;
    population = initializePopulation();
}

std::vector<std::vector<int>*>* Genetic::initializePopulation(){
    auto* result_arr = new std::vector<std::vector<int>*>();
    for(int i = 0; i < pop_size; i++){
        auto* curr_arr = new std::vector<int>();
        for(int j = 0; j < n_variables; j++) {
            std::uniform_int_distribution<int> distribution(minim,maxim);
            curr_arr->push_back(distribution(generator));
        }
        result_arr->push_back(curr_arr);
    }
    return result_arr;
}

std::vector<int>* Genetic::evaluatePopulation(){
    auto* result_arr = new std::vector<int>();
    for(auto  i : (*population)){
        result_arr->push_back((*f)(i));
    }
    return result_arr;
}
void Genetic::next_gen(){
    auto results = evaluatePopulation();
    auto children = new std::vector<std::vector<int>*>();
    auto smallest = std::min_element(results->begin(), results->end());
    int index = std::distance(results->begin(), smallest);
    children->push_back((*population)[index]);



    while (children->size() < pop_size){
        std::vector<int>* p1;
        std::vector<int>* p2;
        std::uniform_int_distribution<int> distribution1(0,pop_size - 1);
        int randA1 = distribution1(generator);
        int randB1 = distribution1(generator);
        if ((*results)[randA1] < (*results)[randB1]){
            auto p1_1 = (*population)[randA1];
            p1 = p1_1;

        } else {
            auto p1_1 = (*population)[randB1];
            p1 = p1_1;
        }

        int randA2 = distribution1(generator);
        int randB2 = distribution1(generator);
        if ((*results)[randA2] < (*results)[randB2]){
            auto p2_1 = (*population)[randA2];
            p2 = p2_1;
        } else {
            auto p2_1 = (*population)[randB2];
            p2 = p2_1;
        }

        auto signs = new std::vector<int>();
        for(int i = 0; i < 2; i++){
            if((*p1)[i] < 0 && (*p2)[i] < 0){
                signs->push_back(-1);
            } else if ((*p1)[i] >= 0 and (*p2)[i] >= 0){
                signs->push_back(1);
            }else{
                std::discrete_distribution<int> distribution2 {-1,1};
                signs->push_back(distribution2(generator));
            }
        }
        auto* binary_p1 = new std::vector<std::string>();
        auto* binary_p2 = new std::vector<std::string>();
        for(auto i: (*p1)){
            binary_p1->push_back(std::bitset<10>(abs(i)).to_string()); //to binary
        }
        for(auto i: (*p2)){
            binary_p2->push_back(std::bitset<10>(abs(i)).to_string()); //to binary
        }
        auto child = new std::vector<std::string>();
        for(int i = 0; i < binary_p1->size(); i++){
            for(int j = 0; j < (*binary_p1)[i].size(); j++){
                if ((*binary_p1)[i][j] == (*binary_p2)[i][j]){
                    std::string s(1, (*binary_p1)[i][j]);
                    child->push_back(s);
                } else {
                    std::uniform_int_distribution<int> distribution2(0, 1);
                    int rand = distribution2(generator);
                    child->push_back(std::to_string(rand));
                }

            }
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
//
//        std::vector<std::string> new_child;
        auto new_child = new std::vector<int>();
        for(int i = 0; i < gens.size(); i++){
            new_child->push_back((*signs)[i] * stoi(gens[i], 0, 2));
        }

        children->push_back(new_child);

    }

    population = children;

}
std::vector<int>* Genetic::run(){
    int am_of_gens = 0;
    while (am_of_gens < 1000){
        am_of_gens++;
        next_gen();
    }
    return (*population)[0];
}

