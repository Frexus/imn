#include <iostream>
#include <ios>
#include <fstream>
#include <ostream>
#include <cstdio>
#include <cstdlib>
#include <cmath>

using namespace std;

#define L1 1.0
#define L2 0.001
#define KROK_MAX 1e6

double func1(double t, double y1, double y2)
{
    return -L1*y1 + L2*y2+1./2.;
}

double func2(double t, double y1, double y2)
{
    return -L2*y2;
}

//void trapez(double& y1, double& y2, double prevy1, double prevy2, double dt)
//{
//    y1 = (prevy1*(1.0 - (L1 * dt)/2.))/(1. + (L1*dt)/2.) + dt/2. * (2*L2*prevy2 + L1)/(1. + (L1*dt)/2.);
//    y2 = (prevy2 * (1 - (L2*dt)/2.))(1. + (L2*dt)/2.);
//}

double trapez(double prevy1, double prevy2, double prevdt, double dt, double (*f)(double, double, double))
{
    return prevy + dt/2. * (func(t, prevy1, prevy2) + func())
}

void dokladne(double& y1, double& y2, double t)
{
    y1 = 0.5*((L1+L2)/(L2-L1))*exp(-L1*t)+L2/(L1-L2)*exp(-L2*t)+1./2.;
    y2 = exp(-L2*t);
}

double err(double y2, double y1, double n)
{
    return (y2-y1)/(pow(2.0,n-1.0) - 1.0);
}

double new_time(double S, double tol, double E, double dt, double n)
{
    return pow((S*tol)/abs(E), 1.0/n)*dt;
}

void zad1_1(double n, double y11, double y21, double S, double T, double tol,
          void (*f)(double&, double&, double, double, double, double, double (*f1)(double, double, double), double (*f2)(double, double, double)),
          char* file)
{
    ofstream out(file);
    double dt = 0.1;
    double y12, y22;
    double prevy1, prevy2;
    int krok = 0;
    for(double t = dt; t < T;){
        prevy1 = y11;
        prevy2 = y12;
        y12 = y11;
        y22 = y21;

        f(y11, y21, y11, y21, t, dt, func1, func2);

        f(y12, y22, y12, y22, t, dt/2.0, func1, func2);
        f(y12, y22, y12, y22, t + dt/2.0, dt/2.0, func1, func2);

        double Ev = err(y11, y12, 5);
        double Ex = err(y21, y22, 5);

        if(Ex < tol && Ev < tol)
        {
            double y1, y2;
            dokladne(y1, y2, t);
            out << t << " " << dt << " " << y12 << " " << y22 << " " << y1 << " " << y2;
            t+=dt;
        }

        double vtime = new_time(S, tol, Ev, dt, 5);
        double xtime = new_time(S, tol, Ex, dt, 5);
        out << " " << vtime << " " << xtime << " \n";
        dt = vtime > xtime ? xtime : vtime;
        ++krok;

        //cout << dt << endl;
    }
    cout << krok << endl;
}

int main()
{
    zad1_1(5, 0, 1, 0.75, 10000, 0.00001, rk4_uklad, "z1.txt");
    zad1_1(3, 0, 1, 0.75, 10000, 0.00001, rk2_uklad, "z1_rk2.txt");
    zad1_2(3, 0, 1, 0.75, 10000, 0.00001, rk2_uklad, "z1_1.txt");
}
