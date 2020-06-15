#include <set>
#include <thread>
#include <map>
#include <iostream>
#include <atomic>
#include <cstring>
#include "genetic.h"
#include "additional_functions.h"

Genetic::Genetic(Genetic const &genetic){}


Genetic::Genetic(int (*func)(int values[]), int n_vars, int size_of_p,
                 int am_threads, int selection, int mating, int mutation,
                 int lower_limit, int upper_limit, int mut_rate, int st_dev,
                 int am_of_gens){

    f = func;
    minim = lower_limit;
    maxim = upper_limit;
    pop_size = size_of_p;
    n_variables = n_vars;
    int* pop = new int[n_variables*size_of_p];

    am_of_threads = am_threads;
    selection_method = selection;
    mating_method = mating;
    mutation_method = mutation;
    mutation_rate = mut_rate;
    standard_deviation = st_dev;
    am_of_generations = am_of_gens;
    population = initializePopulation(pop);
}


int* Genetic::initializePopulation(int* pop){
    /**
    * @brief This function creates the initial population by
    * randomising the points
    *
    * @param pop
    * integer array of population (all the points)
    */
    for(int i = 0; i < pop_size; i++){
        for(int j = 0; j < n_variables; j++) {
            int r = getRand(minim,maxim);
            pop[j+(i*n_variables)] = r;
        }
    }
    return pop;
}


void Genetic::evaluatePopulation(int* pop, int start, int end, int *res){
    /**
    * @brief This function would be run in threads it runs the
    * points(individuals) from the population form start index
    * to end index through the function initialized in constructor
    *
    * @param pop
    * integer array of population (all the points)
    *
    * @param start
    * start index of the range
    *
    * @param end
    * end index of the range
    *
    * @param res
    * integer array of place where results would be written to
    */
    for (int i = start; i < end; i++){
        int point[n_variables];
        for(int j = 0; j < n_variables; j++) {
            if(pop[i*n_variables+j] > maxim){ // checking boundaries
                pop[i*n_variables+j] = getRand(minim, maxim);
            }
            point[j] = pop[i*n_variables+j];
        }
        int a = (*f)(point); // running point through the function
        res[i] = a;
    }
}


int* Genetic::get_signs(const int* p1, const int* p2) const{
   /**
   * @brief This function returns the integer array of 1 and -1
   * that represents the signs of two parents that would be
   * given to the child
   *
   * @param p1
   * integer array of coordinates of the first parent
   *
   * @param p2
   * integer array of coordinates of the second parent
*/
    int* signs = new int[n_variables];
    for(int i = 0; i < n_variables; i++){
        if(p1[i] < 0 && p2[i] < 0){// if signs are the same copying sign
            signs[i] = -1;
        } else { // if signs are not the same assigning 1
            signs[i] = 1;
        }
    }
    return signs;
}


char* Genetic::getCipher(int* parent) const{
    /**
       * @brief This function returns the cipher (binary representation)
       * of the parent(integer value)
       *
       * @param parent
       * integer array if coordinates of given  individual (parent)
    */
    char* binary_parent = new char[n_variables*10];
    for(int i = 0; i < n_variables;i++){
        std::string str_par = std::bitset<10>(abs(parent[i])).to_string(); //to binary length 10
        for (int j = 0; j < 10; j++){
            binary_parent[j+i*10] = str_par[j];
        }
    }
    return binary_parent;
}


int Genetic::getRand(int start, int end){
    /**
       * @brief This function returns the random integer
       * in given range
       *
       * @param start
       * start of the range
       * @param end
       * end of the range
    */
    std::uniform_int_distribution<int> distribution(start, end);
    return distribution(generator);
}

