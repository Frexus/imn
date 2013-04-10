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



void zad5(double dr, double f1,  const double eps, char* filename)
{
    double tbl[M] = {0};
    tbl[0] = 0;
    tbl[1] = f1;
    ofstream out(filename);
    for(int i=2; i < M; ++i)
    {
        tbl[i] = ( (dr * dr) / (12.) ) * (Sm(i*dr + dr) + 10. * Sm(i * dr) + Sm(i * dr - dr)) + 2 * tbl[i-1] - tbl[i-2];
    }
    for(int i = 0; i < M; ++i)
    {
        out << dr * i << " " << tbl[i] << " " << f_dokl(i*dr) << " " << fabs(tbl[i] - f_dokl(i*dr)) << "\n";
    }
}

void zad5_2(double dr, double f1,  const double eps, char* filename)
{
    double tbl[M_2] = {0};
    tbl[0] = 0;
    tbl[1] = f1;
    ofstream out(filename);
    for(int i=2; i < M_2; ++i)
    {
        tbl[i] = ( (dr * dr) / (12.) ) * (Sm(i*dr + dr) + 10. * Sm(i * dr) + Sm(i * dr - dr)) + 2 * tbl[i-1] - tbl[i-2];
    }
    for(int i = 0; i < M_2; ++i)
    {
        out << dr * i << " " << tbl[i] << " " << f_dokl(i*dr) << " " << fabs(tbl[i] - f_dokl(i*dr)) << "\n";
    }
}

int main()
{
    zad5(0.1, f_dokl(0.1), 10e-13, "z5_1.txt");
    zad5_2(0.01, f_dokl(0.01), 10e-13, "z5_2.txt");
    zad5(0.1, -0.0749981, 10e-13, "z5_3.txt");

}
