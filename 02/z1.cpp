#include <iostream>
#include <ios>
#include <fstream>
#include <ostream>
#include <cstdio>
#include <cstdlib>
#include <cmath>

using namespace std;

double func(double t, double y)
{
    return (1.0/5.0)*y;
}

double euler(double prevY, double t, double dt, double (*f)(double t, double y))
{
    return prevY + dt*f(t-dt, prevY);
}

double rk2(double prevY, double t, double dt, double (*f)(double t, double y))
{
    return prevY + dt * f(t-dt + (dt/2.0), prevY + (1.0*dt*f(t-dt, prevY))/(2.0));
}

double dokladne(double t)
{
    return exp((1.0/5.0)*t);
}

double richardson(double y, double prevY, int n)
{
    return y + (y - prevY)/(pow(2.0, n-1.0) - 1);
}

int main()
{
    double y_eu = 1;
    double y_rk2 = 1;
    double prev_eu = 1;
    double prev_rk2 = 1;
    double dt = 0.1;
    ofstream euler_f("z1_eu.txt");
    ofstream rk2_f("z1_rk2.txt");
    ofstream dok_f("z1_dok.txt");
    ofstream euler_err_f("z1_eu_err.txt");
    ofstream rk2_err_f("z1_rk2_err.txt");
//    for(double t = dt; t < 20; t += dt)
//    {
//        y_eu = euler(y_eu, t, dt, func);
//        y_rk2 = rk2(y_rk2, t, dt, func);
//        double dok = dokladne(t);
//        euler_f << t << " " << y_eu << "\n";
//        rk2_f << t << " " << y_rk2 << "\n";
//        dok_f << t << " " << dok << "\n";
//        euler_err_f << t << " " << y_eu - dok << "\n";
//        rk2_err_f << t << " " << y_rk2 - dok << "\n";
//    }

    for(double t = dt; t < 20; t += dt)
    {
        prev_eu = y_eu;
        prev_rk2 = y_rk2;
        y_eu = euler(prev_eu, t, dt, func);
        y_rk2 = rk2(prev_rk2, t, dt, func);
        y_eu = richardson(y_eu, prev_eu, 2);
        y_rk2 = richardson(y_rk2, prev_rk2, 3);
        double dok = dokladne(t);
        euler_f << t << " " << y_eu << "\n";
        rk2_f << t << " " << y_rk2 << "\n";
        dok_f << t << " " << dok << "\n";
        euler_err_f << t << " " << y_eu - dok << "\n";
        rk2_err_f << t << " " << y_rk2 - dok << "\n";
    }

    euler_f.close();
    rk2_f.close();
    dok_f.close();
    euler_err_f.close();
    rk2_err_f.close();


}