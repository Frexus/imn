#include <iostream>
#include <fstream>
#include <cmath>

#define EPS 1e-6

using namespace std;

double iloraz(double u, double t, double du, double (*f)(double ft, double fu))
{
    return (f(t, u+du) - f(t, u-du))/(2.0*du);
}

double funkcja(double t, double u)
{
    return -10.0*(u-5.0*t*t)+10.0*t;
}

double trapez(double prevu, double t, double dt, double u, double (*f)(double ft, double fu))
{
    return prevu + dt*(f(t-dt, prevu) + f(t, u))/2.0;
}

double krok_trapez(double umi, double prevu, double dt, double t, double (*f)(double ft, double fu), double du)
{
    return umi - (umi - prevu - (dt/2.0)*(f(t, umi) + f(t-dt, prevu)))/(1.0-(dt/2.0)*iloraz(umi, t, du, f));
}

double iter_trapez(double prevu, double t, double dt, double (*f)(double ft, double fu), double du)
{
    double umi = prevu;
    double prevumi;
    do
    {
        prevumi = umi;
        umi = krok_trapez(prevumi, prevu, dt, t, f, du);
        cout << umi << endl;
    } while( fabs(prevumi - umi) > EPS);
    return umi;
}

int main()
{
    ofstream z8f("zad8.txt");
    double dt = 0.3;
    double du = 0.3;
    double u = 1.0;
    double prevu;
    double umi = 1.0;
    for(double t = 0; t < 30.0; t += dt)
    {
        prevu = u;
        u = iter_trapez(u, t, dt, funkcja, du);
        z8f << trapez(prevu, t, dt, u, funkcja) << "\n";
    }
}
