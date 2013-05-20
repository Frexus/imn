#include <iostream>
#include <fstream>
#include <cmath>
#include "nrutil.c"

using namespace std;

#define Q (-1.)
#define MI 1.

#define XMIN (-100)
#define XMAX (200)
#define YMIN (-40)
#define YMAX 40
#define DX 0.01

#define ID 5
#define JD 0
#define IG 20
#define JG 20

#define EPSILON 10e-7

void zad1()
{
	double** eta = dmatrix(XMIN, XMAX, YMIN, YMAX);
	double** phi = dmatrix(XMIN, XMAX, YMIN, YMAX);
	
	for(int i = XMIN; i <= XMAX; ++i)
	{
		for(int j = YMIN; j <= YMAX; ++j)
		{
			eta[i][j] = phi[i][j] = 0;
		}
	}
	
	for(int i = XMIN; i <= XMAX; ++i)
	{
		eta[i][YMIN] = (Q / (2. * MI)) * (2. * YMIN * DX - YMIN * DX - YMAX * DX);
		eta[i][YMAX] = (Q / (2. * MI)) * (2. * YMAX * DX - YMIN * DX - YMAX * DX);
		phi[i][YMIN] = (Q / (2. * MI)) * (pow(YMIN * DX, 3) / 3. - (pow(YMIN * DX, 2) / 2.) * (YMIN * DX + YMAX * DX) + YMIN * DX * YMAX * DX * YMIN * DX);
		phi[i][YMAX] = (Q / (2. * MI)) * (pow(YMAX * DX, 3) / 3. - (pow(YMAX * DX, 2) / 2.) * (YMIN * DX + YMAX * DX) + YMIN * DX * YMAX * DX * YMAX * DX);
	}

	for(int i = YMIN; i <= YMAX; ++i)
	{
		eta[XMIN][i] = (Q / (2. * MI)) * (2. * i * DX - YMIN * DX - YMAX * DX);
		eta[XMAX][i] = (Q / (2. * MI)) * (2. * i * DX - YMIN * DX - YMAX * DX);
		phi[XMIN][i] = (Q / (2. * MI)) * (pow(i * DX, 3) / 3. - (pow(i * DX, 2) / 2.) * (YMIN * DX + YMAX * DX) + YMIN * DX * YMAX * DX * i * DX);
		phi[XMAX][i] = (Q / (2. * MI)) * (pow(i * DX, 3) / 3. - (pow(i * DX, 2) / 2.) * (YMIN * DX + YMAX * DX) + YMIN * DX * YMAX * DX * i * DX);
	}
	
	int it = 0;
	double diff_eta = 100;
	double prevdiff_eta, prevdiff_phi;
	double diff_phi = 100;
	do 
	{
		double preveta = eta[50][0];
		double prevphi = phi[50][0];
		cout << eta[50][0] << "\n";
		for(int i = XMIN + 1; i < XMAX; ++i)
		{
			for(int j = YMIN + 1; j < YMAX; ++j)
			{
				phi[i][j] = (phi[i+1][j] + phi[i-1][j] + phi[i][j-1] + phi[i][j+1] - eta[i][j] * DX * DX) / 4.;
				eta[i][j] = (eta[i+1][j] + eta[i-1][j] + eta[i][j-1] + eta[i][j+1]) / 4. - (1./16.) *
							(
							(phi[i][j+1] - phi[i][j-1]) * (eta[i+1][j] - eta[i-1][j]) -
							(phi[i+1][j] - phi[i-1][j]) * (eta[i][j+1] - eta[i][j-1])
							);
			}
		}
		++it;
		if(it > 200)
		{
			diff_eta = fabs(preveta - eta[50][0]);
			diff_phi = fabs(prevphi - phi[50][0]);
		}
	}
	while(diff_eta > EPSILON || diff_phi > EPSILON);
	
	ofstream e("z1e.dat");
	ofstream p("z1p.dat");
	ofstream u("z1u.dat");
	ofstream e_a("z1e_a.dat");
	ofstream p_a("z1p_a.dat");
	
	for(int i = YMIN; i <= YMAX; ++i)
	{
		e << i << "\t" << eta[0][i] << "\t" << eta[50][i] << "\n";
		p << i << "\t" << phi[0][i] << "\t" << phi[50][i] << "\n";
		u << i << "\t" << (Q / (2 * MI)) * (i - YMIN) * (i - YMAX) << (phi[0][i > YMIN ? i - 1 : i] - phi[0][i < YMAX ? i + 1 : i]) / DX <<"\n";
	}

	
	for(int i = XMIN + 1; i < XMAX; ++i)
	{
		for(int j = YMIN + 1; j < YMAX; ++j)
		{
				
			eta[i][j] = (Q / (2. * MI)) * (2. * j * DX - YMIN * DX - YMAX * DX);
			phi[i][j] = (Q / (2. * MI)) * (pow(j * DX, 3) / 3. - (pow(j * DX, 2) / 2.) * (YMIN * DX + YMAX * DX) + YMIN * DX * YMAX * DX * j * DX);
		}
	}
	
	for(int i = YMIN; i <= YMAX; ++i)
	{
		e_a << i << "\t" << eta[0][i] << "\t" << eta[50][i] << "\n";
		p_a << i << "\t" << phi[0][i] << "\t" << phi[50][i] << "\n";
	}
	
	free_dmatrix(eta, XMIN, XMAX, YMIN, YMAX);
	free_dmatrix(phi, XMIN, XMAX, YMIN, YMAX);
}

