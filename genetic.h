#ifndef PROJECT_CPP_GENETIC_H
#define PROJECT_CPP_GENETIC_H
#include <vector>
#include <random>
#include <algorithm>
#include <bitset>
#include <mutex>

int binaryToDecimal(char* n, int len);
int findElementIndex(int arr[], int n, int el);
int findSmallestElement(int arr[], int n);

class Genetic{
public:
    Genetic(int (*f)(int values[]), int n_variables, int pop_size=100,
            int am_threads=1, int selection_method=0, int mating_method=0, int mutation_method=0,
            int lower_limit=-100, int upper_limit=100, int mutation_rate=1, int standard_deviation=2,
            int am_of_generations=1000);

    Genetic(Genetic const &genetic);

    int* run();

    int selection_method;
    int mating_method;
    int mutation_method;
    int (*f)(int values[]);
    int minim;
    int maxim;
    int pop_size;
    int n_variables;
    int am_of_threads;
    int* population;
    int mutation_rate;
    int standard_deviation;
    int am_of_generations;

    void calcGeneration_mpi(int* children, int* results, int amount, int index);

    std::default_random_engine generator{std::random_device{}()};
    mutable std::mutex m_m;
    int* getParent(int* parents, int* results);

    int el1 = 0;
    int el2 = 1;

    int* initializePopulation(int* pop);
    char* getCipher(int* parent);
    int* getParentByFitness(int* parents, int* results);
    char* childSinglePoint(char* binary_p1, char* binary_p2);

    char* childSemirandomBit(char* binary_p1, char* binary_p2);
    int* getResults();
    int* getParentsByRouletteWheel(int* parents, const int* results);
    void evaluatePopulation(int* pop, int start, int end, int *res);
    void calcGeneration(int* results, int amount, int*  children, int displs);
    char* childTwoPoints(const char* binary_p1, const char* binary_p2);
    void next_gen();
    int* mutation(int* individual);
    int getRand(int start, int end);

    int* resetMutation(int* individual);
    int* gaussMutation(int *individual);

    int* randomParents(int* parents, const int* results);
    int* get_signs(const int* p1, const int* p2);
    int* getNewChild(char* binary_p1, char* binary_p2, int* signs);

    int* swapMutation(int* individual);
    int* inversionMutation(int* individual);

};


#endif //PROJECT_CPP_GENETIC_H
