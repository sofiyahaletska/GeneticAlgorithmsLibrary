/**
     * This file is for you to try out how our library works.
     * If one does not pass any parameters in find_global_min,
     * it will call the function that is in the file function_to_calc.
     * So if one wants to find the minimum of the specific function,
     * then one need to edit the function func in a file function_to_calc,
     * also this is the only way one can pass the function if one passes MPI as a type of parallelization.
     */

#include <iostream>
#include <chrono>
#include <atomic>
#include "find_minimum.h"
#include "function_to_calc.h"



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


int main() {
    auto start = get_current_time_fenced();
    int *minim;

    minim = find_global_min(1, &Goldenstein_Price_func, 2, 1, -2, 2, 100);

    std:: cout << to_us(get_current_time_fenced() - start) << std::endl;
    std::cout << "Function      K = x^2 + 2*x" << std::endl << std::flush;
    std::cout << "Minimum found      X = " << minim[1] << std::endl;
    std::cout << "F(x) = " << minim[0] << std::endl;
    return 0;
}
