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

double func1(double t, double y1, double y2)
{
    return -L1*y1 + L2*y2+1./2.;
}

double func2(double t, double y1, double y2)
{
    return -L2*y2;
}


void rk4_uklad(double& u1, double& u2, double prevu1, double prevu2, double prevt, double dt, double (*f1)(double t, double uf, double ut), double (*f2)(double t, double uf, double ut))
{
    double k11 = f1(prevt, prevu1, prevu2);
    double k12 = f2(prevt, prevu1, prevu2);
    double k21 = f1(prevt + dt/2.0, prevu1+dt * k11/2.0, prevu2 + dt * k12/2.0);
    double k22 = f2(prevt + dt, prevu1+dt * k11/2.0, prevu2 + dt * k12/2.0);
    double k31 = f1(prevt + dt/2.0, prevu1 + dt*k21/2.0, prevu2+dt*k22/2.0);
    double k32 = f2(prevt + dt/2.0, prevu1 + dt*k21/2.0, prevu2+dt*k22/2.0);
    double k41 = f1(prevt + dt, prevu1 + dt * k31, prevu2 + dt * k32);
    double k42 = f2(prevt + dt, prevu1 + dt * k31, prevu2 + dt * k32);
    u1 = prevu1 + (dt/6.0)*(k11 + 2.*k21 + 2.*k31 + k41);
    u2 = prevu2 + (dt/6.0)*(k12 + 2.*k22 + 2.*k32 + k42);
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

double dokladne(double& y1, double& y2, double t)
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

void zad3(double y11, double y21, double S, double T, double tol,
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
    zad3(0, 1, 0.75, 10000, 0.00001, rk4_uklad, "z3.txt");
    zad3(0, 1, 0.75, 10000, 0.00001, rk2_uklad, "z3_rk2.txt");
}
