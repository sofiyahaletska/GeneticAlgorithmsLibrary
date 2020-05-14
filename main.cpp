#include <iostream>
#include <chrono>
#include <atomic>
#include "genetic.h"
#include <cmath>

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
    int a = 5*(*lst)[0]+5; /// |x|-|y|
    return a;
}

int main() {

    std::cout << "Function      K = 5X^2 + 3Y^2 + 7Z^2" << std::endl << std::flush;
    Genetic gen = Genetic(&func, 100, 1, 4);
    auto start = get_current_time_fenced();
    std::vector<int>* minim = gen.run();
    auto end = get_current_time_fenced();
    std::cout << "Minimum found      X = " << (*minim)[0]  << " Y = " << (*minim)[1]
//            <<" Z = " << (*minim)[2]<<" Z = " << (*minim)[3]<<" Z = " << (*minim)[4]
            <<std::endl;
    std::cout << "Time: " << to_us(end - start) << std::endl;
    return 0;
}