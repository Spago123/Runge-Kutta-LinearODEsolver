#include<iostream>
#include "odefunction.hpp"

int main(){
    std::string eq("y'''' =-2y'' +1y' +2y -21.5u");
    OdeFunction ode(eq);
    //std::cout<<ode.sysOrder();
    //for(auto string : ode.prepareDerivations(eq, ode.sysOrder()))
      //  std::cout<<string<<std::endl;

    for (double i : ode.getConstants()){
        std::cout<<i<<std::endl;
    }
}