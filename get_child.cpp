#include <iostream>
#include "genetic.h"

char* Genetic::childSinglePoint(const char* binary_p1, const char* binary_p2) const{
    /**
       * @brief This function perform mating of parent pairs by dividing
       * their ciphered genes in one point
       *
       * @param binary_p1
       * char array of ciphered gene of the first parent
       * @param binary_p2
       * char array of ciphered gene of the second parent
    */
    char* child = new char[10*n_variables]; // creating the place for resulted child
    for(int i = 0; i < n_variables; i++){
        for(int j = 0; j < 5; j++) {

            child[j+i*10] = binary_p1[(i*10)+j]; // adding first part of genome from first parent
        }
        for(int l = 5; l < 10; l++) {
            child[l+i*10] = binary_p2[(i*10)+l]; // adding second part of genome from second parent
        }
    }
    return child;
}

char* Genetic::childSemirandomBit(const char* binary_p1, const char* binary_p2){
    /**
       * @brief This function perform mating of parent pairs by copying
       * the same gene-bits of the parents and adding the random bit where
       * parents have different ones.
       *
       * @param binary_p1
       * char array of ciphered gene of the first parent
       * @param binary_p2
       * char array of ciphered gene of the second parent
    */
    char* child = new char[10*n_variables]; // creating the place for resulted child
    for(int i = 0; i < 10*n_variables; i++){

        if (binary_p1[i] == binary_p2[i]){ // copying the same gene-bits of the parents
            child[i] = binary_p2[i];
        } else { // adding the random bit where parents have different ones
            int r = getRand(0, 1);
            std::string str_rand = std::bitset<1>(abs(r)).to_string();
            child[i] = str_rand[0];
        }
    }
    return child;
}

char* Genetic::childTwoPoints(const char* binary_p1, const char* binary_p2) const{
    /**
       * @brief This function perform mating of parent pairs by dividing
       * their ciphered genes by two points.
       *
       * @param binary_p1
       * char array of ciphered gene of the first parent
       * @param binary_p2
       * char array of ciphered gene of the second parent
    */
    char* child = new char[10*n_variables]; // creating the place for resulted child
    for(int i = 0; i < n_variables; i++){
        for(int j = 0; j < 2; j++) {
            child[j+i*10] = binary_p1[(i*10)+j]; // adding first part of genome from first parent
        }
        for(int l = 2; l < 7; l++) {
            child[l+i*10] = binary_p2[(i*10)+l]; // adding second part of genome from second parent
        }
        for(int r = 7; r < 10; r++) {
            child[r+i*10] = binary_p1[(i*10)+r]; // adding second part of genome from first parent
        }
    }
    return child;
}