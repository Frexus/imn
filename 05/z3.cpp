#include <iostream>
#include <cmath>
#include <fstream>

#define M 301
#define M_2 3001
using namespace std;

double n(double r)
{
    return (-pow(r,2.0) * exp(-r)) / (32. * M_PI);
}

double f_dokl(double r)
{
    return exp(-r) * (0.125 * pow(r, 3.) + 0.75 * pow(r, 2.) + 2.25 * r + 3.) - 3.;
}

double nfm(double fm, double pfm, double dr, double r)
{
    return -4. * M_PI * r * n(r) * pow(dr, 2.) - pfm + 2. * fm;
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

void zad3(double dr, double f1, const double eps, char* filename)
{
    double tbl[M] = {0};
    tbl[0] = 0;
    tbl[1] = f1;
    ofstream out(filename);
    double prevdiff = 0, diff = 0;
    do {
        prevdiff = diff;
        
        for(int i = 2; i < M; ++i)
        {
            tbl[i] = nfm(tbl[i-1], tbl[i-2], dr, i*dr);
        }
        
        diff = calka(tbl, dr);
    }
    while(fabs(prevdiff - diff) > eps);
    for(int i = 0; i < M; ++i)
    {
        out << dr * i << " " << tbl[i] << " " << f_dokl(i*dr) << " " << fabs(tbl[i] - f_dokl(i*dr)) << "\n";
    }
}

void zad3_2(double dr, double f1, const double eps, char* filename)
{
    double tbl[M_2] = {0};
    tbl[0] = 0;
    tbl[1] = f1;
    ofstream out(filename);
    double prevdiff = 0, diff = 0;
    do {
        prevdiff = diff;
        
        for(int i = 2; i < M_2; ++i)
        {
            tbl[i] = nfm(tbl[i-1], tbl[i-2], dr, i*dr);
        }
        
        diff = calka(tbl, dr);
    }
    while(fabs(prevdiff - diff) > eps);
    for(int i = 0; i < M_2; ++i)
    {
        out << dr * i << " " << tbl[i] << " " << f_dokl(i*dr) << " " << fabs(tbl[i] - f_dokl(i*dr)) << "\n";
    }
}
int main()
{
    zad3(0.1, f_dokl(0.1), 10e-13, "z3_1.txt");
    zad3_2(0.01, f_dokl(0.01), 10e-13, "z3_2.txt");
    zad3(0.1, -0.0749981, 10e-13, "z3_3.txt");
}
