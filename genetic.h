#ifndef PROJECT_CPP_GENETIC_H
#define PROJECT_CPP_GENETIC_H
#include <vector>
#include <random>
#include <algorithm>
#include <bitset>
#include <mutex>

class Genetic{
public:
    Genetic(int (*f)(std::vector<int>* values), int pop_size, int n_variables, int am_threads);

    Genetic(Genetic const &genetic);

    std::vector<int>* run();

    int (*f)(std::vector<int>* values);
    int minim;
    int maxim;
    int pop_size;
    int n_variables;
    int am_of_threads;
    std::vector<std::vector<int>*>* population;
    std::default_random_engine generator;
    mutable std::mutex m_m;
    std::vector<std::vector<int>*>* getParent(std::vector<int>* results, int method=0);
    std::vector<int>* getNewChild(std::vector<std::string>* binary_p1, std::vector<std::string>* binary_p2, std::vector<int>* signs, int method=0);

private:
    int el1 = 0;
    int el2 = 1;
    std::vector<std::string>* getCipher(std::vector<int>* parent);
    std::vector<std::vector<int>*>* getParentByFitness(std::vector<int>* results);
    std::vector<std::string>* childSinglePoint(std::vector<std::string>* binary_p1, std::vector<std::string>* binary_p2);
    std::vector<std::string>* childSemirandomBit(std::vector<std::string>* binary_p1, std::vector<std::string>* binary_p2);
    std::vector<int>* getResults();
    std::vector<std::vector<int>*>* initializePopulation();
    std::vector<int>* evaluatePopulation(int start, int end, std::vector<int> *res);
    void calcGeneration(std::vector<std::vector<int>*>* children, std::vector<int>* results);
    void next_gen();
    std::vector<int>* mutation(std::vector<int>* individual, int upper_limit, int lower_limit,
                               int method=0, int muatation_rate=2, double standard_deviation=0.001);
    int getRand(int start, int end);

    std::vector<int>* resetMutation(std::vector<int> *individual,
                                             int lower_limit, int upper_limit, int muatation_rate=2);
    std::vector<int>* gaussMutation(std::vector<int> *individual,
                                    int lower_limit, int upper_limit, int muatation_rate=2, double standard_deviation=0.001);

    std::vector<std::vector<int>*>* randomParents(std::vector<int>* results);
    std::vector<int>* get_signs(std::vector<int>* p1, std::vector<int>* p2);
    std::vector<int> * getNewChild(std::vector<std::string>* binary_p1, std::vector<std::string>* binary_p2, std::vector<int>* signs);
};


#endif //PROJECT_CPP_GENETIC_H
