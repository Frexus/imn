#include <iostream>
#include <fstream>
#include "nrutil.c"
#include <cmath>

using namespace std;

#define EPS 0.0001

bool doubleEq (double a, double b)
{
	return fabs(a-b) < EPS;
}

void zad1()
{
	const int N = 100;
	const double dx = 1./100.;
	double dt = 1./200.;
	double* u = dvector(0, N);
	double* v = dvector(0, N);
	double* a = dvector(0, N);
	ofstream out;
	for(int i = 0; i <= N; ++i)
	{
		//a[i] = u[i+1] + u[i-1] - 2 * u[i];
		a[i] = 0;
		u[i] = sin(M_PI * i * dx);
		v[i] = M_PI * sin(2 * M_PI * i * dx);
	}
	for(int i = 1; i <= N-1; ++i)
	{
		//a[i] = (u[i+1] + u[i-1] - 2 * u[i])/pow(dx, 2.);
	}
	for(double t = dt; t <= 2.; t += dt)
	{
		u[0] = sin(M_PI * 0 * dx) * cos(M_PI * t) + sin(2 * M_PI * 0 * dx) * sin(2 * M_PI * t) / 2.;
		u[100] = sin(M_PI * 100 * dx) * cos(M_PI * t) + sin(2 * M_PI * 100 * dx) * sin(2 * M_PI * t) / 2.;
		for(int i = 1; i <= N-1; ++i)
		{
			v[i] = v[i] + dt/2. * a[i];
			u[i] = u[i] + dt * v[i];
		}
		for(int i = 1; i <= N-1; ++i)
		{
			a[i] = (u[i+1] + u[i-1] - 2 * u[i])/pow(dx, 2.);
			v[i] = v[i] + dt/2. * a[i];
		}
		if(doubleEq(t, 0.25) || doubleEq(t, 0.5) || doubleEq(t, 0.75) || doubleEq(t, 1) || doubleEq(t, 1.25) || doubleEq(t, 1.5) || doubleEq(t, 1.75) || doubleEq(t, 2))
		{
			char buf[256];
			sprintf(buf, "z1%.2lf_a.dat", t);
			ofstream analityczne(buf);
			for(int i = 0; i <= N; ++i)
			{
				analityczne << i * dx << "\t" << sin(M_PI * i * dx) * cos(M_PI * t) + sin(2 * M_PI * i * dx) * sin(2 * M_PI * t) / 2. << "\n";
			}
			analityczne.close();
			sprintf(buf, "z1%.2lf.dat", t);
			out.open(buf);
			for(int i = 0; i <= N; ++i)
			{
				out << i * dx << "\t" << u[i] << "\n";
			}
			out.close();
		}
	}
}

void zad2()
{
	const int N = 100;
	const double dx = 1./100.;
	double dt = 1./200.;
	double* u = dvector(0, N);
	double* v = dvector(0, N);
	double* a = dvector(0, N);
	ofstream out("z2.dat");
	for(int i = 0; i <= N; ++i)
	{
		a[i] = 0;
		u[i] = exp(-100*pow(i*dx-0.5, 2));
		v[i] = 0;
	}
	for(int i = 1; i <= N-1; ++i)
	{
		a[i] = (u[i+1] + u[i-1] - 2 * u[i])/pow(dx, 2.);
	}
	for(double t = dt; t <= 4.; t += dt)
	{
		u[0] = sin(M_PI * 0 * dx) * cos(M_PI * t) + sin(2 * M_PI * 0 * dx) * sin(2 * M_PI * t) / 2.;
		u[100] = sin(M_PI * 100 * dx) * cos(M_PI * t) + sin(2 * M_PI * 100 * dx) * sin(2 * M_PI * t) / 2.;
		for(int i = 1; i <= N-1; ++i)
		{
			v[i] = v[i] + dt/2. * a[i];
			u[i] = u[i] + dt * v[i];
		}
		for(int i = 1; i <= N-1; ++i)
		{
			a[i] = (u[i+1] + u[i-1] - 2 * u[i])/pow(dx, 2.);
			v[i] = v[i] + dt/2. * a[i];
		}
		for(int i = 0; i <= N; ++i)
		{
			out << t << " " << i*dx << " " << u[i] << '\n';
		}
		out << '\n';
	}
	out.close();
	out.open("z2b.dat");
	for(int i = 0; i <= N; ++i)
	{
		a[i] = 0;
		u[i] = exp(-100*pow(i*dx-0.5, 2));
		v[i] = 0;
	}
	for(int i = 1; i <= N-1; ++i)
	{
		a[i] = (u[i+1] + u[i-1] - 2 * u[i])/pow(dx, 2.);
	}
	for(double t = dt; t <= 4.; t += dt)
	{
		u[0] = u[1];
		u[100] = u[99];
		for(int i = 1; i <= N-1; ++i)
		{
			v[i] = v[i] + dt/2. * a[i];
			u[i] = u[i] + dt * v[i];
		}
		for(int i = 1; i <= N-1; ++i)
		{
			a[i] = (u[i+1] + u[i-1] - 2 * u[i])/pow(dx, 2.);
			v[i] = v[i] + dt/2. * a[i];
		}
		for(int i = 0; i <= N; ++i)
		{
			out << t << " " << i*dx << " " << u[i] << '\n';
		}
		out << '\n';
	}
}

