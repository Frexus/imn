#include <cstdlib>
#include <cstdio>
#include <cmath>
#include <iostream>
#include <fstream>
#include <sstream>

#include "nrutil.h"
#include "nrutil.c"
#include "gaussj.c"

using namespace std;

#define DU 0.0001

double a[2][2] = {   { 0.25, 0.25-sqrt(3.)/6. },
					 { 0.25 + sqrt(3.)/6.0, 0.25 }
			     };
double b[2] = { 0.5, 0.5 };
double c[2] = { 0.5-sqrt(3.)/6.0, 0.5+sqrt(3.)/6.0 };
double d[2][2] = { { 1, 0 },
	               { 0, 1 }
	             };

double f(double t,double u)
{
	return u*(u-1)*(u-2);
}

double dfdu(double t,double u)
{
	return (f(t, u + DU) - f(t, u))/DU;
}

double F1(double U1,double U2,double t,double u,double dt)
{
	return U1-u-dt*(a[0][0]*f(t+c[0]*dt,U1)+a[0][1]*f(t+c[1]*dt,U2));
}

double F2(double U1,double U2,double t,double u,double dt)
{
	return U2-u-dt*(a[1][0]*f(t+c[0]*dt,U1)+a[1][1]*f(t+c[1]*dt,U2));
}

double dFdU(double U,double t,double dt,int k,int l)
{
	--k;
	--l;
	return d[k][l] -dt*a[k][l]*dfdu(t+dt*c[l],U);
}

double correct_un(double U1,double U2,double t,double u,double dt)
{
	return u+dt*(b[0]*f(t+c[0]*dt,U1)+b[1]*f(t+c[1]*dt,U2));
}

void niejawneRK(double u0, double tol, double dt, double T, string filename, bool print_first_step = false)
{
	double u = u0;
	double U1,U2;

	int iter;
	double err;

	float **A = matrix(1,2,1,2);
    float **B = matrix(1,2,1,1);
	ofstream file;
	if(!filename.empty())
		file.open(filename.c_str());

	for(double t = 0; t <= T ; t += dt)
	{
		U1 = u;
		U2 = u;
		iter = 0;
		do
		{
			if(t < t+dt && print_first_step) cout << U1 << " " << U2 << endl;
			A[1][1] = dFdU(U1,t,dt,1,1);	A[1][2] = dFdU(U2,t,dt,1,2);
			A[2][1] = dFdU(U1,t,dt,2,1);	A[2][2] = dFdU(U2,t,dt,2,2);
			B[1][1] = -F1(U1,U2,t,u,dt);	B[2][1] = -F2(U1,U2,t,u,dt);
			
			gaussj(A,2,B,1);
			
			err = max(fabs(B[1][1]), fabs(B[2][1]));
			
			U1 = U1 + B[1][1];
			U2 = U2 + B[2][1];
		}
		while(err > tol);
		u = correct_un(U1,U2,t,u,dt);
		double dokladne = pow(t+dt, 4);
		if(!filename.empty())
			file << t << " " << u << " " << dokladne << " " << fabs(dokladne - u) << "\n";

	}

    free_matrix(A,1,2,1,2);
    free_matrix(B,1,2,1,1);
}

int main()
{
	niejawneRK(1.33, 0.0001, 1, 8, "", true);
	int i = 0;
	for(double u = 0; u <= 2.1; u += 0.2) 
	{
		ostringstream str;
		str << "z2_u" << i++ << ".txt";
		string filename = str.str();
		niejawneRK(u, 0.0001, 0.4, 8., filename);
	}
	return 0;
}
