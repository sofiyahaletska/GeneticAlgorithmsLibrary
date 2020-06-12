#include <iostream>
#include <chrono>
#include <atomic>
#include <cmath>
#include "genetic.h"
#include "vizualization.h"
#include <mpi.h>

std::chrono::high_resolution_clock::time_point get_current_time_fenced()
{
    std::atomic_thread_fence(std::memory_order_seq_cst);
    auto res_time = std::chrono::high_resolution_clock::now();
    std::atomic_thread_fence(std::memory_order_seq_cst);
    return res_time;
}

template<class D>
long long to_us(const D& d)
{
    return std::chrono::duration_cast<std::chrono::microseconds>(d).count();
}


int func (int* lst){
    int a = pow(lst[0], 2) + 2*lst[0]; /// x^4 - 4^x
    return a;
}

int main(int argc, char** argv) {
    int commsize, rank, len;
    char procname[MPI_MAX_PROCESSOR_NAME];
    MPI_Init(&argc, &argv);
    MPI_Comm_size(MPI_COMM_WORLD, &commsize);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Get_processor_name(procname, &len);
    int *scount = new int[commsize - 1];
    int am_of_gens = 0;
    Genetic gen;
    gen.construct(&func, 100, 1, 4);
    int* results = new int[gen.pop_size];
    int* children = new int[gen.pop_size*gen.n_variables];

    int* popul = new int[gen.pop_size*gen.n_variables];

    while (am_of_gens < 1000) {
        if (rank == 0) {
            if (am_of_gens == 0) {
                std::cout << "Function      K = x^2 + 2*x" << std::endl << std::flush;

                int part = gen.pop_size/ (commsize - 1);
                for (int i = 0; i < (commsize - 1); i++) {
                    int end = part * gen.n_variables*(i + 1);
                    if (i == (commsize - 2)) {
                        end = gen.pop_size*gen.n_variables;
                    }
                    scount[i] = end - part*gen.n_variables * i;
                }
            }
        }

        if (am_of_gens == 0) {
            MPI_Bcast(scount, (commsize - 1), MPI_INT, 0, MPI_COMM_WORLD);
        }

        if (rank == 0) {
            int* copy_pop = new int[gen.pop_size*gen.n_variables];
            for (int i = 0; i < gen.pop_size*gen.n_variables; i++){
                copy_pop[i] = gen.population[i];
            }
            for (int j = 0; j < (commsize - 1); j++) {
                MPI_Send(copy_pop, scount[j], MPI_INT,
                         j+1, 0, MPI_COMM_WORLD);
                copy_pop = copy_pop + scount[j];
            }
        }

        int* part_of_population = new int[scount[rank - 1]];

        if (rank != 0) {
            MPI_Recv(part_of_population, scount[rank - 1], MPI_INT,
                     0, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);

            int* res = new int[scount[rank - 1]/gen.n_variables];
            gen.evaluatePopulation(part_of_population, 0, scount[rank - 1]/gen.n_variables, res);

            MPI_Send(res, scount[rank - 1]/gen.n_variables, MPI_INT,
                     0, 0, MPI_COMM_WORLD);
        }

        if (rank == 0){

            int results_index = 0;
            for (int i = 0; i < commsize -1; i++){
                int* part_res = new int[scount[i]/gen.n_variables];
                MPI_Recv(part_res, scount[i]/gen.n_variables, MPI_INT,
                         i+1, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
                for (int j = 0; j < scount[i]/gen.n_variables; j++){
                    results[results_index] = part_res[j];
                    results_index++;
                }
            }

            int index = findSmallestElement(results, gen.pop_size);

            for (int i = 0; i < gen.n_variables; i++){
                children[i] = gen.population[index*gen.n_variables+i];
            }
        }
        MPI_Bcast(popul, gen.pop_size*gen.n_variables, MPI_INT, 0, MPI_COMM_WORLD);
        gen.population = popul;
        MPI_Bcast(results, gen.pop_size, MPI_INT, 0, MPI_COMM_WORLD);

        if (rank != 0){
            int size;
            if (rank == 1){
                size = scount[rank -1]-1;
            }else {
                size = scount[rank -1];
            }
            int *childs = new int[size];
            gen.calcGeneration(childs, results, size / gen.n_variables);
            MPI_Send(childs, size, MPI_INT, 0, 0, MPI_COMM_WORLD);
        }

        if (rank == 0) {
            int new_pop_index = 1;
            for (int i = 0; i < commsize - 1; i++) {
                int size;
                if (i == 0) {
                    size = scount[i] - 1;
                } else {
                    size = scount[i];
                }

                int *part_children = new int[size];
                MPI_Recv(part_children, size, MPI_INT,
                         i + 1, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
                for (int j = 0; j < size; j++) {
                    children[new_pop_index] = part_children[j];
                    new_pop_index++;
                }
            }
//            int index = findSmallestElement(results, gen.pop_size);
//
//            for (int i = 0; i < gen.n_variables; i++){
//                int x;
//                x = children[i];
//                children[i] = children[index*gen.n_variables+i];
//                children[index*gen.n_variables+i] = x;
//            }
//            std::sort(children, children+gen.pop_size);
            gen.population = children;
//            std::cout << "pop       = ";
//            for (int j = 0; j < gen.pop_size*gen.n_variables; j++) {
//                std::cout << gen.population[j]  << " ";
//            }
//            std::cout <<std::endl;
        }
        am_of_gens++;

    }
    if (rank == 0) {
        auto *res = new std::vector<int>();
        for (int j = 0; j < gen.n_variables; j++) {
            res->push_back(gen.population[j]);
        }
        std::cout << "Minimum found      X = " << (*res)[0]  <<std::endl;
    }

    MPI_Finalize();
    return 0;
}