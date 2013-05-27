#include <iostream>
#include <fstream>
#include <cmath>
#define NRANSI
extern "C" {
	#include "nrutil.c"
	}

using namespace std;

#ifdef Z1
	#define Q (-1.)
#endif

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

#define EPSILON 1e-7

#ifdef Z1
void zad1()
{
	double** eta = dmatrix(XMIN, XMAX, YMIN, YMAX);
	double** phi = dmatrix(XMIN, XMAX, YMIN, YMAX);
	
	double y1 = -0.4, y2 = 0.4;
	
	for(int i = XMIN; i <= XMAX; ++i)
	{
		for(int j = YMIN; j <= YMAX; ++j)
		{
			eta[i][j] = phi[i][j] = 0;
		}
	}
	
	for(int i = XMIN; i <= XMAX; ++i)
	{
		eta[i][YMIN] = (Q / (2. * MI)) * (2. * YMIN * DX - y1 - y2);
		eta[i][YMAX] = (Q / (2. * MI)) * (2. * YMAX * DX - y1 - y2);
		phi[i][YMIN] = (Q / (2. * MI)) * (pow(YMIN * DX, 3.) / 3. - (pow(YMIN * DX, 2.) / 2.) * (y1 + y2) + y1 * y2 * YMIN * DX);
		phi[i][YMAX] = (Q / (2. * MI)) * (pow(YMAX * DX, 3.) / 3. - (pow(YMAX * DX, 2.) / 2.) * (y1 + y2) + y1 * y2 * YMAX * DX);
	}

	for(int i = YMIN; i <= YMAX; ++i)
	{
		double y = i * DX;
		eta[XMIN][i] = (Q / (2. * MI)) * (2. * y - y1 - y2);
		eta[XMAX][i] = (Q / (2. * MI)) * (2. * y - y1 - y2);
		phi[XMIN][i] = (Q / (2. * MI)) * ((pow(y, 3.) / 3.) - (pow(y, 2.) / 2.) * (y1 + y2) + y1 * y2 * y);
		phi[XMAX][i] = (Q / (2. * MI)) * ((pow(y, 3.) / 3.) - (pow(y, 2.) / 2.) * (y1 + y2) + y1 * y2 * y);
	}
	
	ofstream test1("inite.dat");
	ofstream test2("initp.dat");
	
	int it = 0;
	double diff_eta = 100;
	double diff_phi = 100;
	
	for(int i = XMIN; i <= XMAX; ++i)
	{
		for(int j = YMIN; j <= YMAX; ++j)
		{	
			test1 << eta[i][j] << "\t";
			test2 << phi[i][j] << "\t";
		}
		test1 << "\n";
		test2 << "\n";
	}
	double preveta, prevphi;
	
	do 
	{
		preveta = eta[50][0];
		prevphi = phi[50][0];
		for(int i = XMIN + 1; i < XMAX; ++i)
		{
			for(int j = YMIN + 1; j < YMAX; ++j)
			{
				eta[i][j] = ((eta[i+1][j] + eta[i-1][j] + eta[i][j-1] + eta[i][j+1]) / 4.) -
							(
							((phi[i][j+1] - phi[i][j-1]) * (eta[i+1][j] - eta[i-1][j])) -
							((phi[i+1][j] - phi[i-1][j]) * (eta[i][j+1] - eta[i][j-1]))
							) / 16.;
				phi[i][j] = (phi[i+1][j] + phi[i-1][j] + phi[i][j-1] + phi[i][j+1] - eta[i][j] * DX * DX) / 4.;
			}
		}
		++it;
		if(it > 200)
		{
			diff_eta = fabs(preveta - eta[50][0]);
			diff_phi = fabs(prevphi - phi[50][0]);
			//cout << phi[50][0] << "\t" << diff_eta << "\t" << diff_phi << "\n";
		}
	}
	while(diff_eta > EPSILON || diff_phi > EPSILON);
	
	cout << "it: " << it << endl;
	ofstream e("z1e.dat");
	ofstream p("z1p.dat");
	ofstream u("z1u.dat");
	ofstream e_a("z1e_a.dat");
	ofstream p_a("z1p_a.dat");
	
	for(int i = YMIN+1; i < YMAX; ++i)
	{
		e << i << "\t" << eta[0][i] << "\t" << eta[70][i] << "\n";
		p << i << "\t" << phi[0][i] << "\t" << phi[70][i] << "\n";
		u << i << "\t" << (Q / (2. * MI)) * (i*DX - y1) * (i*DX - y2) << "\t" << (phi[0][i+1] - phi[0][i-1]) / (2. * DX) <<"\n";
	}

	
	for(int i = XMIN; i <= XMAX; ++i)
	{
		for(int j = YMIN; j <= YMAX; ++j)
		{
				
			eta[i][j] = (Q / (2. * MI)) * (2. * j * DX - YMIN * DX - YMAX * DX);
			phi[i][j] = (Q / (2. * MI)) * (pow(j * DX, 3) / 3. - (pow(j * DX, 2) / 2.) * (YMIN * DX + YMAX * DX) + YMIN * DX * YMAX * DX * j * DX);
		}
	}
	
	for(int i = YMIN; i <= YMAX; ++i)
	{
		e_a << i << "\t" << eta[0][i] << "\t" << eta[70][i] << "\n";
		p_a << i << "\t" << phi[0][i] << "\t" << phi[70][i] << "\n";
	}
	
	free_dmatrix(eta, XMIN, XMAX, YMIN, YMAX);
	free_dmatrix(phi, XMIN, XMAX, YMIN, YMAX);
}
#endif
#ifdef Z2
void zad2(double Q)
{
	double** eta = dmatrix(XMIN, XMAX, YMIN, YMAX);
	double** phi = dmatrix(XMIN, XMAX, YMIN, YMAX);
	
	for(int i = XMIN; i <= XMAX; ++i)
	{
		for(int j = YMIN; j <= YMAX; ++j)
		{
			eta[i][j] = (Q / (2. * MI)) * (2. * j * DX - YMIN * DX - YMAX * DX);
			phi[i][j] = (Q / (2. * MI)) * ((pow(j * DX, 3.) / 3.) - (pow(j * DX, 2.) / 2.) * (YMIN * DX + YMAX * DX) + YMIN * DX * YMAX * DX * j * DX);
		}
	}
	/*
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
	*/
	double dol = (Q / (2. * MI)) * (pow(YMIN * DX, 3.) / 3. - (pow(YMIN * DX, 2.) / 2.) * (YMIN * DX + YMAX * DX) + YMIN * DX * YMAX * DX * YMIN * DX);
	double gora = (Q / (2. * MI)) * (pow(YMAX * DX, 3.) / 3. - (pow(YMAX * DX, 2.) / 2.) * (YMIN * DX + YMAX * DX) + YMIN * DX * YMAX * DX * YMAX * DX);
	
	for(int i = XMIN; i <= XMAX; ++i)
		{
			eta[i][YMIN] = dol;
			eta[i][YMAX] = gora;
			
			if(i >= -IG || i <= IG)
				eta[i][JG] = gora;
			
			if(i >= -ID || i <= ID)
				eta[i][JD] = dol;
		}
		
	for(int i = YMIN; i <= JD; ++i)
	{
		eta[-ID][i] = dol;
		eta[ID][i] = dol;
	}
	for(int i = JG; i <= YMAX; ++i)
	{
		eta[-IG][i] = gora;
		eta[IG][i] = gora;
	}

	for(int i = YMIN; i <= YMAX; ++i)
	{
		double y = i * DX;
		eta[XMIN][i] = (Q / (2. * MI)) * (2. * y - YMIN * DX - YMAX * DX);
		eta[XMAX][i] = (Q / (2. * MI)) * (2. * y - YMIN * DX - YMAX * DX);
		phi[XMIN][i] = (Q / (2. * MI)) * (pow(y, 3) / 3. - (pow(y, 2) / 2.) * (YMIN * DX + YMAX * DX) + YMIN * DX * YMAX * DX * y);
		phi[XMAX][i] = (Q / (2. * MI)) * (pow(y, 3) / 3. - (pow(y, 2) / 2.) * (YMIN * DX + YMAX * DX) + YMIN * DX * YMAX * DX * y);
	}
	int it = 0;
	double diff_eta = 100;
	double diff_phi = 100;
	do
	{
		double preveta = eta[50][0];
		double prevphi = phi[50][0];
		/*
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
		}*/
		//gora i dol
		for(int i = XMIN; i <= XMAX; ++i)
		{
			if(i < -IG || i > IG)
				eta[i][40] = (2. * (phi[i][39] - phi[i][40])) / (DX * DX);
			else
				eta[i][JG] = (2. * (phi[i][JG-1] - phi[i][JG])) / (DX * DX);
			
			if(i < -ID || i > ID)
				eta[i][-40] = (2. * (phi[i][-39] - phi[i][-40])) / (DX * DX);
			else
				eta[i][JD] = (2. * (phi[i][JD+1] - phi[i][JD])) / (DX * DX);
		}
	
		// boki
		for(int i = YMIN; i <= YMAX; ++i)
		{
			eta[XMIN][i] = (Q / (2. * MI)) * (2. * i * DX - YMIN * DX - YMAX * DX);
			eta[XMAX][i] = (Q / (2. * MI)) * (2. * i * DX - YMIN * DX - YMAX * DX);
			if(i < JD)
			{
				eta[-ID][i] = (2. * (phi[-ID-1][i] - phi[-ID][i])) / (DX * DX);
				eta[ID][i] = (2. * (phi[ID+1][i] - phi[ID][i])) / (DX * DX);
			}
			
			if(i > JG)
			{
				eta[IG][i] = (2. * (phi[IG+1][i] - phi[IG][i])) / (DX * DX);
				eta[-IG][i] = (2. * (phi[-IG-1][i] - phi[-IG][i])) / (DX * DX);
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
				if(  (i < -IG || i > IG || j < JG) && (i < -ID || i > ID || j > JD) )
				{ 
				eta[i][j] = ((eta[i+1][j] + eta[i-1][j] + eta[i][j-1] + eta[i][j+1]) / 4.) -
							(
							((phi[i][j+1] - phi[i][j-1]) * (eta[i+1][j] - eta[i-1][j])) -
							((phi[i+1][j] - phi[i-1][j]) * (eta[i][j+1] - eta[i][j-1]))
							) / 16.;
				phi[i][j] = (phi[i+1][j] + phi[i-1][j] + phi[i][j-1] + phi[i][j+1] - eta[i][j] * DX * DX) / 4.;
				}
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
	cout << "iter: " << it << "\n";
	char buf[250];
	sprintf(buf, "z2p%.0lf.dat", Q);
	ofstream p(buf);
	
		for(int i = XMIN + 1; i < XMAX; ++i)
		{
			for(int j = YMIN + 1; j < YMAX; ++j)
			{
				if(  !((i < -IG || i > IG || j < JG) && (i < -ID || i > ID || j > JD)) )
				{ 
				eta[i][j] = 0;
				phi[i][j] = 0;
				}
			}
		}
	
	for(int i = XMIN ; i <= XMAX; ++i)
	{
		for(int j = YMIN ; j <= YMAX; ++j)
		{
			p << i*DX << "\t" << j*DX << "\t" << phi[i][j] << "\n";
		}
		p << "\n";
	}
	
}
#endif
int main()
{
	#ifdef Z1
	zad1();
	#endif
	#ifdef Z2
	zad2(-500);
	zad2(-350);
	zad2(-200);
	zad2(-100);
	zad2(-1);
	#endif
}
