#include <iostream>
#include <Eigen/Dense>
#include "RungaKutta.hpp"
#include "ReadingXml.hpp"


int main(){
    ReadingXML reader;
    RungaKutta::rungaKutta4Ode<Eigen::Dynamic, 1>(reader.getStartTime(), reader.getStopTime(), 
    reader.getStep(), reader.getInitCond(), reader.getOde(), reader.getSystemInput(), reader.getFile());

}