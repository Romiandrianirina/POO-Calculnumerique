#ifndef DEF_APPRO
#define DEF_APPRO

#include <iostream>
#include <cmath>
#include <functional>

    void find_intervalle(std::function<double(double)> f,double* a, double* b);
    void approximation(std::function<double(double)> f,double a, double b, double epsilon);
#endif