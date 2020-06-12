#include <set>
#include <thread>
#include <map>
#include <iostream>
#include <atomic>
#include "genetic.h"
#include "vizualization.h"

int findSmallestElement(int arr[], int n){
    int res = -1;
    int temp = arr[0];
    for(int i=0; i<n; i++) {
        if(temp>arr[i]) {
            temp=arr[i];
            res = i;
        }
    }
    return res;
}


int findElementIndex(int arr[], int n, int el){
    int res = -1;
    for(int i=0; i<n; i++) {
        if(arr[i] == el) {
            res = i;
            break;
        }
    }
    return res;
}


Genetic::Genetic(Genetic const &genetic){}

Genetic::Genetic(int (*func)(int values[]), int size_of_p = 100, int n_vars = 2, int am_threads=4){
    f = func;
    minim = -11;
    maxim = 11;
    pop_size = size_of_p;
    n_variables = n_vars;
    int* pop = new int[n_variables*size_of_p];
    population = initializePopulation(pop);
    am_of_threads = am_threads;
//    for(int i = 0; i < pop_size; i++){
//        for(int j = 0; j < n_variables; j++) {
//            std::cout << population[j+(i*n_variables)] << std::endl;
//        }
//    }
}

int* Genetic::initializePopulation(int* pop){
        for(int i = 0; i < pop_size; i++){
        for(int j = 0; j < n_variables; j++) {
            int r = getRand(minim,maxim);
            pop[j+(i*n_variables)] = r;
        }
    }
    return pop;
}
//
std::vector<int>* Genetic::run(){
    int min_points[1000*n_variables];
    int am_of_gens = 0;
    while (am_of_gens < 1000){
        am_of_gens++;
        next_gen();

        for(int j = 0; j < n_variables; j++) {
            min_points[j] = population[j];
        }


    }
    std::vector<int>* res = new std::vector<int>();
    for(int j = 0; j < n_variables; j++) {
        res->push_back(population[j]);
    }

    std::cout << "Minimum found      X = " << (*res)[0] // << " Y = " << (*(*population)[0])[1]
              //            <<" Z = " << (*minim)[2]<<" Z = " << (*minim)[3]<<" Z = " << (*minim)[4]
              <<std::endl;
//    visualization(f, 2, min_points);
    return res;
}
//
int* Genetic::getResults(int* results){
//    int* results = new int[pop_size];
    std::vector<std::thread> vector_of_threads1;
    vector_of_threads1.reserve(am_of_threads);
    int part = pop_size/am_of_threads;
    for (int i = 0; i < am_of_threads; i++) {
        int end = part*(i+1);
        if (i == am_of_threads-1){
            end = pop_size;
        }
        vector_of_threads1.emplace_back(&Genetic::evaluatePopulation, this, part*i, end, results);
    }
    for (auto &t: vector_of_threads1) {
        t.join();
    }
//    evaluatePopulation(0, pop_size, results);
    return results;
}
//
void Genetic::evaluatePopulation(int start, int end, int *res){
    for (int i = start; i < end; i++){
        int point[n_variables];
        for(int j = 0; j < n_variables; j++) {
            point[j] = population[i*n_variables+j];
        }
        int a = (*f)(point);
        res[i] = a;
    }
}

void Genetic::next_gen(){
    int res[pop_size];
    int* results = getResults(res);
//    for(int i = 0; i < pop_size; i++){
//        for(int j = 0; j < n_variables; j++) {
//            std::cout << results[j+(i*n_variables)] << std::endl;
//        }
//    }
    int* children = new int[pop_size*n_variables];
    int index = findSmallestElement(results, pop_size);

    for (int i = 0; i < n_variables; i++){
        children[i] = population[index*n_variables+i];

    }

    int* children_size = new int[1];
    children_size[0] = n_variables;
    std::vector<std::thread> vector_of_threads2;
    vector_of_threads2.reserve(am_of_threads);
    for (int i = 0; i < am_of_threads; i++) {
        vector_of_threads2.emplace_back(&Genetic::calcGeneration, this, children, results, children_size);
    }
    for (auto &t: vector_of_threads2) {
        t.join();
    }
//    calcGeneration(children, results, children_size);
//
    population = children;
}

