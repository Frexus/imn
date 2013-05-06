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

void z2()
{
	double fi[N][N];
	double intg = 0, prev_intg;
	
	memset(fi, 0, sizeof(double) * N * N);
	ofstream a_out("z2_a.txt");
	unsigned int itnum = 0;
	
	for(int i = 0; i < N; ++i)
	{
		fi[i][0] = pow(-4., 2) - pow((double)i * DY - 4., 2);
		fi[i][N-1] = pow((N-1) * DX - 4., 2) - pow((double)i * DY - 4., 2);
		fi[0][i] = pow((double)i * DX - 4., 2) - pow(-4., 2);
		fi[N-1][i] = pow((double)i * DX - 4., 2) - pow((N-1) * DY - 4., 2);
	}
	for(int k = 32; k != 0; k /= 2)
	{
		char buf[20];

		do
		{
			prev_intg = intg;
			for(int i = k; i < N - k; i+=k)
			{
				for(int j = k; j < N - k; j+=k)
				{
					fi[i][j] = (fi[i-k][j] + fi[i][j-k] + fi[i+k][j] + fi[i][j+k]) / 4.;
				}
			}
			intg = 0;
			for(int i = 0; i < N - k; i += k)
			{
				for(int j = 0; j < N - k; j += k)
				{
					intg += pow(fi[i + k][j] + fi[i + k][j + k] - fi[i][j] - fi[i][j + k], 2.) + pow(fi[i][j + k] + fi[i + k][j + k] - fi[i][j] - fi[i + k][j], 2);
				}
			}
			intg /= 8.;
			a_out << itnum++ << " " << intg << "\n";
		}
		while(fabs(prev_intg - intg) > EPSILON);
		

		sprintf(buf, "z2_k%d.txt", k);
		ofstream map_out(buf);
		for(int i = 0; i < N; i+=k)
		{
			for(int j = 0; j < N; j+=k)
			{
				//cout << i << " " << j << endl;
				map_out << fi[i][j] << " ";
			}
			map_out << "\n";
		}

		//for(int i = k; i < N - k; i+=k)
		//{
			//for(int j = k; j < N - k; j+=k)
			//{
				//fi[i-k/2][j-k/2] = (fi[i-k][j] + fi[i+k][j] + fi[i][j-k] + fi[i][j+k]) / 4.;
				//fi[i+k/2][j+k/2] = (fi[i-k][j] + fi[i+k][j] + fi[i][j-k] + fi[i][j+k]) / 4.;
				//fi[i-k/2][j] = (fi[i-k][j] + fi[i+k][j]) / 2.;
				//fi[i][j-k/2] = (fi[i][j-k] + fi[i][j+k]) / 2.;
				//fi[i+k/2][j] = (fi[i-k][j] + fi[i+k][j]) / 2.;
				//fi[i][j+k/2] = (fi[i][j-k] + fi[i][j+k]) / 2.;
			//}
		//}
		//for(int i = 0; i < N-k; i += k)
		//{
			//for(int j = 0; j < N-k; j += k)
			//{
				//fi[i+k/2][j] = (fi[i][j] + fi[i+k][j]) / 2.;
				//fi[i][j+k/2] = (fi[i][j] + fi[i][j+k]) / 2.;
				//fi[i+k/2][j+k/2] = (fi[i][j] + fi[i][j+k] + fi[i+k][j] + fi[i+k][j+k]) / 4.;
			//}
		//}
		if(k != 1)
		{
			for(int i = k/2; i < N-k/2+1; i += k/2)
			{
				for(int j = k/2; j < N-k/2+1; j += k/2)
				{
					if(j % k && i % k) // w srodku
					{
						fi[i][j] = (fi[i-k/2][j-k/2] + fi[i+k/2][j-k/2] + fi[i-k/2][j+k/2] + fi[i+k/2][j+k/2]) / 4.;
					}
					else if( j % k ) // pomiedzy czarnymi dla wierszy
					{
						fi[i][j] = (fi[i][j-k/2] + fi[i][j+k/2]) / 2.;
					}
					else if( i % k ) // pomiedzy czarnymi dla kolumn
					{
						fi[i][j] = (fi[i+k/2][j] + fi[i-k/2][j]) / 2.;
					}
				}
			}
		}
					
					
		map_out.close();
	}
	
}

int main()
{
	z2();
}
