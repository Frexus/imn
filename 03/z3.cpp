#include <iostream>
#include <ios>
#include <fstream>
#include <ostream>
#include <cstdio>
#include <cstdlib>
#include <cmath>

using namespace std;

double func(double t, double u)
{
    return -100. * (u - sin(t)) + cos(t);
}

double new_u (double t, double dt, double prevu)
{
    return (prevu + dt * (100. * sin(t + dt) + cos (t + dt))) / (1. + 100. * dt);
}

double euler(double prevu, double dt, double f)
{
    return prevu + dt * f;
}

double err(double y2, double y1, double n)
{
    return (y2-y1)/(pow(2.0,n-1.0) - 1.0);
}

double new_time(double S, double tol, double E, double dt, double n)
{
    return pow((S*tol)/abs(E), 1.0/n)*dt;
}

void zad2_1(double n, double u, double S, double T, double tol, char* file)
{
    ofstream out(file);
    double dt = 0.0001;
    double u1 = u, u2 = u;
    double prevu = u;
    int krok = 0;
    for(double t = 2. * dt; t < T ; ){

        u1 = euler(prevu, dt * 2, func(t, prevu));
        u2 = euler(prevu, dt, func(t, prevu));
        u2 = euler(u2, dt, func(t + dt, u2));

        double Ev = fabs(err(u2, u1, n));

        if(Ev < tol)
        {
            prevu = u2;
            t += 2. * dt;
            out << t << " " << dt << " " << u2 << "\n";
        }

        dt = new_time(S, tol, Ev, dt, n);
        ++krok;

        //cout << dt << endl;
    }
    cout << krok << endl;
}

void zad2_2(double n, double u, double S, double T, double tol, char* file)
{
    ofstream out(file);
    double dt = 0.0001;
    double u1 = u, u2 = u;
    double prevu = u;
    int krok = 0;
    for(double t = 2. * dt; t < T ; ){

        u1 = new_u(t, dt * 2., prevu);
        u2 = new_u(t, dt, prevu);
        u2 = new_u(t+dt, dt, u2);

        double Ev = fabs(err(u2, u1, n));

        if(Ev < tol)
        {
            prevu = u2;
            t += 2. * dt;
            out << t << " " << dt << " " << u2 << "\n";
        }
        dt = new_time(S, tol, Ev, dt, n);
        ++krok;

        //cout << dt << endl;
    }
    cout << krok << endl;
}

int main()
{
    zad2_1(2, 1, 0.75, M_PIl, 0.01, "z3_euj_01.txt");
    zad2_1(2, 1, 0.75, M_PIl, 0.001, "z3_euj_001.txt");
    zad2_1(2, 1, 0.75, M_PIl, 0.0001, "z3_euj_0001.txt");

    zad2_2(3, 1, 0.75, M_PIl, 0.01, "z3_eunj_01.txt");
    zad2_2(3, 1, 0.75, M_PIl, 0.001, "z3_eunj_001.txt");
    zad2_2(3, 1, 0.75, M_PIl, 0.0001, "z3_eunj_0001.txt");
}