void Genetic::calcGeneration(int* children, int* results, int* children_size){
    int p_size = 0;
    {
        std::lock_guard<std::mutex> lg{m_m};
        p_size = children_size[0];
    }
    while (p_size < pop_size){
        int* p1 = new int[n_variables];
        int* p2 = new int[n_variables];
        int* pars = new int[2*n_variables];
        int* parents;

        {
            std::lock_guard<std::mutex> lg{m_m};
            parents = getParent(pars, results, 0);
            el1 = (el1 +1)%100;
            el2 = (el2 +1)%100;
//            if ((*parents)[1] == NULL){
//                std::cout << "Error" << std::endl;
//            }
            for (int i = 0; i < n_variables; i++){
                p1[i] = parents[i];
            }
            for (int i = 0; i < n_variables; i++){
                p2[i] = parents[i+n_variables];
            }

        }
//

        int* signs = get_signs(p1, p2);


        char* binary_p1 = getCipher(p1);
        char* binary_p2 = getCipher(p2);

        int* new_child = getNewChild(binary_p1, binary_p2, signs, 0);
        new_child = mutation(new_child, maxim, minim, 1, 2);

        {
            std::lock_guard<std::mutex> lg{m_m};
            for (int i = 0; i< n_variables; i++){
                if (new_child[i] > maxim || new_child[i] < minim){
                    new_child[i] = getRand(minim, maxim);
                }
            }
            for(int i = 0; i < n_variables; i++){
                children[children_size[0]+i] = new_child[i];
            }
            children_size[0] += n_variables;
        }
//
        delete binary_p1;
        delete binary_p2;
        delete signs;
        {
            std::lock_guard<std::mutex> lg{m_m};
            p_size = children_size[0];
        }
    }
}
//
int* Genetic::getParent(int* parents, int* results, int method){
    if (method == 1){
        return getParentByFitness(parents, results);

    }else{
        return randomParents(parents, results);
    }
}

int* Genetic::get_signs(const int* p1, const int* p2){
    int* signs = new int[n_variables];
    for(int i = 0; i < n_variables; i++){
        if(p1[i] < 0 && p2[i] < 0){
            signs[i] = -1;
        } else if (p1[i] >= 0 and p2[i] >= 0){
            signs[i] = 1;
        }else{
            {
                std::lock_guard<std::mutex> lg{m_m};
                signs[i] = (getRand(-1,1));
            }
        }
    }
    return signs;
}

char* Genetic::getCipher(int* parent){
    char* binary_parent = new char[n_variables*10];
    for(int i = 0; i < n_variables;i++){
        std::string str_par = std::bitset<10>(abs(parent[i])).to_string(); //to binary
        for (int j = 0; j < 10; j++){
            binary_parent[j+i*10] = str_par[j];
        }
    }
    return binary_parent;
}
int binaryToDecimal(char* n, int len) {
    char* num = n;
    int dec_value = 0;
    int base = 1;

    for (int i = len - 1; i >= 0; i--) {
        if (num[i] == '1')
            dec_value += base;
        base = base * 2;
    }

    return dec_value;
}

int* Genetic::getNewChild(char* binary_p1, char* binary_p2, int* signs, int method){
    char* child;
    if (method == 1){
        child = childSinglePoint(binary_p1, binary_p2);
    } else {
        child = childSemirandomBit(binary_p1, binary_p2);
    }

    int* new_child = new int[n_variables];
    char gens[10];
    int amount_of_bits_in_one_variable = 10;
    int child_index = 0;
    for (int i = 1; i < n_variables + 1; i++){
        for (int j = 0; j < amount_of_bits_in_one_variable; j++) {
            gens[j] = child[child_index];
            child_index++;
        }
        new_child[i-1] = binaryToDecimal(gens, 10);
    }

    return new_child;
}

int* Genetic::mutation(int* individual, int upper_limit, int lower_limit,
                                    int method, int muatation_rate, double standard_deviation) {
    if(method == 1){
        return gaussMutation(individual, lower_limit, upper_limit);
    }else{
        return resetMutation(individual, lower_limit, upper_limit);
    }
}
//
int Genetic::getRand(int start, int end){
        std::uniform_int_distribution<int> distribution(start, end);
        return distribution(generator);
}
