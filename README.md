# Genetic Algorithms Library

## Description
Library for optimizing multidimensional functions using genetic algorithms.

Genetic algorithms are search procedures based on the mechanisms of natural selection and inheritance. They use the evolutionary principle of survival of the most adapted individuals.

КАРТИНКАААААААААААААААААААААААААААААААААААААААААААААА

Unlike most optimization algorithms, genetic algorithms do not use derivatives to find minimum. One of the most significant advantages of genetic algorithms is their ability to find the global minimum without focusing on local minimum. Randomness plays a significant role in the structure of genetic algorithms, and this is the main reason why genetic algorithms continue to search for search space.


## Library + Incoming and outgoing data
### Data
Receives an input function for optimization, GA parameters (population size, probability of mutations, etc.), way of parallelization(MPI, std::thread) and search for its minimum.

### Library

## Genetic Algorithms
Our genetic algorithm contains 7 parts:
Initialization - defining our population
Fitness Calculation - calculate the fitness value of gens using the given function
Selection - select part of individuals that will be contained in next generation
Pairing - select pairs of parents from our population which can mate and create their off-springs
Mating(Crossover) -  we have selected parent chromosomes that will produce off-springs. So in biological terms, the crossover is a reproduction, generating gens for off-springs.
Mutation - change in the genes of children which makes them different from their parents.
Constructing the next generation - combining earlier selected and newly made individuals to construct the nest generation

In our GA Pairing, Mating and Mutation can be performed by several different approaches - details in the picture. So in result of mixing approaches of different parts among them, our library contains not just one GA, but 32 different combinations of stages, that roughly speaking is 32 different GAs.

КАРТИНКААААААААААААААААААААААААААААААААААААААААААААААААААААААААААААААААААААААААААААААААААААААААААААААААААААААААААААААААААААААААААААААА
Note: swap mutation and inversion mutation - for functions with a large number of variables

## Paralization


## Usage Example/Testing


## Run Dependencies
To run the project you will need to download this repository and run command in command line. 


## Documentation

## Team
Sophia Kravchuk, Julia Pochynok, Sophia Haletska

