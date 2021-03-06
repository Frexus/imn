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
#define KROK_MAX 1e7

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

    double k21 = f1(prevt + dt/2.0, prevu1 + dt * k11/2.0, prevu2 + dt * k12/2.0);
    double k22 = f2(prevt + dt/2.0, prevu1 + dt * k11/2.0, prevu2 + dt * k12/2.0);

    double k31 = f1(prevt + dt/2.0, prevu1 + dt * k21/2.0, prevu2 + dt * k22/2.0);
    double k32 = f2(prevt + dt/2.0, prevu1 + dt * k21/2.0, prevu2 + dt * k22/2.0);

    double k41 = f1(prevt + dt, prevu1 + dt * k31, prevu2 + dt * k32);
    double k42 = f2(prevt + dt, prevu1 + dt * k31, prevu2 + dt * k32);

    u1 = prevu1 + (dt/6.0)*(k11 + 2. * k21 + 2. * k31 + k41);
    u2 = prevu2 + (dt/6.0)*(k12 + 2. * k22 + 2. * k32 + k42);
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
    return pow((S*tol)/E, 1.0/n)*dt;
}

void zad1_1(double n, double y11, double y21, double S, double T, double tol,
          void (*f)(double&, double&, double, double, double, double, double (*f1)(double, double, double), double (*f2)(double, double, double)),
          char* file)
{
    ofstream out(file);
    double dt = 1;
    double y12 = y11, y22 = y21;
    double prevy1=y11, prevy2 = y21;
    int krok = 0;
    for(double t = 0; t < T;){

        f(y11, y21, prevy1, prevy2, t, dt*2., func1, func2);

        double tmpy1, tmpy2;
        f(tmpy1, tmpy2, prevy1, prevy2, t, dt, func1, func2);
        f(y12, y22, tmpy1, tmpy2, t + dt, dt, func1, func2);

        double Ev = fabs(err(y12, y11, n));
        double Ex = fabs(err(y22, y21, n));

        if( (Ex < tol) && (Ev < tol) )
        {
//            y11 = y12;
//            y21 = y22;
            prevy1 = y12;
            prevy2 = y22;
            double y1, y2;
            t +=2* dt;
            dokladne(y1, y2, t);
            out << t << " " << dt << " " << y12 << " " << y22 << " " << y1 << " " << y2 << "\n";
        }

        double vtime = new_time(S, tol, Ev, dt, n);
        double xtime = new_time(S, tol, Ex, dt, n);

        dt = vtime > xtime ? xtime : vtime;
        ++krok;

        //cout << dt << endl;
    }
    cout << krok << endl;
}

void zad1_2(double n, double y11, double y21, double S, double T, double tol,
          void (*f)(double&, double&, double, double, double, double, double (*f1)(double, double, double), double (*f2)(double, double, double)),
          char* file)
{
    ofstream out(file);
    double dt = 1;
    double y12 = y11, y22 = y21;
    double prevy1=y11, prevy2 = y21;
    int krok = 0;
    for(double t = 0; t < T;){

        f(y11, y21, prevy1, prevy2, t, dt*2., func1, func2);

        double tmpy1, tmpy2;
        f(tmpy1, tmpy2, prevy1, prevy2, t, dt, func1, func2);
        f(y12, y22, tmpy1, tmpy2, t + dt, dt, func1, func2);

        double Ev = fabs(err(y12, y11, n));
        double Ex = fabs(err(y22, y21, n));

        if( (Ex < tol) && (Ev < tol) )
        {
//            y11 = y12;
//            y21 = y22;
            prevy1 = y12;
            prevy2 = y22;
            double y1, y2;
            t += 2* dt;
            dokladne(y1, y2, t);
            out << t << " " << dt << " " << y12 << " " << y22 << " " << y1 << " " << y2 << "\n";
        }

        double vtime = new_time(S, tol, Ev, dt, n);
        double xtime = new_time(S, tol, Ex, dt, n);

        dt = vtime > xtime ? xtime : vtime;
        ++krok;
        if(t > 5000)
        {
            dt = 100;
        }
        if(krok > KROK_MAX)
        {
            cout << " niestabilne! "; break;
        }

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
