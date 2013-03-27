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

double err(double y2, double y1, double n)
{
    return (y2-y1)/(pow(2.0,n-1.0) - 1.0);
}

double new_time(double S, double tol, double E, double dt, double n)
{
    return pow((S*tol)/abs(E), 1.0/n)*dt;
}

void niejawneRK(double u01, double u02, double tol, double dt, double T, string filename, bool print_first_step = false)
{
	double u1_krotki, u2_krotki, u1_dlugi, u2_dlugi;
    u1_krotki = u1_dlugi = u01;
    u2_krotki = u2_dlugi = u02;
	double U1_1_krotki, U1_2_krotki, U2_1_krotki, U2_2_krotki, U1_1_dlugi, U1_2_dlugi, U2_1_dlugi, U2_2_dlugi;
    double prevu1 = u01, prevu2 = u02;
    double tmpdt;
			U1_1_krotki = U1_2_krotki = U1_1_dlugi = U1_2_dlugi = prevu1;
		U2_1_krotki = U2_2_krotki = U2_1_dlugi = U2_2_dlugi = prevu2;
	float **A = matrix(1,4,1,4);
    float **B = matrix(1,4,1,1);
	ofstream file;
	if(!filename.empty())
		file.open(filename.c_str());

	for(double t = 0; t <= T ;)
	{

        //dlugi?
        tmpdt = dt * 2;
        
		A[1][1] = 1 + L1 * a[0][0] * tmpdt;	A[1][2] = -L2 * a[0][0] * tmpdt;	A[1][3] = L1 * a[0][1] * tmpdt;	A[1][4] = -L2 * a[0][1] * tmpdt;
		A[2][1] = L1 * a[1][0] * tmpdt;		A[2][2] = -L2 * a[1][0] * tmpdt;	A[2][3] = 1 + L1 * a[1][1] * tmpdt;A[2][4] = -L2 * a[1][1] * tmpdt;
		A[3][1] = 0;						A[3][2] = 1 + L2 * a[0][0] * tmpdt;A[3][3] = 0;					A[3][4] = L2 * a[0][1] * tmpdt;
		A[4][1] = 0;						A[4][2] = L2 * a[1][0] * tmpdt;	A[4][3] = 0;					A[4][4] = 1 + L2 * a[1][1] * tmpdt;
			
		B[1][1] = u1_dlugi + (tmpdt * L1) * (a[0][0] + a[0][1]) / 2.;
		B[2][1] = u1_dlugi + (tmpdt * L1) * (a[1][0] + a[1][1]) / 2.;
		B[3][1] = u2_dlugi;
		B[4][1] = u2_dlugi;
			
		gaussj(A,4,B,1);
					
		U1_1_dlugi = U1_1_dlugi + B[1][1];
		U1_2_dlugi = U1_2_dlugi + B[3][1];
		U2_1_dlugi = U2_1_dlugi + B[2][1];
		U2_2_dlugi = U2_2_dlugi + B[4][1];

		u1_dlugi = u1_dlugi + (dt / 2.) * (f1(t, U1_1_dlugi, U2_1_dlugi) + f1(t, U1_2_dlugi, U2_2_dlugi));
		u2_dlugi = u2_dlugi + (dt / 2.) * (f2(t, U1_1_dlugi, U2_1_dlugi) + f2(t, U1_2_dlugi, U2_2_dlugi));
		
        //2 krotkie?     
		A[1][1] = 1 + L1 * a[0][0] * dt;	A[1][2] = -L2 * a[0][0] * dt;	A[1][3] = L1 * a[0][1] * dt;	A[1][4] = -L2 * a[0][1] * dt;
		A[2][1] = L1 * a[1][0] * dt;		A[2][2] = -L2 * a[1][0] * dt;	A[2][3] = 1 + L1 * a[1][1] * dt;A[2][4] = -L2 * a[1][1] * dt;
		A[3][1] = 0;						A[3][2] = 1 + L2 * a[0][0] * dt;A[3][3] = 0;					A[3][4] = L2 * a[0][1] * dt;
		A[4][1] = 0;						A[4][2] = L2 * a[1][0] * dt;	A[4][3] = 0;					A[4][4] = 1 + L2 * a[1][1] * dt;
			
		B[1][1] = u1_krotki + (dt * L1) * (a[0][0] + a[0][1]) / 2.;
		B[2][1] = u1_krotki + (dt * L1) * (a[1][0] + a[1][1]) / 2.;
		B[3][1] = u2_krotki;
		B[4][1] = u2_krotki;
			
		gaussj(A,4,B,1);
					
		U1_1_krotki = U1_1_krotki + B[1][1];
		U1_2_krotki = U1_2_krotki + B[3][1];
		U2_1_krotki = U2_1_krotki + B[2][1];
		U2_2_krotki = U2_2_krotki + B[4][1];

		u1_krotki = u1_krotki + (dt / 2.) * (f1(t, U1_1_krotki, U2_1_krotki) + f1(t, U1_2_krotki, U2_2_krotki));
		u2_krotki = u2_krotki + (dt / 2.) * (f2(t, U1_1_krotki, U2_1_krotki) + f2(t, U1_2_krotki, U2_2_krotki));
        
        A[1][1] = 1 + L1 * a[0][0] * dt;	A[1][2] = -L2 * a[0][0] * dt;	A[1][3] = L1 * a[0][1] * dt;	A[1][4] = -L2 * a[0][1] * dt;
		A[2][1] = L1 * a[1][0] * dt;		A[2][2] = -L2 * a[1][0] * dt;	A[2][3] = 1 + L1 * a[1][1] * dt;A[2][4] = -L2 * a[1][1] * dt;
		A[3][1] = 0;						A[3][2] = 1 + L2 * a[0][0] * dt;A[3][3] = 0;					A[3][4] = L2 * a[0][1] * dt;
		A[4][1] = 0;						A[4][2] = L2 * a[1][0] * dt;	A[4][3] = 0;					A[4][4] = 1 + L2 * a[1][1] * dt;
			
		B[1][1] = u1_krotki + (dt * L1) * (a[0][0] + a[0][1]) / 2.;
		B[2][1] = u1_krotki + (dt * L1) * (a[1][0] + a[1][1]) / 2.;
		B[3][1] = u2_krotki;
		B[4][1] = u2_krotki;
			
		gaussj(A,4,B,1);
			
		U1_1_krotki = U1_1_krotki + B[1][1];
		U1_2_krotki = U1_2_krotki + B[3][1];
		U2_1_krotki = U2_1_krotki + B[2][1];
		U2_2_krotki = U2_2_krotki + B[4][1];

		u1_krotki = u1_krotki + (dt / 2.) * (f1(t, U1_1_krotki, U2_1_krotki) + f1(t, U1_2_krotki, U2_2_krotki));
		u2_krotki = u2_krotki + (dt / 2.) * (f2(t, U1_1_krotki, U2_1_krotki) + f2(t, U1_2_krotki, U2_2_krotki));
        
        double errU1 = fabs(err(u1_dlugi, u1_krotki, 5));
        double errU2 = fabs(err(u2_dlugi, u2_krotki, 5));
        
        if(errU1 < tol && errU2 < tol)
        {
            prevu1 = u1_krotki;
            prevu2 = u2_krotki;
            t+= 2* dt;
            file << t << " " << prevu1 << " " << prevu2 << " " << dt << endl;
        }
        
        double dtU1 = new_time(0.75, tol, errU1, dt, 5);
        double dtU2 = new_time(0.75, tol, errU2, dt, 5);
        
        dt = min(dtU1, dtU2);
        
        cout << dt << endl;

	}

    free_matrix(A,1,4,1,4);
    free_matrix(B,1,4,1,1);
}

int main()
{
	niejawneRK(0, 1, 0.0001, 0.1, 10000, "z3.txt");
	return 0;
}
