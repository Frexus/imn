#include <iostream>
#include <ios>
#include <fstream>
#include <ostream>
#include <cstdio>
#include <cstdlib>
#include <cmath>

using namespace std;

double bis(double (*func)(double), double x1, double x2, double xacc)
{
	int j;
	float dx,f,fmid,xmid,rtb;

	f=(*func)(x1);
	fmid=(*func)(x2);
	rtb = f < 0.0 ? (dx=x2-x1,x1) : (dx=x1-x2,x2);
	while(1) {
		fmid=(*func)(xmid=rtb+(dx *= 0.5));
		if (fmid <= 0.0) rtb=xmid;
		if (fabs(dx) < xacc || fmid == 0.0) return rtb;
	}
	return 0.0;
}

double n_phi(double phi, double p_phi, double dx, double E)
{
    return 2. * phi - p_phi - E * phi * dx * dx;
}

double n_phi_max(double E)
{
    double phi[201];
    phi[0] = 0;
    phi[1] = 0.0157;
    double dx = 0.01;
    for(int i = 1; i < 200; i++)
    {
        phi[i+1] = 2. * phi[i] - phi[i-1] - E * phi[i] * dx * dx;
    }
    return phi[200];
}

void zad1a(double phi0, double phi1, double dx, double L, char* filename)
{
    ofstream file(filename);
    int size = 2*ceil(L/dx)+1;
    double* phi = new double[size];

    for(double E = 0; E <= 50; E += 0.1)
    {
        file << E << ' ' << n_phi_max(E) << '\n';
    }
    delete phi;
}

void zad1b(char* filename)
{
    ofstream file(filename);
    double m0 = bis(n_phi_max, 0, 5.1, 10e-10);
    cout << "miejsce zerowe dla E: " << m0 << '\n';
    const int N = 2001;
    double phi[N];
    double x = 0;
    double dx = 0.01;
    phi[0] = 0;
    phi[1] = 0.0157;
    for(int i = 1; i < N-1; i++)
    {
        phi[i+1] = 2. * phi[i] - phi[i-1] - m0 * phi[i] * dx * dx;
    }
    for(int i = 0; i < N; i++)
    {
        file << x << " " << phi[i] << '\n';
        x+=dx;
    }
}

int main()
{
    zad1a(0, 0.0157, 0.01, 1, "z1a.txt");
    zad1b("z1b.txt");
}
