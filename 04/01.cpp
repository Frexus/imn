#include <iostream>
#include <cmath>
#include <gsl/gsl_linalg.h>

const double a[2][2] = { 1./4., 1./4. - sqrt(3.)/6.,
                         1./4. + sqrt(3.)/6., 1./4.
                     };

const double b = 1./2.;
const double c[2] = {1./2. - sqrt(3.)/6., 1./2. + sqrt(3.)/6. };

double getDerivative(double delta[2][2], int k, int l, double dt, double (*poch_f)(double, double), double prevt, double ul)
{
    return delta[k][l] - dt * a[k][l] * poch_f(prevt + dt * c[0], ul);
}

void metoda(double& u1, double& u2, double dt, double T, double tol, double (*f1)(double, double), double (*f2)(double, double), double (*poch_f1)(double, double), double (*poch_f2)(double, double))
{
    double U1 = u1, U2 = u2;
    double A[2][2];
    double vb[2];
    
    for(double t = dt; t < T; t += dt)
    {
        while(true)
        {
            double prevU1 = U1, prevU2 = U2;
            A = { getDerivative(a, 0, 0, dt, poch_f1, t - dt, U1), getDerivative(a, 0, 1, dt, poch_f1, t - dt, U2),
                getDerivative(a, 1, 0, dt, poch_f2, t - dt, U1), getDerivative(a, 1, 1, dt, poch_f2, t - dt, U2)
             };
            vb = { -f1(U1, U2), -f2(U1, U2) };
            gsl_matrix_view m = gsl_matrix_view_array (A, 2, 2);
            gsl_vector_view b = gsl_vector_view_array (vb, 2);
            gsl_vector *x = gsl_vector_alloc (2);
            int s;
            gsl_permutation * p = gsl_permutation_alloc (2);
            gsl_linalg_LU_decomp (&m.matrix, p, &s);
            gsl_linalg_LU_solve (&m.matrix, p, &b.vector, x);
            U1 = x[0];
            U2 = x[1];
            if( fabs(U1 - prevU1) < tol && fabs(U2 - prevU2) < tol)
                break;
        }
    }
    u1 = U1;
    u2 = U2;
}

int main() 
{
    
    
}
