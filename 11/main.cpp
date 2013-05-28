#include <iostream>
#include <fstream>
#include <cmath>
#include <sstream>
#include "nrutil.c"

using namespace std;

const double _y1 = -0.4;
const double _y2 = 0.4;
const double Q = -1.;
const double mu = 1.;
const double dx = 0.01;
const int xmax = 200;
const int ymax = 40;
const int ymin = -40;
const int xmin = -100;
const int id = 5;
const int jd = 0;
const int ig = 20;
const int jg = 20;

void zad1()
{
	double** Vx = 	dmatrix(xmin-1, xmax+1, ymin-1, ymax+1);
	double** Vy = 	dmatrix(xmin-1, xmax+1, ymin-1, ymax+1);
	double** unp1 = dmatrix(xmin-1, xmax+1, ymin-1, ymax+1);
	double** un = 	dmatrix(xmin-1, xmax+1, ymin-1, ymax+1);
	double** unm1 = dmatrix(xmin-1, xmax+1, ymin-1, ymax+1);
	double dt = 0;

	ofstream calka("z1i.dat");
	ofstream srodek("z1srodek.dat");

	for(int i = xmin; i <= xmax; ++i)
	{
		for(int j = ymin; j <= ymax; ++j)
		{
			double x = i * dx;
			double y = j * dx;

			Vx[i][j] = (Q / (2. * mu)) * (y - _y1) * (y - _y2);
			Vy[i][j] = 0;

			double tmp = sqrt(pow(Vx[i][j], 2.) + pow(Vy[i][j], 2.));
			dt = tmp > dt ? tmp : dt;
		}
	}

	dt = dx / (4. * dt);
	cout << "DT: " << dt << endl;

	for (int i = xmin; i <= xmax; ++i)
	{
		for (int j = ymin; j <= ymax; ++j)
		{

			double x = i * dx;
			double y = j * dx;

			unm1[i][j] = exp(-25.*(pow(x+0.6,2)+pow(y,2)));
			un[i][j] = exp(-25.*(pow((x - Vx[i][j] * dt) + 0.6, 2)+pow(y - Vy[i][j] * dt, 2)));
		}
	}

	ofstream pocz("z1test.dat");
	for (int i = xmin; i <= xmax; ++i)
	{
		for (int j = ymin; j <= ymax; ++j)
		{
			pocz << i << " " << j << " " << un[i][j] << '\n';
		}
		pocz << '\n';
	}

	int it = 0;
	for (double t = 0; t <= 100; t += dt)
	{
		double I = 0;
		double iks = 0;
		for(int i = xmin; i <= xmax; ++i)
		{
			for(int j = ymin; j <= ymax; ++j)
			{
				int ip1_idx = (i+1) == (xmax + 1) ? xmin : (i + 1);
				int im1_idx = (i-1) == (xmin - 1) ? xmax : (i - 1);
				int jp1_idx = (j+1) == (ymax + 1) ? ymin : (j + 1);
				int jm1_idx = (j-1) == (ymin - 1) ? ymax : (j - 1);
				
				unp1[i][j] = unm1[i][j] - dt * (Vx[i][j] * ((un[ip1_idx][j] - un[im1_idx][j]) / dx) + Vy[i][j] * ((un[i][jp1_idx] - un[i][jm1_idx]) / dx));
				I += unp1[i][j];
				iks += i * dx * unp1[i][j];
			}
		}

		for(int i = xmin; i <= xmax; ++i)
		{
			for(int j = ymin; j <= ymax; ++j)
			{
				unm1[i][j] = un[i][j];
				un[i][j] = unp1[i][j];
			}
		}

		calka << t << " " << I * dx * dx << "\n";
		srodek << t << " " << (iks * dx * dx) / I << "\n";

		if(it == 0 || it == 200 || it == 320 || it == 600)
		{
			char buf[256];
			sprintf(buf, "z1u%d.dat", it);
			ofstream ciecz(buf);
			for(int i = xmin; i <= xmax; ++i)
			{
				for(int j = ymin; j <= ymax; ++j)
				{
					ciecz << i << " " << j << " " << unp1[i][j] << '\n';
				}
				ciecz << '\n';
			}
		}
		it++;
	}
	char buf[256];
	sprintf(buf, "z1u%d.dat", it);
	ofstream ciecz(buf);
	for(int i = xmin; i <= xmax; ++i)
	{
		for(int j = ymin; j <= ymax; ++j)
		{
			ciecz << i << " " << j << " " << unp1[i][j] << '\n';
		}
		ciecz << '\n';
	}
}

