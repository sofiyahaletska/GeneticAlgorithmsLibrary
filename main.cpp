#include <iostream>
#include <chrono>
#include <atomic>
#include <cmath>
#include "genetic.h"
#include "vizualization.h"

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



int func (std::vector<int>* lst){
    int a = abs((*lst)[0]) - abs((*lst)[1]); /// |x|-|y|
    return a;
}

double funcD (std::vector<double>* lst){
    double a = abs((*lst)[0]) - abs((*lst)[1]); /// |x|-|y|
    return a;
}

int main() {

    std::cout << "Function      K = |x|-|y|" << std::endl << std::flush;
    Genetic gen = Genetic(&func, 100, 2, 4);
    auto start = get_current_time_fenced();
    std::vector<int>* minim = gen.run();
    auto end = get_current_time_fenced();

    std::cout << "Minimum found      X = " << (*minim)[0]  << " Y = " << (*minim)[1]
//            <<" Z = " << (*minim)[2]<<" Z = " << (*minim)[3]<<" Z = " << (*minim)[4]
            <<std::endl;
    std::cout << "Time: " << to_us(end - start) << std::endl;
    visualization(&funcD, 3);
    return 0;
}