#ifndef ALGEBRAFUNCTION_H
#define ALGEBRAFUNCTION_H

#include <vector>
#include <string>
#include "mathfunctions.hpp"

class AlgebraFunction{

    std::vector<Function*> functions;

    public:

    AlgebraFunction(std::string equation){
        functions = convertToFunctions(extractTerms(equation));
    }

    double operator()(double time){
        double sum = 0;
        for(int i = 0; i < functions.size(); i++){
            sum += functions[i]->evaluate(time);
        }
        return sum;
    }

    ~AlgebraFunction(){
        for (const auto& func : functions) {
            delete func;
        }        
    }
};

#endif