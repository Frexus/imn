#include <iostream>
#include <ios>
#include <fstream>
#include <ostream>
#include <cstdio>
#include <cstdlib>
#include <cmath>

using namespace std;

double n(double r)
{
    return (-pow(r,2.0) * exp(-r)) / (32. * M_PI);
}

double Sm(double r)
{
    return -4. * M_PI * n(r) * r;
}

double func1 (double r, double x, double y)
{
    return y;
}

double func2(double r, double x, double y)
{
    return Sm(r);
}


void rk2_uklad(double& u1, double& u2, double prevu1, double prevu2, double prevt, double dt, double (*f1)(double t, double uf, double ut), double (*f2)(double t, double uf, double ut))
{
    double k11 = f1(prevt, prevu1, prevu2);
    double k12 = f2(prevt, prevu1, prevu2);
    double k21 = f1(prevt + dt, prevu1+dt * k11, prevu2 + dt * k12);
    double k22 = f2(prevt + dt, prevu1+dt * k11, prevu2 + dt * k12);
    u1 = prevu1 + (dt/2.0)*(k11 + k21);
    u2 = prevu2 + (dt/2.0)*(k12 + k22);
}

double f_dokl(double r)
{
    return exp(-r) * (0.125 * pow(r, 3.) + 0.75 * pow(r, 2.) + 2.25 * r + 3.) - 3.;
}

void zad5()
{
    double dr = 0.1;
    double df, dg;
    df = -3;
    dg = 0;
    for(double r = 30; r >= 0; r -= dr)
    {
        rk2_uklad(df, dg, df, dg, r, dr, func1, func2);
        cout << r << " " << df << " " << dg << " " << f_dokl(r) << "\n";
    }
}
int main()
{
    zad5();
}
