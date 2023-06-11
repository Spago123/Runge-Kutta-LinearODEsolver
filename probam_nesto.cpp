#include <iostream>
#include "algebrafunction.hpp"

int main(){
    AlgebraFunction alg("2.5-1t");
    std::cout<<alg(2.5);
}