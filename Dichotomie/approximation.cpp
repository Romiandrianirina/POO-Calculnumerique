#include <iostream>
#include <cmath>
#include <functional>
#include "appro.hpp"

using namespace std;

void find_intervalle(std::function<double(double)> f, double *a, double *b)
{
    double debut = 0, fin = 10;
    double diff = 0.5, x = debut;

    while (x < fin)
    {

        if (f(x) * f(x + diff) < 0)
        {
            *a = x;
            *b = x + diff;
            return;
        }
        x += diff;
    }
    return;
}

void approximation(std::function<double(double)> f,double a, double b, double epsilon)
{
    double milieu = 0;
    while((b-a)/2 > epsilon)
    {
        milieu = (a + b) / 2;

        if(f(milieu) == 0)
            break;

        if(f(a) * f(milieu) < 0)
            b = milieu;
        else
            a = milieu;
    }
    milieu = (a + b) /2;

    cout<<"Approximation obtenu: "<<milieu<<endl;
    cout<<"Precision: "<<epsilon<<endl;
    
}