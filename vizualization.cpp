#include "vizualization.h"
#include "matplotlibcpp.h"
namespace plt = matplotlibcpp;

void visualization( int(*func)(std::vector<int>*), int n, std::vector<std::vector<int>*>* population){
    std::vector<int> x_array;
    std::vector<int> y_array;
    std::vector<int>* minim;
    int value1;
    int value2;
    for (int i = 0; i < population->size(); i++){
        minim  = (*population)[i];
        value1 = (*minim)[0];
        value2 = (*minim)[1];
        x_array.push_back(value1);
        y_array.push_back(value2);
    }
    std::map<std::string, std::string> colour({{"color", "red"}}) ;
    if (n == 3){
        std::vector<std::vector<int>> x, y, z;
        for (int i = -5; i <= 5;  i+= 1) {
            std::vector<int> x_row, y_row, z_row;
            for (int j = -5; j <= 5; j+=1) {
                x_row.push_back(i);
                y_row.push_back(j);
                auto* values = new std::vector<int>();
                values->push_back(i);
                values->push_back(j);
                auto result = func(values);
                z_row.push_back(result);
            }
            x.push_back(x_row);
            y.push_back(y_row);
            z.push_back(z_row);

        }
        plt::plot_surface(x, y, z);
    }
    else if(n == 2){
        std::vector<int> x ,y;
        for(int i=-5; i<5; i+= 1) {
            x.push_back(i);
            auto* values = new std::vector<int>();
            values->push_back(i);
            y.push_back(func(values));
        }
        plt::plot(x, y);
    }
    else{
        std::cout << "We can not visualize function with this amount of variables"<<std::endl;
    }
    plt::scatter(x_array, y_array, 10, colour) ;
    plt::show();
}
