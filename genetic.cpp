#include <set>
#include <thread>
#include <map>
#include <iostream>
#include <atomic>
#include <cstring>
#include "genetic.h"

int findSmallestElement(int arr[], int n){
    int temp = arr[0];
    int res = 0;
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


Genetic::Genetic(int (*func)(int values[]), int size_of_p, int n_vars, int am_threads){
    f = func;
    minim = -200;
    maxim = 200;
    pop_size = size_of_p;
    n_variables = n_vars;
    int* pop = new int[n_variables*size_of_p];
    population = initializePopulation(pop);
    am_of_threads = am_threads;
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


void Genetic::evaluatePopulation(int* pop, int start, int end, int *res){
    for (int i = start; i < end; i++){
        int point[n_variables];
        for(int j = 0; j < n_variables; j++) {
            if(pop[i*n_variables+j] > maxim){
                pop[i*n_variables+j] = getRand(minim, maxim);
            }
            point[j] = pop[i*n_variables+j];
        }
        int a = (*f)(point);
        res[i] = a;
    }
}


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


int Genetic::getRand(int start, int end){
    std::uniform_int_distribution<int> distribution(start, end);
    return distribution(generator);
}

