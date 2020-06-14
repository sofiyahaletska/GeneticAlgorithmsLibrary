#include <iostream>
#include "genetic.h"

char* Genetic::childSinglePoint(char* binary_p1, char* binary_p2){
    char* child = new char[10*n_variables];
    for(int i = 0; i < n_variables; i++){
        for(int j = 0; j < 5; j++) {

            child[j+i*10] = binary_p1[(i*10)+j];
        }
        for(int l = 5; l < 10; l++) {
            child[l+i*10] = binary_p2[(i*10)+l];
        }
    }
    return child;
}

char* Genetic::childSemirandomBit(char* binary_p1, char* binary_p2){
    char* child = new char[10*n_variables];
//    std::cout << binary_p1 << std::endl;
//    std::cout << binary_p2 << std::endl;
    for(int i = 0; i < 10*n_variables; i++){

        if (binary_p1[i] == binary_p2[i]){
            child[i] = binary_p2[i];
        } else {
            int r = getRand(0, 1);
            std::string str_rand = std::bitset<1>(abs(r)).to_string();
            child[i] = str_rand[0];
        }
    }
//    std::cout << child << std::endl;
    return child;
}

char* Genetic::childTwoPoints(const char* binary_p1, const char* binary_p2){
    char* child = new char[10*n_variables];
    for(int i = 0; i < n_variables; i++){
        for(int j = 0; j < 2; j++) {
            child[j+i*10] = binary_p1[(i*10)+j];
        }
        for(int l = 2; l < 7; l++) {
            child[l+i*10] = binary_p2[(i*10)+l];
        }
        for(int r = 7; r < 10; r++) {
            child[r+i*10] = binary_p1[(i*10)+r];
        }
    }
    return child;
}