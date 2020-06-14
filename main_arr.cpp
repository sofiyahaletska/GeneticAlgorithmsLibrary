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


int main() {

    std::cout << "Function      K = x^2 + 2*x" << std::endl << std::flush;

    Genetic gen = Genetic(&func, 100, 1, 4);

    auto start = get_current_time_fenced();

    std::vector<int>* minim = gen.run();

    auto end = get_current_time_fenced();

    std::cout << "Time: " << to_us(end - start) << std::endl;
    return 0;
}