void zad2()
{
	double** eta = dmatrix(XMIN, XMAX, YMIN, YMAX);
	double** phi = dmatrix(XMIN, XMAX, YMIN, YMAX);
	
	for(int i = XMIN; i <= XMAX; ++i)
	{
		for(int j = YMIN; j <= YMAX; ++j)
		{
			eta[i][j] = phi[i][j] = 0;
		}
	}
	
	for(int i = XMIN; i <= XMAX; ++i)
	{
		if(i < -ID || i > ID)
		{
			phi[i][YMIN] = (Q / (2. * MI)) * (pow(YMIN * DX, 3) / 3. - (pow(YMIN * DX, 2) / 2.) * (YMIN * DX + YMAX * DX) + YMIN * DX * YMAX * DX * YMIN * DX);
		}
		else
		{
			phi[i][JD+1] = (Q / (2. * MI)) * (pow(YMIN * DX, 3) / 3. - (pow(YMIN * DX, 2) / 2.) * (YMIN * DX + YMAX * DX) + YMIN * DX * YMAX * DX * YMIN * DX);
		}
		if(i < -IG || i > IG)
		{
			phi[i][YMAX] = (Q / (2. * MI)) * (pow(YMAX * DX, 3) / 3. - (pow(YMAX * DX, 2) / 2.) * (YMIN * DX + YMAX * DX) + YMIN * DX * YMAX * DX * YMAX * DX);
		}
		else
		{
			phi[i][JG-1] = (Q / (2. * MI)) * (pow(YMAX * DX, 3) / 3. - (pow(YMAX * DX, 2) / 2.) * (YMIN * DX + YMAX * DX) + YMIN * DX * YMAX * DX * YMAX * DX);
		}
	}

	for(int i = YMIN; i <= YMAX; ++i)
	{
		eta[XMIN][i] = (Q / (2. * MI)) * (2. * i * DX - YMIN * DX - YMAX * DX);
		eta[XMAX][i] = (Q / (2. * MI)) * (2. * i * DX - YMIN * DX - YMAX * DX);
		phi[XMIN][i] = (Q / (2. * MI)) * (pow(i * DX, 3) / 3. - (pow(i * DX, 2) / 2.) * (YMIN * DX + YMAX * DX) + YMIN * DX * YMAX * DX * i * DX);
		phi[XMAX][i] = (Q / (2. * MI)) * (pow(i * DX, 3) / 3. - (pow(i * DX, 2) / 2.) * (YMIN * DX + YMAX * DX) + YMIN * DX * YMAX * DX * i * DX);
	}
	int it = 0;
	double diff_eta = 100;
	double prevdiff_eta = 0, prevdiff_phi = 0;
	double diff_phi = 100;
	do
	{
		double preveta = eta[50][0];
		double prevphi = phi[50][0];
		
		for(int i = XMIN; i <= XMAX; ++i)
		{
			for(int j = YMIN; j <= YMAX; ++j)
			{
				if(j == -40)
					eta[i][j] = (2. * (phi[i][-39] - phi[i][-40])) / (DX * DX);
				else if(j == 40)
					eta[i][j] = (2. * (phi[i][39] - phi[i][40])) / (DX * DX);
				else if(j == JD)
					eta[i][j] = (2. * (phi[i][JD+1] - phi[i][JD])) / (DX * DX);
				else if(j == JG)
					eta[i][j] = (2. * (phi[i][JG-1] - phi[i][JG])) / (DX * DX);
				else if(j != 39 && j != -39 && j != JD+1 && j != JG-1)
				{
					if(i == -ID)
						eta[i][j] = (2. * (phi[-ID-1][j] - phi[-ID][j])) / (DX * DX);
					if(i == -IG)
						eta[i][j] = (2. * (phi[-IG-1][j] - phi[-IG][j])) / (DX * DX);
					if(i == ID)
						eta[i][j] = (2. * (phi[ID+1][j] - phi[ID][j])) / (DX * DX);
					if(i == IG)
						eta[i][j] = (2. * (phi[IG+1][j] - phi[IG][j])) / (DX * DX);
				}
			}
		}
		eta[-ID][JD] = ((2. * (phi[-ID-1][JD] - phi[-ID][JD])) / (DX * DX) + (2. * (phi[-ID][JD+1] - phi[-ID][JD])) / (DX * DX)) / 2.;
		eta[ID][JD] = ((2. * (phi[ID+1][JD] - phi[ID][JD])) / (DX * DX) + (2. * (phi[ID][JD+1] - phi[ID][JD])) / (DX * DX)) / 2.;
		eta[-IG][JG] = ((2. * (phi[-IG-1][JG] - phi[-IG][JG])) / (DX * DX) + (2. * (phi[-IG][JG+1] - phi[-IG][JG])) / (DX * DX)) / 2.;
		eta[IG][JG] = ((2. * (phi[IG+1][JG] - phi[IG][JG])) / (DX * DX) + (2. * (phi[IG][JG+1] - phi[IG][JG])) / (DX * DX)) / 2.;

		for(int i = XMIN + 1; i < XMAX; ++i)
		{
			for(int j = YMIN + 1; j < YMAX; ++j)
			{
				if(j <= JG && i <= -IG && i >= IG && j >= JD && i <= -ID && i >= ID)
				{ 
					eta[i][j] = (eta[i+1][j] + eta[i-1][j] + eta[i][j-1] + eta[i][j+1]) / 4. - (1./16.) *
								((phi[i][j+1] - phi[i][j-1]) * (eta[i+1][j] - eta[i-1][j]) -
								(phi[i+1][j] - phi[i-1][j]) * (eta[i][j+1] - eta[i][j-1]));
					phi[i][j] = (phi[i+1][j] + phi[i-1][j] + phi[i][j-1] + phi[i][j+1] - eta[i][j] * DX * DX) / 4.;
				}
				else
				{
					eta[i][j] = 0;
				}
			}
		}
		++it;
		if(it > 100)
		{
			prevdiff_eta = diff_eta;
			prevdiff_phi = diff_phi;
			diff_eta = fabs(preveta - eta[50][0]);
			diff_phi = fabs(prevphi - phi[50][0]);
		}
	}
	while(diff_eta > EPSILON || diff_phi > EPSILON);
	
	ofstream p("z2p1.dat");
	
	for(int i = YMIN ; i <= YMAX; ++i)
	{
		for(int j = XMIN ; j <= XMAX; ++j)
		{
			p << phi[i][j] << " ";
		}
		p << "\n";
	}
	
}

int main()
{
	#ifdef Z1
	zad1();
	#endif
	#ifdef Z2
	zad2();
	#endif
}
