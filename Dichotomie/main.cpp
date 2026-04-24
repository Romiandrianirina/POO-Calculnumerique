#include <iostream>
#include <cmath>
#include <functional>
#include "appro.hpp"

int main()
{
    auto f = [](double x) -> double{
        return x * x + 2*x - 1;
    };
    double gauche = 0, droite = 0;
    double epsilon = 0.000000000001;
    find_intervalle(f, &gauche, &droite);
    approximation(f, gauche, droite, epsilon);

}