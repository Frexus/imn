#include <iostream>
#include <cmath>
#include <fstream>
#include <string>

using namespace std;

#define N 121

double ro(double x, double y)
{
	return exp(-(pow(sqrt((x/6.)*(x/6.)+(y/6.)*(y/6.)) - 3., 2.)));
}

double fi(double omega, double ij, double ip1j, double im1j, double ijp1, double ijm1, double dx, double x, double y)
{
	double frac = (ip1j + im1j + ijp1, + ijm1 + ro(x,y)*dx*dx) / 4.;
	return (1. - omega)*ij + omega * frac;
}

double dfi(double pfi, double nfi, double d)
{
	return (nfi - pfi) / (2. * d);
}

int main()
{
	double fi_tab[N][N];
	cout.precision(10);
	for(int i=0; i < N; ++i)
	{
		for(int j = 0; j < N; ++j)
		{
			fi_tab[i][j] = 0;
		}
	}
	double a = 0, preva = 0;
	int it = 1;
	ofstream f;
		double omega = 1.95;
		a = 1000;
		it = 1;
		do{
			preva = a;
			a = 0;
			for(int i = 1; i < N-1; ++i)
			{
				for(int j = 1; j < N-1; ++j)
				{
					fi_tab[i][j] = (1. - omega) * fi_tab[i][j] + omega * (fi_tab[i+1][j] + fi_tab[i-1][j] + fi_tab[i][j-1] + fi_tab[i][j+1] + ro(j-60, i-60)) / 4.;
				}
			}
			for(int i = 1; i < N-1; ++i)
			{
				for(int j = 1; j < N-1; ++j)
				{
					a += 0.5 * (pow( (fi_tab[i+1][j] - fi_tab[i-1][j]) / 2., 2) + pow( (fi_tab[i][j+1] - fi_tab[i][j-1]) / 2., 2)) - ro(j - 60, i - 60) * fi_tab[i][j];
				}
			}
			it++;
		}
		while(fabs(a - preva) > 10e-5);
	
	f.open("z2.txt", ofstream::out);
	for(int j = 1; j < N-1; ++j)
	{
		double rho = -(fi_tab[j-1][60] - 2. * fi_tab[j][60] + fi_tab[j+1][60] + fi_tab[j][59] - 2. * fi_tab[j][60] + fi_tab[j][61]);
		f << j-60 << " " << rho << " " << ro(0, j-60) << "\n";
	}
}
