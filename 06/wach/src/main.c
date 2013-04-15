/**
*	@author		Marcin Wachulec
*	@date			10-04-2013	
*	@file			main.c
*	@brief		kompilacja gcc *.c -lm
*/

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "nrutil.h"


double d_random(){
	return ( (double)rand() )/(RAND_MAX+1.0);
}

double* bisection (double * E, double* result) {

		result[0] = result[1] = result[2] = 0.0;
		
		int j;
		int L = 1;
		
		double tab[201];
		double v0 = 0;
		double v1 = 0.0157;
		
		double dx = 0.01;
		double x;
		
		int i;
		int k=0;

		for( j = 0; j < 3; j++ ) {
				tab[0] = v0;
				tab[1] = v1;
				for( i = 2; i < 201; i++ ){
					tab[i] = 0.0;
				}
				
				i=2;
				
				for( x = -L + 2 * dx; x <= L + dx; x += dx ) {
					tab[i] = 2.0 * tab[i-1] - tab[i-2] - E[j] * tab[i-1] * pow( dx, 2 );
					i++;
				}
				result[k] = tab[200];
				k++;
			}

		return result;
}

void thrand(double* theta) {
	theta[0] = M_PI / 4;
	theta[100] = 0.0;
	int i;
	for( i = 1; i < 100; i++ ){
		theta[i] = d_random();
	}
}

void thiter(double* theta){
	theta[0] = M_PI / 4;
	theta[100] = 0.0;
	int i;
	double ds = 0.005;
	for( i = 1; i < 100; i++ ) {
		theta[i] = M_PI / 4.0 - M_PI * ds * i / 2.0;
	}
}

double integral(double (*fun) (double), double* theta, int n, double ds) {
	double tmp = 0;
	int i;
	for( i = 0; i <= n; i++ )
		tmp += fun( theta[i] );
	tmp *= ds;
	return tmp;
}

//############################ zad1a ###############################
void zad1a(const char* fname){
	FILE* fp = fopen(fname, "w");
	int L = 1;
	
	double v0 = 0;
	double v1 = 0.0157;
	
	double dx = 0.01;
	
	double tab[201];
	
	double E;
	double x;
	
	int i;
	
	for( E = 0; E < 50; E += 0.1 ) {
		tab[0] = v0;
		tab[1] = v1;
		for( i = 2; i < 201; i++ ){
			tab[i] = 0.0;
		}
		
		i = 2;
		
		for( x = -L + 2 * dx; x < L+dx; x += dx ) {
			tab[i] = 2.0 * tab[i-1] - tab[i-2] - E * tab[i-1] * pow( dx, 2 );
			i++;
		}
		fprintf( fp, "%g %g\n", E, tab[200] );

	}
	fclose(fp);
}

//############################ zad1b ###############################

void zad1b( const char* fname1, const char* fname2 ) {
	FILE* fp,* fp2;
	fp = fopen( fname1, "w" );
	fp2 = fopen( fname2, "w" );
	
	
	double E[3];
	double Emin = 0.0;
	double Emax = 5.1;

	double res[3];

	while( 1 ){

		E[0] = Emin;
		E[2] = Emax;
		E[1] = ( E[0] + E[2] ) * 0.5;
		
		bisection( E, res );
		
		if( fabs( res[1] ) < pow( 10, -10 ) ) {
			break;
		} else if( ( res[0] * res[1] ) < 0 ) { 
			Emin = E[0];
			Emax = E[1];
		} else if( ( res[1] * res[2] ) < 0 ){ 
			Emin = E[1];
			Emax = E[2];
		}

	}
	
	fprintf( fp, "E0 = %g\n", E[1] );
	
	int L=1.0;
	
	double tab[201];
	double dx=0.01;
	double x;
	
	int i;
	
	tab[0]=0.0;
	tab[1]=0.0157;
	
	for( i = 2 ; i < 201; i++ ){
		tab[i] = 0.0;
	}
	i = 2;
	
	fprintf( fp2, "%d %g\n", -L, tab[0] );
	fprintf( fp2, "%g %g\n", -L + dx, tab[1] );

	for( x = -L + 2 * dx ; x <= L + dx ; x += dx ) {
		tab[i] = 2.0 * tab[i-1] - tab[i-2] - E[1] * tab[i-1] * pow( dx, 2 );
		fprintf( fp2, "%g %g\n", x, tab[i] );
		
		i++;

	}
	fclose(fp);
	fclose(fp2);
}

//############################ zad2 ###############################

void zad2(int ver){
	int i, j, it = 1;
	double P = 10.0;
	
	char file_name[20];
	
	double ds = 0.005;
	double vlength = 0.0;
	double theta[101];

	if( ver == 1 ){
		thrand( theta );
	}else if( ver == 2 ){
		thiter( theta );
	}
	sprintf(file_name, "zad2%d%d.dat", ver, 0);
	
		FILE * fp2 = fopen( file_name, "w" );
		for( i = 0; i < 101; i++ ){
					fprintf(fp2, "%g %g %g %g\n", i * ds, theta[i], integral( sin, theta, i, ds ), integral( cos, theta, i, ds ) );
				}
		fclose(fp2);
		
	float** J = matrix( 1, 99, 1, 99 );
	float** F = matrix( 1, 99, 1, 1 );
	
	do {
	
		for( i = 1; i < 100; i++ ) {
			for( j = 1 ; j < 100; j++ ){
					J[i][j] = 0.0;
					if( i == j ) {
						J[i][j] = -2.0 + P * pow( ds, 2 ) * cos( theta[i] );
					}
					if( ( i == j + 1 ) || ( i == j - 1 ) )
						J[i][j] = 1.0;
			}
			F[i][1] = -( theta[i-1] - 2.0 * theta[i] + theta[i+1] + P * pow( ds, 2 ) * sin( theta[i] ) );
		}
	
		gaussj( J, 99, F, 1 );
	
		for( i = 1; i < 100; i++ ){
			theta[i] = theta[i] + F[i][1];
		}
		vlength = 0;
	
		for( i = 1; i < 100; i++ ) {
			vlength += pow( F[i][1], 2 );
		}
		
		printf( "%g \n", vlength );
		
		vlength = sqrt( vlength );
		
		sprintf( file_name, "zad2%d%d.dat", ver, it );
		
		FILE * fp = fopen( file_name, "w" );
		
		for( i = 0; i < 101; i++ ) {
				fprintf( fp, "%g %g %g %g\n", i * ds, theta[i], integral( sin, theta, i, ds ), integral( cos, theta, i, ds ) );
		}
			
		fclose(fp);
		
		it++;
		
	}while( vlength > 0.001 );
	
	free_matrix( J, 1, 99, 1, 99 );
	free_matrix( F, 1, 99, 1, 1 );
}

int main(){

	zad1a("zad1a.dat");
	zad1b("zad1bE.dat","zad1b.dat");
	
	zad2(1);
	zad2(2);

	return 0;
	
}

