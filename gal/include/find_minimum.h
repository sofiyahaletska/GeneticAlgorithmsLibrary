#ifndef GAL_FIND_MINIMUM_H
#define GAL_FIND_MINIMUM_H
int* find_global_min(int type_of_parallelism = 0, int (*f)(int values[])=nullptr, int number_of_variables=1,
                     int amount_of_threads_or_cores=1, int lower_limit=-100, int upper_limit=100, int population_size=1000000,
                     int selection_method=0, int mating_method=0, int mutation_type=0, int mutation_rate=1,
                     int standard_deviation=2, int am_of_generations=1000);
/**
   * @brief Genetic algorithms are search procedures based on the mechanisms of natural selection and inheritance.
   * They use the evolutionary principle of survival of the most adapted individuals.This library is designed to
   * find the global minimum of a function using the benefits of genetic algorithms and is optimized in two ways.
   */

/**
   * @brief This function takes all the necessary arguments and returns the global minimum of
   * the function you specified.The parameters will be specified with default values
   * if one does not pass them. The parameters that one can specify are as follows:
   *
   * @param type_of_parallelism
   * This library supports two types of parallelization such as:
   * MPI : 1
   * std::threads : otherwise
   * Accordingly, to select one of them,
   * one should pass the value specified here opposite the corresponding method in the parameter.
   * One should also make sure that one has all necessary libraries.
   * The required argument type is int.
   *
   * @param function
   * In this parameter one need to pass the function whose global minimum one want to find.
   * The required argument type is int*.
   *
   * @param number_of_variables
   * This parameter should specify the number of variables of the previously specified function.
   * One should also make sure that one understand correctly what the function`s variables mean.
   * Preferably the number of variables = dimension of the function - 1.
   * The required argument type is int.
   *
   * @param amount_of_threads_or_cores
   * With this parameter, one can set the number of threads or the number of cores that
   * one wants to use for optimization.
   * One also need to know that more threads will not always give better results and run faster.
   * Unfortunately, everything has limitations.
   * Equally important, if you choose MPI as a type of parallelization,
   * you will not be able to set this parameter with a value that is higher
   * than the number of cores on your device.
   * Also, regarding the following parameters.
   * If you plan to put a fairly small population_size,
   * then a larger number of threads will not give you the desired acceleration in execution time.
   * The required argument type is int.
   *
   * @param lower_limit
   * The lower limit of the function.
   * The required argument type is int.
   *
   * @param upper_limit
   * The upper limit of the function.
   * The required argument type is int.
   *
   * @param population_size
   * A parameter that specifies the size of the population.
   * The required argument type is int.
   *
   * @param selection_method
   * This library supports three types of selection such as:
   *  ParentByFitness : 1
   *  ParentsByRouletteWheel : 2
   *  tournamentParents: otherwise
   * Accordingly, to select one of them,
   * one should pass the value specified here opposite the corresponding method in the parameter.
   * The required argument type is int.
   *
   * @param mating_method
   * This library supports three types of mating such as:
   * childSinglePoint : 1
   * childTwoPoints : 2
   * childSemirandomBit : otherwise
   * Accordingly, to select one of them,
   * one should pass the value specified here opposite the corresponding method in the parameter.
   * The required argument type is int.
   *
   * @param mutation_type
   * This library supports four types of mutation such as:
   * gaussMutation : 1
   * swapMutation : 2
   * inversionMutation : 3
   * resetMutation : otherwise
   * Accordingly, to select one of them,
   * one should pass the value specified here opposite the corresponding method in the parameter.
   * The required argument type is int.
   *
   * @param mutation_rate
   * One can set the mutation_rate for a mutation.
   * The required argument type is int.
   *
   * @param am_of_generations
   * A parameter that determines the number of generations.
   * The required argument type is int.
   *
   * @param standard_deviation
   * One can set the standard deviation if one uses a Gaussian mutation.
   * * The required argument type is int.
   *
   * @return result
   * variable type int* which is the array where one can find parameters as follows:
   * global minimum of the function that was specified
   * values of variables in the global minimum.
   */
#endif //GAL_FIND_MINIMUM_H
