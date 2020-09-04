#include <iostream>
#include "genetic.h"
#include "additional_functions.h"


int* Genetic::getNewChild(char* binary_p1, char* binary_p2){
    /**
      * @brief This function calls the right mating method by
      * the given index (initialized in constructor)
      *
      * @param binary_p1
      * char array of ciphered gene of the first parent
      * @param binary_p2
      * char array of ciphered gene of the second parent
   */
    char* child; // place for child in binary representation
    if (mating_method == 1){
        child = childSinglePoint(binary_p1, binary_p2);
    } if (mating_method == 2){
        child = childTwoPoints(binary_p1, binary_p2);
    } else {
        child = childSemirandomBit(binary_p1, binary_p2);
    }

    int* new_child = new int[n_variables]; // place for child in decimal point representation
    char gens[10];
    int amount_of_bits_in_one_variable = 10;
    int child_index = 0;
    for (int i = 1; i < n_variables + 1; i++){ // get the coordinates in binary representation
        for (int j = 0; j < amount_of_bits_in_one_variable; j++) {
            gens[j] = child[child_index];
            child_index++;
        }
        new_child[i-1] = binaryToDecimal(gens, 10); // converting binary to decimal
    }
    return new_child;
}


int* Genetic::mutation(int* individual) {
    /**
      * @brief This function calls the right mutation method by
      * the given index (initialized in constructor)
      *
      * @param individual
      * individual that should be mutated
   */
    if(mutation_method == 1){
        return gaussMutation(individual);
    }if(mutation_method == 2){
        return swapMutation(individual);
    }if(mutation_method == 3){
        return inversionMutation(individual);
    }else{
        return resetMutation(individual);
    }
}


int* Genetic::getParent(int* parents, int* results){
    /**
     * @brief This function calls the right selection method by
     * the given index (initialized in constructor)
     *
     * @param parents
     * int array - place for parents to be returned to
     *
     * @param results
     * int array - results according to which parents would be chosen
  */
    if (selection_method == 1){
        return getParentByFitness(parents, results);
    }if (selection_method == 2){
        return getParentsByRouletteWheel(parents, results);
    }else{
        return tournamentParent(parents, results);
    }
}