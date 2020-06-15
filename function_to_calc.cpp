#include <cmath>
#include <cmath>
#include <vector>

int func (int* lst){
//    int a = pow(lst[0], 2) + lst[0]*2; /// x^2 + 2*x
    int a = pow(lst[0], 2) + pow(lst[1], 2)+ pow(lst[2], 2)+ pow(lst[3], 2); /// x^2 + 2*x
    return a;
}

int Goldenstein_Price_func (int* lst){
    int a = (1+pow(lst[0]+lst[1]+1,2)*(19-14*lst[0]+3*pow(lst[0],2)-14*lst[1]+6*lst[0]*lst[1]+
            3*pow(lst[1],2)))*(30+pow(2*lst[0]-3*lst[1],2)*(18-32*lst[0]+12*pow(lst[0],2)+
                    48*lst[1]-36*lst[0]*lst[1]+27*pow(lst[1],2)));
    return a;
}

int Shekel_7_func (int* lst) {
    double res=0;
    std::vector<std::vector<double>> a = {{4,1,8,6,3,2,5,8,6,7},
                                       {4,1,8,6,7,9,5,1,2,3.6},
                                       {4,1,8,6,3,2,3,8,6,7},
                                       {4,1,8,6,7,9,3,1,2,3.6}};
    std::vector<double> c = {0.1,0.2,0.2,0.4,0.6,0.6,0.3,0.7,0.5,0.5};
    for (int j =0; j<7; j++){
        double low_s = 0;
        for(int i = 0; i<4; i++) {
            low_s += pow(lst[j]-a[i][j],2) + c[j];
        }
        res += 1/low_s;
    }
    return (int)res;
}