void czytaj_predkosc(const char* predkosc, double** Vx, double** Vy)
{
    FILE * fp = fopen(predkosc,"r");
    int i,j;
    double k,l;
    for(int i = xmin; i <= xmax; i++)
    {
        for(int j = ymin; j <= ymax; j++)
        {
            fscanf(fp,"%lf %lf %lf %lf",&k,&l,&Vx[i][j],&Vy[i][j]);
        }
    }
    fclose(fp);
 //    ofstream test("z2predkosc.dat.in");
 //    for (int i = xmin; i <= xmax; ++i)
	// {
	// 	for (int j = ymin; j <= ymax; ++j)
	// 	{
	// 		test << i << " " << j << " " << Vx[i][j] << " " << Vy[i][j] << '\n';
	// 	}
	// 	test << '\n';
	// }
}

void zad2()
{
	double** Vx = 	dmatrix(xmin-1, xmax+1, ymin-1, ymax+1);
	double** Vy = 	dmatrix(xmin-1, xmax+1, ymin-1, ymax+1);
	double** unp1 = dmatrix(xmin-1, xmax+1, ymin-1, ymax+1);
	double** un = 	dmatrix(xmin-1, xmax+1, ymin-1, ymax+1);
	double** unm1 = dmatrix(xmin-1, xmax+1, ymin-1, ymax+1);
	double dt = 0;

	ofstream calka("z2i.dat");
	ofstream srodek("z2srodek.dat");

	czytaj_predkosc("predkosc.dat.in", Vx, Vy);

	for(int i = xmin; i <= xmax; ++i)
	{
		for(int j = ymin; j <= ymax; ++j)
		{
			double tmp = sqrt(pow(Vx[i][j], 2.) + pow(Vy[i][j], 2.));
			dt = tmp > dt ? tmp : dt;
		}
	}

	dt = dx / (4. * dt);
	cout << "DT: " << dt << endl;

	for (int i = xmin; i <= xmax; ++i)
	{
		for (int j = ymin; j <= ymax; ++j)
		{
				double x = i * dx;
				double y = j * dx;

				unm1[i][j] = exp(-25.*(pow(x+0.6,2)+pow(y,2)));
				un[i][j] = exp(-25.*(pow((x - Vx[i][j] * dt) + 0.6, 2)+pow(y - Vy[i][j] * dt, 2)));
		}
	}

	for(int i=-ig+1;i<ig;i++){ 
		for(int j=jg+1;j<ymax-1;j++){ 
			unm1[i][j]=1.0; 
			un[i][j]=1.0; 
		} 
	} 
	
	for(int i=-id+1;i<id;i++){ 
		for(int j=ymin+1;j<jd;j++){ 
			unm1[i][j]=1.0; 
			un[i][j]=1.0; 
		} 
	}


	// ofstream pocz("z2test.dat");
	// for (int i = xmin; i <= xmax; ++i)
	// {
	// 	for (int j = ymin; j <= ymax; ++j)
	// 	{
	// 		pocz << i << " " << j << " " << un[i][j] << '\n';
	// 	}
	// 	pocz << '\n';
	// }

	int it = 0;
	for (double t = 0; t <= 100; t += dt)
	{
		double iks = 0;
		double I = 0;
		for(int i = xmin+1; i < xmax; ++i)
		{
			for(int j = ymin+1; j < ymax; ++j)
			{
				//if(  (i < -ig || i > ig || j < jg) && (i < -id || i > id || j > jd) )
				{
					int ip1_idx = (i+1) == (xmax + 1) ? xmin : (i + 1);
					int im1_idx = (i-1) == (xmin - 1) ? xmax : (i - 1);
					int jp1_idx = (j+1) == (ymax + 1) ? ymin : (j + 1);
					int jm1_idx = (j-1) == (ymin - 1) ? ymax : (j - 1);

					unp1[i][j] = unm1[i][j] - dt * (Vx[i][j] * ((un[ip1_idx][j] - un[im1_idx][j]) / dx) + Vy[i][j] * ((un[i][jp1_idx] - un[i][jm1_idx]) / dx));
					I += unp1[i][j];
					iks += i * dx * unp1[i][j];
				}
				//else
				{
					//unp1[i][j] = 1;
				}
			}
		}

		for(int i = xmin; i <= xmax; ++i)
		{
			for(int j = ymin; j <= ymax; ++j)
			{
				unm1[i][j] = un[i][j];
				un[i][j] = unp1[i][j];
			}
		}

		calka << t << " " << I * dx * dx << "\n";
		srodek << t << " " << (iks * dx * dx) / I << "\n";

		if(it == 0 || it == 200 || it == 320 || it == 600 || it == 1300)
		{
			char buf[256];
			sprintf(buf, "z2u%d.dat", it);
			ofstream ciecz(buf);
			for(int i = xmin; i <= xmax; ++i)
			{
				for(int j = ymin; j <= ymax; ++j)
				{
					ciecz << i << " " << j << " " << unp1[i][j] << '\n';
				}
				ciecz << '\n';
			}
		}
		it++;
	}
	char buf[256];
	sprintf(buf, "z2u%d.dat", it);
	ofstream ciecz(buf);
	for(int i = xmin; i <= xmax; ++i)
	{
		for(int j = ymin; j <= ymax; ++j)
		{
			ciecz << i << " " << j << " " << unp1[i][j] << '\n';
		}
		ciecz << '\n';
	}
}

