#include <iostream>
#include <sstream>
#include <fstream>
#include <memory.h>
#include <cmath>

#define N 257
#define DX (1./32.)
#define DY (1./32.)
#define EPSILON 10e-9
#define K 1

using namespace std;

void z1()
{
	double fi[N][N];
	double intg = 0, prev_intg;
	
	ofstream out_a("z1_a.txt");
	ofstream out_pot("z1_pot.txt");
	
	memset(fi, 0, sizeof(double) * N * N);
	
	unsigned int itnum = 0;
	
	for(int i = 0; i < N; ++i)
	{
		fi[i][0] = pow(-4., 2) - pow((double)i * DY - 4., 2);
		fi[i][N-1] = pow((N-1) * DX - 4., 2) - pow((double)i * DY - 4., 2);
		fi[0][i] = pow((double)i * DX - 4., 2) - pow(-4., 2);
		fi[N-1][i] = pow((double)i * DX - 4., 2) - pow((N-1) * DY - 4., 2);
	}
	
	do
	{
		prev_intg = intg;
		for(int i = 1; i < N - 1; ++i)
		{
			for(int j = 1; j < N - 1; ++j)
			{
				fi[i][j] = (fi[i-1][j] + fi[i][j-1] + fi[i+1][j] + fi[i][j+1]) / 4.;
			}
		}
		intg = 0;
		for(int i = 0; i < N - K; ++i)
		{
			for(int j = 0; j < N - K; ++j)
			{
				intg += pow(fi[i + K][j] + fi[i + K][j + K] - fi[i][j] - fi[i][j + K], 2.) + pow(fi[i][j + K] + fi[i + K][j + K] - fi[i][j] - fi[i + K][j], 2);
			}
		}
		intg /= 8.;
		out_a << itnum++ << " " << intg << "\n";
		//cout << prev_intg - intg << endl;
	}
	while(fabs(prev_intg - intg) > EPSILON);
	
	for(int i = 0; i < N; ++i)
	{
		for(int j = 0; j < N; ++j)
		{
			out_pot << fi[i][j] << " ";
		}
		out_pot << "\n";
	}
}

int main()
{
	z1();
}
