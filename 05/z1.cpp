#include <iostream>
#include <cmath>
#include <fstream>

#define M 301

using namespace std;

double n(double r)
{
    return (-pow(r,2.0) * exp(-r)) / (32. * M_PI);
}

double f_dokl(double r)
{
    return exp(-r) * (0.125 * pow(r, 3.) + 0.75 * pow(r, 2.) + 2.25 * r + 3.) - 3.;
}

double fm(double pfm, double nfm, double dr, double r)
{
    return (-4. * M_PI * r * n(r) * pow(dr, 2.) - nfm - pfm) / (-2.);
}

double calka(double *tbl, const double dr)
{
    int i;
    double sum = 0;
    for(i = 1; i < M-1; ++i)
    {
        sum += (1. / 2.) * pow((tbl[i+1] - tbl[i-1])/(2. * dr), 2.) - 4. * M_PI * (i*dr) * n(i/30.) * tbl[i];
    }
    return sum * dr;
}

void zad1(double dr, double last, double first, const double eps, char* filename)
{
    double tbl[M] = {0};
    tbl[0] = first;
    tbl[M-1] = last;
    ofstream out(filename);
    double prevdiff = 0, diff = 0;
    do {
        prevdiff = diff;
        
        for(int i = 1; i < M - 1; ++i)
        {
            tbl[i] = fm(tbl[i-1], tbl[i+1], dr, i*dr);
        }
        
        diff = calka(tbl, dr);
    }
    while(fabs(prevdiff - diff) > eps);
    for(int i = 0; i < M; ++i)
    {
        out << dr * i << " " << tbl[i] << " " << f_dokl(i*dr) << " " << fabs(tbl[i] - f_dokl(i*dr)) << "\n";
    }
}    
int main()
{
    zad1(0.1, -3, 0, 10e-13, "z1e13.txt");
    zad1(0.1, -3, 0, 10e-7, "z1e7.txt");
    zad1(0.1, -3, 0, 10e-5, "z1e5.txt");
}
