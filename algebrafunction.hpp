#ifndef ODEFUNCTION_H
#define ODEFUNCTION_H

#include<vector>
#include<string>

class AlgebraFunction{
    double dc;
    std::vector<double> coeffs;

    public:

    AlgebraFunction(std::string equation){
        
    }

    double operator()(double time){
        double sum = dc;
        for(int i = 0; i < coeffs.size(); i++){

        }
    }
};

#endif