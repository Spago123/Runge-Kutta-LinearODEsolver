#include<iostream>
#include<Eigen/Dense>
#include<vector>
#include<functional>
#include <fstream>
#include "odefunction.hpp"
#include "algebrafunction.hpp"

//template<int Rows, int Columns>
Eigen::MatrixXd calculate(std::vector<OdeFunction> f, std::vector<std::vector<double>> params, double input){
    Eigen::MatrixXd mat(f.size(), 1);
    for(int i = 0; i < f.size() - 1; i++)
        mat(i, 0) = f[i](params[i]);

    params[f.size() - 1].push_back(input);
    mat(f.size() - 1, 0) = f[f.size() - 1](params[f.size() - 1]);
    
    return mat;
}

template<int Rows, int Columns>
std::vector<std::vector<double>> calculateParamsForK1(Eigen::MatrixXd y, int sysOrder){
    std::vector<std::vector<double>> mat(sysOrder);
    for(int i = 0; i < sysOrder - 1; i++){
        mat[i].push_back(y(i + 1, 0));
    }
    for(int i = 0; i < sysOrder; i++){
        mat[sysOrder - 1].push_back(y(i, 0));
    }
    return mat;
}

template<int Rows, int Columns>
std::vector<std::vector<double>> calculateParamsForK2(Eigen::MatrixXd y, Eigen::MatrixXd k1, int sysOrder){
    std::vector<std::vector<double>> mat(sysOrder);
    for(int i = 0; i < sysOrder - 1; i++){
        mat[i].push_back(y(i + 1, 0) + k1(i+1, 0)/2.);
    }
    for(int i = 0; i < sysOrder; i++){
        mat[sysOrder - 1].push_back(y(i, 0) + k1(i, 0)/2.);
    }
    return mat;
}

template<int Rows, int Columns>
std::vector<std::vector<double>> calculateParamsForK3(Eigen::MatrixXd y, Eigen::MatrixXd k2, int sysOrder){
    std::vector<std::vector<double>> mat(sysOrder);
    for(int i = 0; i < sysOrder - 1; i++){
        mat[i].push_back(y(i + 1, 0) + k2(i+1, 0)/2.);
    }
    for(int i = 0; i < sysOrder; i++){
        mat[sysOrder - 1].push_back(y(i, 0) + k2(i, 0)/2.);
    }
    return mat;
}

template<int Rows, int Columns>
std::vector<std::vector<double>> calculateParamsForK4(Eigen::MatrixXd y, Eigen::MatrixXd k3, int sysOrder){
    std::vector<std::vector<double>> mat(sysOrder);
    for(int i = 0; i < sysOrder - 1; i++){
        mat[i].push_back(y(i + 1, 0) + k3(i+1, 0));
    }
    for(int i = 0; i < sysOrder; i++){
        mat[sysOrder - 1].push_back(y(i, 0) + k3(i, 0));
    }
    return mat;
}

template<int Rows, int Columns>
int rungaKutta4Ode(double t0, double tFinal, double deltaT, Eigen::MatrixXd y0, std::vector<OdeFunction> f, AlgebraFunction sysInput,
                    std::string name){

    std::ofstream file(name);
    if (!file.is_open()) {
        std::cout << "Failed to open the file." << std::endl;
        return 1;
    }

    int sysOrder = f.size();
    int n = (tFinal - t0)/deltaT;

    Eigen::MatrixXd k1(sysOrder, 1);
    Eigen::MatrixXd k2(sysOrder, 1);
    Eigen::MatrixXd k3(sysOrder, 1);
    Eigen::MatrixXd k4(sysOrder, 1);    

    Eigen::MatrixXd yn(sysOrder, 1);
    yn = y0;

    double t = t0;
    for(int i = 0; i < n; i++, t += deltaT){
        
        k1 = deltaT * calculate(f, calculateParamsForK1<Eigen::Dynamic, Eigen::Dynamic>(yn, sysOrder), sysInput(t));
        k2 = deltaT * calculate(f, calculateParamsForK2<Eigen::Dynamic, Eigen::Dynamic>(yn, k1, sysOrder), sysInput(t + deltaT/2.));
        k3 = deltaT * calculate(f, calculateParamsForK3<Eigen::Dynamic, Eigen::Dynamic>(yn, k2, sysOrder), sysInput(t + deltaT/2.));
        k4 = deltaT * calculate(f, calculateParamsForK4<Eigen::Dynamic, Eigen::Dynamic>(yn, k3, sysOrder), sysInput(t + deltaT));
        
        yn += (k1 + 2*k2 + 2*k3 + k4)/6.;
        file << t << "\t" << yn(0, 0) << std::endl;
    }
    file.close();
    return 1;
}

int main(){
    /*Reading with parser*/
    std::string ode("y'=-0.01y+1u");
    std::string input("1t");



    AlgebraFunction u(input);

    int sysOrder = OdeFunction::systemOrder(ode);
    std::vector<OdeFunction> F;
    for(int i = 0; i < sysOrder - 1; i++)
        F.push_back(OdeFunction({1}));
    F.push_back(OdeFunction(ode));

    Eigen::MatrixXd y0(1, 1);
    y0(0, 0) = 0;
    //y0(1, 0) = 0;
    //y0(2, 0) = 0;

    rungaKutta4Ode<Eigen::Dynamic, Eigen::Dynamic>(0, 5, 0.001, y0, F, u, "rez1.txt");

}