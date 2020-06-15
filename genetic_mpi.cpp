#include "genetic.h"
#include "additional_functions.h"
#include <iostream>

void Genetic::calcGeneration_mpi(int* children, int* results, int amount, int index){
    int children_index = index;
    while (amount > 0){
        std::cout << amount << std::endl;
        int* p1 = new int[n_variables];
        int* p2 = new int[n_variables];
        int* pars = new int[2*n_variables];
        int* parents;

        parents = getParent(pars, results);
        el1 = (el1 +1)%100;
        el2 = (el2 +1)%100;

        for (int i = 0; i < n_variables; i++){
            p1[i] = parents[i];
        }
        for (int i = 0; i < n_variables; i++){
            p2[i] = parents[i+n_variables];
        }

        int* signs = get_signs(p1, p2);

        char* binary_p1 = getCipher(p1);
        char* binary_p2 = getCipher(p2);

        int* new_child = new int[n_variables];


        new_child = getNewChild(binary_p1, binary_p2);

//        new_child = mutation(new_child);


//        for (int i = 0; i< n_variables; i++){
//            if (new_child[i] > maxim || new_child[i] < minim){
//                new_child[i] = getRand(minim, maxim);
//            }
//        }

        for(int i = 0; i < n_variables; i++){
            children[children_index] = new_child[i];
            children_index++;
            amount = amount-1;

        }
        delete binary_p1;
        delete binary_p2;
        delete signs;
//        amount--;
    }
}

