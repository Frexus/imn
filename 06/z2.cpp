#include <iostream>
#include <ios>
#include <sstream>
#include <fstream>
#include <ostream>
extern "C" {
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
}
#include <cmath>
#include "nrutil.h"

using namespace std;

#define P 10.0

void gaussj(float **a, int n, float **b, int m);

void copy_matrix(float** src, float** dest, int n, int m)
{
	for(int i=1; i <= n; ++i)
	{
		for(int j = 1; j <= m; ++j)
		{
			src[i][j] = dest[i][j];
		}
	}
}

void update_mtrx(float** J, float** F, int n, double* theta, double ds)
{

	for(int i = 1; i <= n; ++i)
	{
		for(int j = 1; j <= n; ++j)
		{
			if(i == j) {
				J[i][j] = -2. + P * ds * ds * cos(theta[i]);
				if(j > 1)
					J[i][j-1] = 1.0;
				if(i > 1)
					J[i-1][j] = 1.0;
			}
		}
		F[i][1] = -(theta[i-1] - 2. * theta[i] + theta[i+1] + P * ds * ds * sin(theta[i]));
	}
}

void test(double** tab)
{
	for(int i=1; i < 11; ++i)
	{
		*(tab[i-1]) = i;
		cout << *(tab[i-1]) << ' ';
	}
}

double v_length(float** nr_vec, int n)
{
	double l = 0;
	for(int i = 1; i <= n; ++i)
	{
		l += nr_vec[i][1] * nr_vec[i][1];
	}
	return sqrt(l);
}

double integral(double (*f)(double), double ds, int n, double *theta)
{
	double result = 0;
	for(int i = 0; i <= n; ++i)
	{
		result += f(theta[i]) * ds;
	}
	return result;
}


void zad2(bool v, char* prefix)
{
	ofstream f;
	
	float** J_matrix = matrix(1, 99, 1, 99);
	float** F_vec = matrix(1, 99, 1, 1);
	
	const double ds = 0.005;
	double theta[101];
	
	//init
	theta[0] = M_PI /4.0;
	theta[100] = 0;
	int it = 0;
	
	for(int i = 1; i <= 99; ++i)
	{
		if(!v)
		{
			theta[i] = (double)rand()/((double)RAND_MAX);
		}
		else
		{
			theta[i] = M_PI/4.0 - M_PI/2.0 * ds * (double)i;
		}
	}
	stringstream ss;
	ss << prefix << "_it" << it << ".txt";
	string str;
	ss >> str;
	f.open(str.c_str(), fstream::out);
		
	for(int i=0; i < 101; ++i)
	{
		f << i * ds << " " << integral(cos, ds, i, theta) << " " << theta[i] << " " << integral(sin, ds, i, theta) << '\n';
	}
	f.close();
	it++;
	//calc
	do
	{
		update_mtrx(J_matrix, F_vec, 99, theta, ds);
		
		::gaussj(J_matrix, 99, F_vec, 1);
		
		for(int i = 1; i <= 99; ++i)
		{
			theta[i] += F_vec[i][1];
		}
		
		ss << prefix << "_it" << it << ".txt";
		string str;
		ss >> str;
		f.open(str.c_str(), fstream::out);
		
		for(int i=0; i < 101; ++i)
		{
			f << i * ds << " " << integral(cos, ds, i, theta) << " " << theta[i] << " " << integral(sin, ds, i, theta) << '\n';
		}
		f.close();
		it++;
	}
	while(v_length(F_vec, 99) > 10e-3);
	
	free_matrix(J_matrix, 1, 99, 1, 99);
	free_matrix(F_vec, 1, 99, 1, 1);
}

int main()
{
	zad2(0, "zad2a");
	zad2(1, "zad2b");
}
