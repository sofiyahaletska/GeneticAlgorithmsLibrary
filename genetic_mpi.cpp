#include "genetic.h"


void Genetic::calcGeneration_mpi(int* children, int* results, int amount, int index){
    /**
   * @brief This function is private and used in our library to calculate the generation when one is using
   * MPI as a type of parallelization.
   * In this function selection of parents, children making and mutation are called.
   * The function has parameters as follows:
   *
   * @param children
   *This is a buffer that is passed to the function as a parameter,
   *and as a result of the function it will be filled with a new generation.
   * The required argument type is int*.
   *
   * @param results
   * This is a buffer with the results of calculating the function at certain points,
   * which was calculated in the previous step, to be more precise, in the function evaluatePopulation.
   * The required argument type is int*.
   *
   * @param amount
   * This is a parameter that determines how many children you need to create.
   * The required argument type is int.
   *
   * @param index
   * This parameter tells from which index in the results starts the results we are interested in.
   * It also points the index from which to begin writing to the children buffer.
   * The required argument type is int.
   *
   */
    int children_index = index;
    // The cycle of creating children starts here
    while (amount){
        //Initialization of subbuffers required in the creation process
        int* p1 = new int[n_variables];
        int* p2 = new int[n_variables];
        int* pars = new int[2*n_variables];
        int* parents;

         // Selection of the parents
        parents = getParent(pars, results);
        //Initialization of additional variables required in the mutation
        el1 = (el1 +1)%100;
        el2 = (el2 +1)%100;

        for (int i = 0; i < n_variables; i++){
            p1[i] = parents[i];
        }
        for (int i = 0; i < n_variables; i++){
            p2[i] = parents[i+n_variables];
        }
        // Selecting the sign for child
        int* signs = get_signs(p1, p2);
        
        //Convert numbers to binary form.
        // Preparation for the next stage.
        char* binary_p1 = getCipher(p1);
        char* binary_p2 = getCipher(p2);

        // Creating a child
        int* new_child = getNewChild(binary_p1, binary_p2, signs);
        // Mutation occurs over a set of a child's genes
        new_child = mutation(new_child);

        //Check whether the child is within the function boundaries,
        // if no - transformation happens
        for (int i = 0; i< n_variables; i++){
            if (new_child[i] > maxim || new_child[i] < minim){
                new_child[i] = getRand(minim, maxim);
            }
        }
        // The child is added in the new generation buffer(children)
        for(int i = 0; i < n_variables; i++){
            children[children_index] = new_child[i];
            children_index++;
        }
         //Additional variables used during this function are deleted.
        delete binary_p1;
        delete binary_p2;
        delete signs;
        // The number of children to be made is reduced to continue the cycle or complete it
        // if the required amount has already been created
        amount--;
    }
}

