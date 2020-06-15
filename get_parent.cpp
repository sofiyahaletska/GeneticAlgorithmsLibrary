#include <iostream>
#include "genetic.h"
#include "additional_functions.h"

int* Genetic::getParentByFitness(int* parents, int* results){
<<<<<<< HEAD
    /**
=======
     /**
>>>>>>> 8badea96779bd60a17738de0f0be4d586bc938d3
       * @brief This function perform selection of parent pairs according to
       * their fitness. As the fittest individual will be paired with the fittest
       *
       * @param parents
       * variable(place) where selected parents will be placed
       * @param results
       * results of fitness values for every parent
    */
    int cum_sum[pop_size];
    for (int i = 0; i < pop_size; i++) { // getting fitness values
        int a = results[i];
        cum_sum[i] = a;
    }
    std::sort(cum_sum, cum_sum+pop_size); // sorting fitness values

    // finding indexes of parents
    int ind1 = findElementIndex(results, pop_size, cum_sum[el1]);
    int ind2 = findElementIndex(results, pop_size, cum_sum[el2]);

    // forming parents
    for (int i=0; i < n_variables; i++){
        parents[i] = population[ind1*n_variables+i];
        parents[i+n_variables] = population[ind2*n_variables+i];
    }
    return parents;
}


int* Genetic::tournamentParent(int *parents, const int *results) {
    /**
   * @brief This function perform selection of parent pairs by choosing 2 random parents
     * from all and choosing the fittest of them
   *
   * @param parents
   * variable(place) where selected parents will be placed
   * @param results
   * results of fitness values for every parent
    */
    for (int i = 0; i < 2; i++) {
        int randA1 = getRand(0, pop_size - 1); //choosing first random parent
        int randB1 = getRand(0, pop_size - 1); //choosing second random parent
        if (results[randA1] < results[randB1]) { //select fitter parent
            for (int j = 0; j < n_variables; j++) {
                parents[j+i*n_variables] = population[randA1 * n_variables + j];
            }
        } else {
            for (int j = 0; j < n_variables; j++) {
                parents[j+i*n_variables] = population[randB1 * n_variables + j];
            }
        }
    }
    return parents;
}


int* Genetic::getParentsByRouletteWheel(int* parents, const int* results){
    /**
    * @brief This function perform selection of parent pairs acoording to roulette wheel selection.
    * It "forms" a roulette wheel from parents' fitness values so that probability of being chosen is higher
    * if fitness value is higher
    *
    * @param parents
    * variable(place) where selected parents will be placed
    * @param results
    * results of fitness values for every parent
    */
    int eval_sum = 0;
    int cum_sum[pop_size];
    for (int i = 0; i < pop_size; i++)  { // calculating cumulative sum of fitness values
        int a = results[i];
        cum_sum[i] = a;
        eval_sum += a;
    }
    // sort fitness values
    std::sort(cum_sum, cum_sum+pop_size);

    // perform roulette wheel - choosing first parent
    int curr_sum1 = getRand(0, eval_sum);
    int individual_ind = 0;
    int max_am_loops = 0;
    while(curr_sum1 < eval_sum && max_am_loops < 100) {
        int curr_ind1 = pop_size- 1 - (individual_ind % pop_size);
        curr_sum1 += results[curr_ind1];
        individual_ind++;
        max_am_loops++;
    }
    int ind1 = ((pop_size- 1 - (individual_ind % pop_size))%pop_size)*n_variables;

    // perform roulette wheel - choosing second parent
    int curr_sum2 = getRand(0, eval_sum);
    max_am_loops = 0;
    int individual_ind2 = 0;
    while(curr_sum2 < eval_sum && max_am_loops < 100) {
        int curr_ind2 = pop_size- 1 - (individual_ind % pop_size);
        curr_sum2 += results[curr_ind2];
        individual_ind++;
        max_am_loops++;
    }
    int ind2 = ((pop_size- 1 - (individual_ind2 % pop_size))%pop_size)*n_variables;

    // forming parents
    for (int i=0; i < n_variables; i++){
        parents[i] = population[ind1*n_variables+i];
        parents[i+n_variables] = population[ind2*n_variables+i];
    }
    return parents;
}
