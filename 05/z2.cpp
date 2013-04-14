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

double pfm(double fm, double nfm, double dr, double r)
{
    return -4. * M_PI * r * n(r) * pow(dr, 2.) - nfm + 2. * fm;
}

double calka(double *tbl, const double dr)
{
    int i;
    double sum = 0;
    for(i = 1; i < M-1; ++i)
    {
<<<<<<< Updated upstream
        sum += (1. / 2.) * pow((tbl[i+1] - tbl[i-1])/(2. * dr), 2.) - 4. * M_PI * (i*dr) * n(i/30.) * tbl[i];
    }
    return sum * dr;
=======
        sum += (1. / 2.) * pow((tbl[i+1] - tbl[i-1])/(2. * dr), 2.) - 4. * M_PI * (i*dr) * n(i*dr) * tbl[i];
    }
    return sum;
>>>>>>> Stashed changes
}

void zad2(double dr, const double eps, char* filename)
{
<<<<<<< Updated upstream
    double tbl[M] = {0};
    tbl[M-1] = tbl[M-2] = -3;
    ofstream out(filename);
    double prevdiff = 0, diff = 0;
    do {
        prevdiff = diff;
        
        for(int i = 0; i < M-2; ++i)
        {
            tbl[i] = pfm(tbl[i+1], tbl[i+2], dr, i*dr);
        }
        
        diff = calka(tbl, dr);
    }
    while(fabs(prevdiff - diff) > eps);
    for(int i = 0; i < M; ++i)
    {
        out << dr * i << " " << tbl[i] << " " << f_dokl(i*dr) << " " << fabs(tbl[i] - f_dokl(i*dr)) << "\n";
=======
    double tbl[M];
    for(int i=0; i < M; ++i) tbl[i] = 0;
    tbl[M-1] = tbl[M-2] = -3;
    ofstream out(filename);
    double prevdiff = 0, diff = 0;

    for(int i = M-2; i > 0; --i)
    {
        tbl[i-1] = pfm(tbl[i], tbl[i+1], dr, i*dr);
    }
        
    for(int i = 0; i < M; ++i)
    {
        out << dr * i << " " << tbl[i] << " " << f_dokl(i*dr) << " " << f_dokl(i*dr) - tbl[i] << "\n";
>>>>>>> Stashed changes
    }
}    
int main()
{
<<<<<<< Updated upstream
    zad2(0.1, 10e-8, "z2e8.txt");
=======
    zad2(0.1, 10e-13, "z2e13.txt");
>>>>>>> Stashed changes
}
