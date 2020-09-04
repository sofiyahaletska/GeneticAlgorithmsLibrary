# Genetic Algorithms Library

## Team
Sophia Kravchuk, Julia Pochynok, Sophia Haletska

## Description
Library for optimizing multidimensional functions using genetic algorithms.


Genetic algorithms are search procedures based on the mechanisms of natural selection and inheritance. They use the evolutionary principle of survival of the most adapted individuals.

![](https://github.com/juliapochynok/GeneticAlgorithmsLibrary/blob/master/img/Screenshot%20from%202020-09-04%2010-55-37.png?raw=true)


Unlike most optimization algorithms, genetic algorithms do not use derivatives to find minimum. One of the most significant advantages of genetic algorithms is their ability to find the global minimum without focusing on local minimum. Randomness plays a significant role in the structure of genetic algorithms, and this is the main reason why genetic algorithms continue to search for search space.


## Library + Incoming and outgoing data

### Library
Our main function called find_minimum.
If you are not familiar with the parameters and capabilities of the find_minimum function, we suggest you read the documentation.


### Data
Receives an input function for optimization, GA parameters (population size, probability of mutations, etc.), way of parallelization(MPI, std::thread) and search for its minimum.


## Genetic Algorithms
Our genetic algorithm contains 7 parts:


Initialization - defining our population

Fitness Calculation - calculate the fitness value of gens using the given function

Selection - select part of individuals that will be contained in next generation

Pairing - select pairs of parents from our population which can mate and create their off-springs

Mating(Crossover) -  we have selected parent chromosomes that will produce off-springs. So in biological terms, the crossover is a reproduction, generating gens for off-springs.

Mutation - change in the genes of children which makes them different from their parents.

Constructing the next generation - combining earlier selected and newly made individuals to construct the nest generation


In our GA Pairing, Mating and Mutation can be performed by several different approaches - details in the picture. So in result of mixing approaches of different parts among them, our library contains not just one GA, but 36 different combinations of stages, that roughly speaking is 36 different GAs.

<img src="https://github.com/juliapochynok/GeneticAlgorithmsLibrary/blob/master/img/Screenshot%20from%202020-09-04%2010-59-09.png?raw=true" width="600">


Note: swap mutation and inversion mutation - for functions with a large number of variables

## Paralization

<img src="https://github.com/sophiakravchuk/GeneticAlgorithmsLibrary/blob/master/img/stages_mult_final.png" width="600" align="center">

In our project, we used two types of multithreading: std::thread and MPI.


Our parallelization consists of two parts, as it is shown in the image above. First of all, we are counting our resulting population in part Selection in threads. Also, the main process from Pairing to Mutation is held with pairs of individuals from the old population in multiple threads.

## Usage & Testing
While testing all 36 different GAs we found the most optimal and the least optimal combinations of stages.
We performed our testing on Goldstein-Price function, which is:

![](https://github.com/juliapochynok/GeneticAlgorithmsLibrary/blob/master/img/Screenshot%20from%202020-09-04%2021-57-20.png?raw=true)


For functions with a small number of variables the best combinations are:
0 -> 2 -> 0 

![](https://github.com/juliapochynok/GeneticAlgorithmsLibrary/blob/master/img/020.png?raw=true)

0 -> 0 -> 0 

![](https://github.com/juliapochynok/GeneticAlgorithmsLibrary/blob/master/img/000.png?raw=true)

For functions with a small number of variables the best combinations are:

0 -> 0 -> 2 

![](https://github.com/juliapochynok/GeneticAlgorithmsLibrary/blob/master/img/002.png?raw=true)

0 -> 0 -> 3 

![](https://github.com/juliapochynok/GeneticAlgorithmsLibrary/blob/master/img/003.png?raw=true)

The least optimal combinations are:
2 -> 0 -> 0 

![](https://github.com/juliapochynok/GeneticAlgorithmsLibrary/blob/master/img/200.png?raw=true)

1 -> 0 -> 1 

![](https://github.com/juliapochynok/GeneticAlgorithmsLibrary/blob/master/img/101.png?raw=true)


## Run Dependencies
To run the project you will need to download this repository and run command in command line. 


In order to use our project as a library you need:
1. Download the gal folder from this repository.
2. Place it in the directory with libraries on your device (ubuntu users have /usr/share)
3. In your project in Clion, create a folder named 'cmake'.
4. In the folder, create a file called 'FindGAL.cmake'
5. Copy the script below and paste into FindGAL.cmake, add your locations where requested(read text inside the stars, after inserting text, no stars should remain.)
```
set( FIND_GAL_PATHS *path to the gal folder (ubuntu users - /usr/share/gal)* )
 
find_path( GAL_INCLUDE_DIR find_minimum.h
           PATH_SUFFIXES include
           PATHS ${FIND_GAL_PATHS} )
find_library(GAL_LIBRARY
               NAMES gal
               PATH_SUFFIXES lib
               PATHS ${FIND_GAL_PATHS} )
 ```
6. Paste the script below in your Cmakelist.txt file between sets (CMAKE_CXX_STANDARD X(X reder to standard of c++ that you use) ) and add_executable( ... )
 
```
list(APPEND CMAKE_MODULE_PATH "${CMAKE_CURRENT_LIST_DIR}/cmake")
```
7. Paste the script below in your Cmakelist.txt file after add_executable( ... )
```
include(FindPkgConfig)
find_package(GAL REQUIRED)
include_directories(${GAL_INCLUDE_DIR})
target_link_libraries(${PROJECT_NAME} ${GAL_LIBRARY})

```
8.Make #include <find_minimum.h>

9.Call a function in your code with the appropriate parameters (find_global_min ())

## Documentation

	Genetic algorithms are search procedures based on the mechanisms of natural selection and inheritance.
    They use the evolutionary principle of survival of the most adapted individuals.This library is designed to
    find the global minimum of a function using the benefits of genetic algorithms and is optimized in two ways.
   

	This function takes all the necessary arguments and returns the global minimum of
    the function you specified.The parameters will be specified with default values
    if one does not pass them. The parameters that one can specify are as follows:
   
    @param type_of_parallelism
    This library supports two types of parallelization such as:
    MPI : 1
    std::threads : otherwise
    Accordingly, to select one of them,
    one should pass the value specified here opposite the corresponding method in the parameter.
    One should also make sure that one has all necessary libraries.
    The required argument type is int.
   
    @param function
    In this parameter one need to pass the function whose global minimum one want to find.
    The required argument type is int*.
   
    @param number_of_variables
    This parameter should specify the number of variables of the previously specified function.
    One should also make sure that one understand correctly what the function`s variables mean.
    Preferably the number of variables = dimension of the function - 1.
    The required argument type is int.
   
    @param amount_of_threads_or_cores
    With this parameter, one can set the number of threads or the number of cores that
    one wants to use for optimization.
    One also need to know that more threads will not always give better results and run faster.
    Unfortunately, everything has limitations.
    Equally important, if you choose MPI as a type of parallelization,
    you will not be able to set this parameter with a value that is higher
    than the number of cores on your device.
    Also, regarding the following parameters.
    If you plan to put a fairly small population_size,
    then a larger number of threads will not give you the desired acceleration in execution time.
    The required argument type is int.
   
    @param lower_limit
    The lower limit of the function.
    The required argument type is int.
   
    @param upper_limit
    The upper limit of the function.
    The required argument type is int.
   
    @param population_size
    A parameter that specifies the size of the population.
    The required argument type is int.
   
    @param selection_method
    This library supports three types of selection such as:
     ParentByFitness : 1
     ParentsByRouletteWheel : 2
     tournamentParents: otherwise
    Accordingly, to select one of them,
    one should pass the value specified here opposite the corresponding method in the parameter.
    The required argument type is int.
   
    @param mating_method
    This library supports three types of mating such as:
    childSinglePoint : 1
    childTwoPoints : 2
    childSemirandomBit : otherwise
    Accordingly, to select one of them,
    one should pass the value specified here opposite the corresponding method in the parameter.
    The required argument type is int.
   
    @param mutation_type
    This library supports four types of mutation such as:
    gaussMutation : 1
    swapMutation : 2
    inversionMutation : 3
    resetMutation : otherwise
    Accordingly, to select one of them,
    one should pass the value specified here opposite the corresponding method in the parameter.
    The required argument type is int.
   
    @param mutation_rate
    One can set the mutation_rate for a mutation.
    The required argument type is int.
   
    @param am_of_generations
    A parameter that determines the number of generations.
    The required argument type is int.
   
    @param standard_deviation
    One can set the standard deviation if one uses a Gaussian mutation.
     The required argument type is int.
   
    @return result
    variable type int which is the array where one can find parameters as follows:
    global minimum of the function that was specified
    values of variables in the global minimum.
  