void zad3()
{

	double** Vx = 	dmatrix(xmin-1, xmax+1, ymin-1, ymax+1);
	double** Vy = 	dmatrix(xmin-1, xmax+1, ymin-1, ymax+1);
	double** unp1 = dmatrix(xmin-1, xmax+1, ymin-1, ymax+1);
	double** un = 	dmatrix(xmin-1, xmax+1, ymin-1, ymax+1);
	double** unm1 = dmatrix(xmin-1, xmax+1, ymin-1, ymax+1);
	double dt = 0;

	ofstream calka("z3i.dat");
	ofstream srodek("z3srodek.dat");

	czytaj_predkosc("predkosc.dat.in", Vx, Vy);

	for(int i = xmin; i <= xmax; ++i)
	{
		for(int j = ymin; j <= ymax; ++j)
		{
			double tmp = sqrt(pow(Vx[i][j], 2.) + pow(Vy[i][j], 2.));
			dt = tmp > dt ? tmp : dt;
		}
	}

	dt = dx / (4. * dt);
	dt /= 2;
	cout << "DT/2: " << dt << endl;

	for (int i = xmin; i <= xmax; ++i)
	{
		for (int j = ymin; j <= ymax; ++j)
		{
				double x = i * dx;
				double y = j * dx;

				unm1[i][j] = exp(-25.*(pow(x+0.6,2)+pow(y,2)));
				un[i][j] = exp(-25.*(pow((x - Vx[i][j] * dt) + 0.6, 2)+pow(y - Vy[i][j] * dt, 2)));
		}
	}

	for(int i=-ig+1;i<ig;i++){ 
		for(int j=jg+1;j<ymax-1;j++){ 
			unm1[i][j]=1.0; 
			un[i][j]=1.0; 
		} 
	} 
	
	for(int i=-id+1;i<id;i++){ 
		for(int j=ymin+1;j<jd;j++){ 
			unm1[i][j]=1.0; 
			un[i][j]=1.0; 
		} 
	}

	int it = 0;
	for (double t = 0; t <= 100; t += dt)
	{
		double iks = 0;
		double I = 0;
		for(int i = xmin+1; i < xmax; ++i)
		{
			for(int j = ymin+1; j < ymax; ++j)
			{
				if(  (i < -ig || i > ig || j < jg) && (i < -id || i > id || j > jd) )
				{
					int ip1_idx = (i+1) == (xmax + 1) ? xmin : (i + 1);
					int im1_idx = (i-1) == (xmin - 1) ? xmax : (i - 1);
					int jp1_idx = (j+1) == (ymax + 1) ? ymin : (j + 1);
					int jm1_idx = (j-1) == (ymin - 1) ? ymax : (j - 1);

					unp1[i][j] = (un[ip1_idx][j] + un[im1_idx][j] + un[i][jm1_idx] + un[i][jp1_idx]) / 4. - dt * (Vx[i][j] * (un[ip1_idx][j] - un[im1_idx][j]) / (2. * dx) + Vy[i][j] * (un[i][jp1_idx] - un[i][jm1_idx]) / (2. * dx));
					I += unp1[i][j];
					iks += i * dx * unp1[i][j];
				}
			}
		}

		for(int i = xmin; i <= xmax; ++i)
		{
			for(int j = ymin; j <= ymax; ++j)
			{
				unm1[i][j] = un[i][j];
				un[i][j] = unp1[i][j];
			}
		}

		calka << t << " " << I * dx * dx << "\n";
		srodek << t << " " << (iks * dx * dx) / I << "\n";

		if(it == 0 || it == 1512 || it == 2520 || it == 6000 || it == 10000)
		{
			char buf[256];
			sprintf(buf, "z3u%d.dat", it);
			ofstream ciecz(buf);
			for(int i = xmin; i <= xmax; ++i)
			{
				for(int j = ymin; j <= ymax; ++j)
				{
					ciecz << i << " " << j << " " << unp1[i][j] << '\n';
				}
				ciecz << '\n';
			}
		}
		it++;
	}
	char buf[256];
	sprintf(buf, "z3u%d.dat", it);
	ofstream ciecz(buf);
	for(int i = xmin; i <= xmax; ++i)
	{
		for(int j = ymin; j <= ymax; ++j)
		{
			ciecz << i << " " << j << " " << unp1[i][j] << '\n';
		}
		ciecz << '\n';
	}
}


int main(int argc, char const *argv[])
{
	zad1();
	zad2();
	zad3();
	return 0;
}