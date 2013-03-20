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

double trapez(double prevy, double prevy1, double prevy2, double prevt, double dt, double (*f)(double, double, double))
{
    double y1 = (prevy1 * (1. - (L1*dt)/2.))/(1. + (L1*dt)/2.) + (dt/2.) * (2. * L2 * prevy2 + L1)/(1. + (L1*dt)/2.);
    double y2 = (prevy2 * (1 - (L2*dt)/2.))/(1. + (L2*dt)/2.);
    double t = prevt + dt;
    return prevy + dt/2. * (f(prevt, prevy1, prevy2) + f(t, y1, y2));
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

void zad2_1(double n, double y11, double y21, double S, double T, double tol, char* file)
{
    ofstream out(file);
    double dt = 1;
    double y12 = y11, y22 = y21;
    double prevy1=y11, prevy2 = y21;
    int krok = 0;
    for(double t = 0; t < T;){

        y11 = trapez(prevy1, prevy1, prevy2, t, dt, func1);
        y12 = trapez(prevy1, prevy1, prevy2, t, dt/2., func1);
        y12 = trapez(y12, y12, prevy2, t, dt/2., func1);

        y21 = trapez(prevy2, prevy1, prevy2, t, dt, func2);
        y22 = trapez(prevy2, prevy1, prevy2, t, dt/2., func2);
        y22 = trapez(y22, prevy1, y22, t, dt/2., func2);

        double Ev = fabs(err(y12, y11, n));
        double Ex = fabs(err(y22, y21, n));

        if( (Ex < tol) && (Ev < tol) )
        {
//            y11 = y12;
//            y21 = y22;
            prevy1 = y12;
            prevy2 = y22;
            double y1, y2;
            dokladne(y1, y2, t);
            out << t << " " << dt << " " << y12 << " " << y22 << " " << y1 << " " << y2 << "\n";
            t += dt;
        }

        double vtime = new_time(S, tol, Ev, dt, n);
        double xtime = new_time(S, tol, Ex, dt, n);

        dt = vtime > xtime ? xtime : vtime;
        ++krok;

        //cout << dt << endl;
    }
    cout << krok << endl;
}

int main()
{
    zad2_1(3, 0, 1, 0.75, 10000, 0.00001, "z2.txt");
}
