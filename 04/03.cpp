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
double L1 = 1.;
double L2 = 0.001;

double f1(double t,double u1, double u2)
{
	return -L1 * u1 + L2 * u2 + L1/2.;
}

double f2(double t, double u1, double u2)
{
	return -L2 * u2;
}

void niejawneRK(double u01, double u02, double tol, double dt, double T, string filename, bool print_first_step = false)
{
	double u1 = u01, u2 = u02;
	double U1_1,U2_1, U1_2, U2_2;

	int iter;
	double err;

	float **A = matrix(1,4,1,4);
    float **B = matrix(1,4,1,1);
	ofstream file;
	if(!filename.empty())
		file.open(filename.c_str());

	for(double t = 0; t <= T ; t += dt)
	{
		U1_1 = U1_2 = u1;
		U2_1 = U2_2 = u2;

			
			A[1][1] = 1 + L1 * a[0][0] * dt;	A[1][2] = -L2 * a[0][0] * dt;	A[1][3] = L1 * a[0][1] * dt;	A[1][4] = -L2 * a[0][1] * dt;
			A[2][1] = L1 * a[1][0] * dt;		A[2][2] = -L2 * a[1][0] * dt;	A[2][3] = 1 + L1 * a[1][1] * dt;A[2][4] = -L2 * a[1][1] * dt;
			A[3][1] = 0;						A[3][2] = 1 + L2 * a[0][0] * dt;A[3][3] = 0;					A[3][4] = L2 * a[0][1] * dt;
			A[4][1] = 0;						A[4][2] = L2 * a[1][0] * dt;	A[4][3] = 0;					A[4][4] = 1 + L2 * a[1][1] * dt;
			
			B[1][1] = u1 + (dt * L1) * (a[0][0] + a[0][1]) / 2.;
			B[2][1] = u1 + (dt * L1) * (a[1][0] + a[1][1]) / 2.;
			B[3][1] = u2;
			B[4][1] = u2;
			
			gaussj(A,4,B,1);
			
			err = max(fabs(B[1][1]), max(fabs(B[2][1]), max(fabs(B[3][1]), fabs(B[4][1]))));
			
			U1_1 = U1_1 + B[1][1];
			U1_2 = U1_2 + B[3][1];
			U2_1 = U2_1 + B[2][1];
			U2_2 = U2_2 + B[4][1];
			cout << err << endl;

		u1 = u1 + (dt / 2.) * (f1(t, U1_1, U2_1) + f1(t, U1_2, U2_2));
		u2 = u2 + (dt / 2.) * (f2(t, U1_1, U2_1) + f2(t, U1_2, U2_2));
		if(!filename.empty())
			file << t << " " << u1 << " " << u2 << endl;

	}

    free_matrix(A,1,2,1,2);
    free_matrix(B,1,2,1,1);
}

int main()
{
	niejawneRK(0, 1, 0.0001, 0.1, 10000, "z3.txt");
	return 0;
}
