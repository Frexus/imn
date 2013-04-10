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

double Sm(double r)
{
    return -4. * M_PI * n(r) * r;
}



void zad4(double dr, const double eps, char* filename)
{
    double tbl[M] = {0};
    tbl[M-1] = tbl[M-2] = -3;
    ofstream out(filename);
    for(int i=M-3; i >= 0; --i)
    {
        tbl[i] = ( (dr * dr) / (12.) ) * (Sm(i*dr + dr) + 10. * Sm(i * dr) + Sm(i * dr - dr)) + 2 * tbl[i+1] - tbl[i+2];
    }
    for(int i = 0; i < M; ++i)
    {
        out << dr * i << " " << tbl[i] << " " << f_dokl(i*dr) << " " << fabs(tbl[i] - f_dokl(i*dr)) << "\n";
    }
}

int main()
{
    zad4(0.1, 10e-13, "z4.txt");
}
