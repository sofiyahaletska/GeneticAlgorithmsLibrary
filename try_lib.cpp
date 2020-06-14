#include <iostream>
#include <chrono>
#include <atomic>
#include "find_minimum.h"

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
    int* minim = find_global_min(1, nullptr, 1,4);
    std:: cout << to_us(get_current_time_fenced() - start) << std::endl;
    std::cout << "Function      K = x^2 + 2*x" << std::endl << std::flush;
    std::cout << "Minimum found      X = " << minim[1] << std::endl;
    std::cout << "F(x) = " << minim[0] << std::endl;
    return 0;
}