void zad3(double beta)
{
	const int N = 100;
	const double dx = 1./100.;
	double dt = 1./200.;
	double* u = dvector(0, N);
	double* v = dvector(0, N);
	double* a = dvector(0, N);
	double* v2 = dvector(0, N);
	char buf[256];
	sprintf(buf, "z3b%.2lf.dat", beta);
	ofstream out(buf);
	for(int i = 0; i <= N; ++i)
	{
		a[i] = 0;
		u[i] = exp(-100*pow(i*dx-0.5, 2));
		v[i] = 0;
	}
	for(int i = 1; i <= N-1; ++i)
	{
		a[i] = (u[i+1] + u[i-1] - 2 * u[i])/pow(dx, 2.) - 2 * beta * v[i];
	}
	for(double t = dt; t <= 4.; t += dt)
	{
		u[0] = sin(M_PI * 0 * dx) * cos(M_PI * t) + sin(2 * M_PI * 0 * dx) * sin(2 * M_PI * t) / 2.;
		u[100] = sin(M_PI * 100 * dx) * cos(M_PI * t) + sin(2 * M_PI * 100 * dx) * sin(2 * M_PI * t) / 2.;
		for(int i = 1; i <= N-1; ++i)
		{
			v2[i] = v[i];
			v[i] = v[i] + dt/2. * a[i];
			u[i] = u[i] + dt * v[i];
		}
		for(int i = 1; i <= N-1; ++i)
		{
			a[i] = (u[i+1] + u[i-1] - 2 * u[i])/pow(dx, 2.) - 2 * beta * v2[i];
			v[i] = v[i] + dt/2. * a[i];
		}
		for(int i = 0; i <= N; ++i)
		{
			out << t << " " << i*dx << " " << u[i] << '\n';
		}
		out << '\n';

	}
}

double get_a(double* u, int i, double t, double dx, double omega)
{
    if(i == 50)
        return (u[i+1] + u[i-1] - 2. * u[i])/pow(dx,2) + cos(omega*t);
    else
    	return (u[i+1] + u[i-1] - 2. * u[i])/pow(dx,2);
}
void zad4(double beta)
{
	const int N = 100;
	const double dx = 1./100.;
	const double omega = M_PI/2.;
	double dt = 1./200.;
	double* u = dvector(0, N);
	double* v = dvector(0, N);
	double* v2 = dvector(0, N);
	ofstream out("z4.dat");
	for(int i = 0; i <= N; ++i)
	{
		u[i] = 0;
		v[i] = 0;
	}

	for(double t = dt; t <= 10.; t += dt)
	{
		for(int i = 1; i < N-1; ++i){
		        v2[i] = v[i] + dt / 2. * (get_a(u, i, t, dx, omega) - 2. * beta * v[i]);
		}
		
		for(int i = 1; i < N-1; ++i){
		        u[i] = u[i] + dt * v2[i];
		}
		
		for(int i = 1; i < N-1; ++i){
		        v[i] = v2[i] + dt / 2. * (get_a(u, i, t, dx, omega) - 2. * beta * v[i]);
		}

		for(int i = 0; i <= N; ++i)
		{
			out << t << " " << i*dx << " " << u[i] << '\n';
		}
		out << '\n';

	}
}

int main()
{
	zad1();
	zad2();
	zad3(0.2);
	zad3(1.);
	zad3(4.);
	zad4(1.);
	return 0;
}
