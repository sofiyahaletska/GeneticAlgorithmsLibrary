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
    Genetic(int (*f)(int values[]), int pop_size, int n_variables, int am_threads);

    Genetic(Genetic const &genetic);

    std::vector<int>* run();

    int (*f)(int values[]);
    int minim;
    int maxim;
    int pop_size;
    int n_variables;
    int am_of_threads;
    int* population;
    void calcGeneration_mpi(int* children, int* results, int amount, int index);

    std::default_random_engine generator{std::random_device{}()};
    mutable std::mutex m_m;
    int* getParent(int* parents, int* results, int method=0);
    std::vector<int>* getNewChild(std::vector<std::string>* binary_p1, std::vector<std::string>* binary_p2, std::vector<int>* signs, int method=0);

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
    char* childTwoPoints(char* binary_p1, char* binary_p2);
    void next_gen();
    int* mutation(int* individual, int upper_limit, int lower_limit,
                               int method=0, int muatation_rate=2, double standard_deviation=0.001);
    int getRand(int start, int end);

    int* resetMutation(int* individual, int lower_limit, int upper_limit, int muatation_rate=2);
    int* gaussMutation(int *individual, int lower_limit, int upper_limit,
            int muatation_rate=2, double standard_deviation=0.001);

    int* randomParents(int* parents, const int* results);
    int* get_signs(const int* p1, const int* p2);
    int* getNewChild(char* binary_p1, char* binary_p2, int* signs, int method);

    int* swapMutation(int* individual);
    int* inversionMutation(int* individual);

};


#endif //PROJECT_CPP_GENETIC_H
