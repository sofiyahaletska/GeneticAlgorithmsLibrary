Завдання: Реалізувати бібліотеку оптимізації багатовимірних функцій за допомогою генетичних алгоритмів.

Опис: Бібліотека повинна отримувати на вхід функцію для оптимізації, параметри ГА (розмір популяції, ймовірність мутацій тощо)
та шукати її мінімум.

Багатовимірні функції  та їх мінімум

На перший погляд здається, що можна просто розв’язати цю систему алгебраїчних рівнянь і знайти екстремум функції. Але цей шлях приводить до екстремуму тільки у випадку гладкої квадратичної функції. 

В інших випадках внаслідок великого інтервалу пошуку та поганого початкового наближення, а також кривизни поверхні f(x,y) ми можемо не отримати розв’язку системи алгебраїчних рівнянь. Тому найчастіше використовуються ітераційні методи пошуку, коли ми наближаємось до точки мінімуму поступовими кроками, виконуючи на кожному кроці одні і ті ж дії – ітерації.

Генетичні алгоритми — це процедури пошуку, засновані на механізмах природного відбору і спадкоємства. У них використовується еволюційний принцип виживання найбільш пристосованих особин. 

1.обробляють не значення параметрів самого завдання, а їх закодовану форму;

2.здійснюють пошук рішення виходячи не з єдиної точки, а з їх деякої популяції;

3.використовують тільки цільову функцію, а не її похідні або іншу додаткову інфор3.мацію;

4.застосовують імовірнісні, а не детерміновані правила вибору.

Використання мінімуму інформації про завдання і рандомізація операцій приводять у результаті до стійкості генетичних алгоритмів і до їх переваги над іншими широко вживаними технологіями.

На відміну від більшості алгоритмів оптимізації, генетичні алгоритми не використовують похідні для пошуку мінімумів. Однією з найбільш значущих переваг генетичних алгоритмів є їх здатність знаходити глобальний мінімум, не зациклюючись на локальних мінімумах. Випадковість відіграє істотну роль у структурі генетичних алгоритмів, і це головна причина, по якій генетичні алгоритми продовжують шукати простір пошуку.

Що ми вже зробили?

Знайшли багато корисної літератури і зрозуміли принцип роботи генетичних алгоритмів
Реалізували один генетичний алгоритм на С++, який шукає мінімум функції
Обговорювали, які методи розпаралелювання ми можемо використати у написаному послідовному алгоритмі

Що ми плануємо робити далі?

Вдосконалення ГА:
реалізувати стадії відбору, парування, злиття і мутації різними способами (рулеткове колесо, найпристосованіша частина і тд)
протестувати різні критерії припинення і обрати найкращий


Вдосконалення розпаралелення:
розпаралелити наш теперішній код
реалізувати розпаралелення іншим способом


організувати наявний код в бібліотеку, написати документацію та тести до неї


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
  

