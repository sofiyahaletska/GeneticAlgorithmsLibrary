#include <iostream>
#include "genetic.h"

int func (std::vector<int>* lst){
    return (*lst)[0]*(*lst)[0]+(*lst)[1]*(*lst)[1]+(*lst)[2]*(*lst)[2]+(*lst)[3]*(*lst)[3];
}

int main() {
//    std::cout << "Hello, World!" << std::endl;
    Genetic gen = Genetic(&func, 100, 4);
    std::vector<int>* minim = gen.run();
    std::cout << "Minimum found      X =" << (*minim)[0] << ", Y =" << (*minim)[1] << ", Z =" << (*minim)[2] << ", K =" << (*minim)[3] <<std::endl;



    return 0;
}