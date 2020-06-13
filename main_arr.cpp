#include <iostream>
#include <chrono>
#include <atomic>
#include <cmath>
#include "genetic.h"
#include <thread>



std::chrono::high_resolution_clock::time_point get_current_time_fenced()
{
    std::atomic_thread_fence(std::memory_order_seq_cst);
    auto res_time = std::chrono::high_resolution_clock::now();
    std::atomic_thread_fence(std::memory_order_seq_cst);
    return res_time;
}

template<class D>
long long to_us(const D& d)
{
    return std::chrono::duration_cast<std::chrono::microseconds>(d).count();
}


int func (int* lst){
    int a = pow(lst[0], 2) + lst[0]*2; /// x^4 - 4^x
    return a;
}


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

    int* res_a = new int[n_variables];
    std::vector<int>* res = new std::vector<int>();
    for(int j = 0; j < n_variables; j++) {
        res->push_back(population[j]);
        res_a[j] = population[j];
    }
// << " Y = " << (*res)[1] 

    std::cout << "Minimum found      X = " << (*res)[0] <<std::endl;
    std::cout << "F(x) = " << f(res_a) << std::endl;
    return res;
}



void Genetic::next_gen(){
    int* results = getResults();

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
    for (int i = 0; i < pop_size*n_variables; i++){
        population[i] = children[i];
    }

    delete[] children;

}

int* Genetic::getResults(){
    int* results = new int[pop_size];
    std::vector<std::thread> vector_of_threads1;
    vector_of_threads1.reserve(am_of_threads);
    int part = pop_size/am_of_threads;
    for (int i = 0; i < am_of_threads; i++) {
        int end = part*(i+1);
        if (i == am_of_threads-1){
            end = pop_size;
        }
        vector_of_threads1.emplace_back(&Genetic::evaluatePopulation, this, population, part*i, end, results);
    }
    for (auto &t: vector_of_threads1) {
        t.join();
    }
    return results;
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
            for (int i = 0; i < n_variables; i++){
                p1[i] = parents[i];
            }
            for (int i = 0; i < n_variables; i++){
                p2[i] = parents[i+n_variables];
            }

        }

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
//        delete binary_p1;
//        delete binary_p2;
//        delete signs;
//        delete[] p1;
//        delete[] p2;
//        delete[] pars;

        {
            std::lock_guard<std::mutex> lg{m_m};
            p_size = children_size[0];
        }
    }
}


int main() {

    std::cout << "Function      K = x^2 + 2*x" << std::endl << std::flush;

    Genetic gen = Genetic(&func, 100, 2, 4);

    auto start = get_current_time_fenced();

    std::vector<int>* minim = gen.run();

    auto end = get_current_time_fenced();

    std::cout << "Time: " << to_us(end - start) << std::endl;
    return 0;
}
