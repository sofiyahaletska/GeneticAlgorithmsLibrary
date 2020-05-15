#include "vizualization.h"
#include "matplotlibcpp.h"
namespace plt = matplotlibcpp;

void visualization( double(*func)(std::vector<double>*), int n){
    if (n == 3){
        std::vector<std::vector<double>> x, y, z;
        for (double i = -5; i <= 5;  i+= 0.25) {
            std::vector<double> x_row, y_row, z_row;
            for (double j = -5; j <= 5; j+=0.25) {
                x_row.push_back(i);
                y_row.push_back(j);
                auto* values = new std::vector<double>();
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
        std::vector<double> x ,y;
        for(double i=-5; i<5; i+= 0.25) {
            x.push_back(i);
            auto* values = new std::vector<double>();
            values->push_back(i);

            y.push_back(func(values));
        }
        plt::plot(x, y);

    }
    else{
        std::cout << "We can not visualize function with this amount of variables"<<std::endl;
    }
    plt::show();
}

