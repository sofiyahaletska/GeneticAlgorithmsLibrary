#ifndef GAL_FIND_MINIMUM_H
#define GAL_FIND_MINIMUM_H
int* find_global_min(int type_of_parallelism = 0, int (*f)(int values[])=nullptr, int number_of_variables=1,
                     int amount_of_threads_or_cores=1, int lower_limit=-100, int upper_limit=100, int population_size=100,
                     int selection_method=0, int mating_method=0, int mutation_type=0, int mutation_rate=1,
                     int standard_deviation=2, int am_of_generations=1000);
#endif //GAL_FIND_MINIMUM_H
