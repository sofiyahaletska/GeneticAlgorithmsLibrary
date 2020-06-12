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
    Genetic();

    void construct(int (*func)(int values[]), int size_of_p = 100, int n_vars = 2, int am_threads=4);
    std::vector<int>* run();

    int (*f)(int values[]);
    int minim;
    int maxim;
    int pop_size;
    int n_variables;
    int am_of_threads;

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
    int* getResults(int* res);

    void evaluatePopulation(int* pop, int start, int end, int *res);
    void calcGeneration(int* children, int* results, int amount);
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


    int* population;
};


#endif //PROJECT_CPP_GENETIC_H
