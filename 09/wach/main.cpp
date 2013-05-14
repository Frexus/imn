/**
*		@author		Wachulec Marcin
*		@date		08-05-2013
*		@file		main.cpp
*		@brief		lab09
*/
#include <stdio.h>
#include <math.h>

/**(0)
*	static const int x_m, y_m
*		stale. rozmiar naszej tablicy/siatki
*/
static const int x_m = 201;
static const int y_m = 102;

//################################## PROCEDURY #####################################

/**(1)
*	double phi_tab[][]
*		dwuwymiarowa tablica wartoci double ( siatka 201 x 102 )
*/
double phi_tab[x_m][y_m];

/**(2)
*	double integral(int)
*		calka zbierznosci
*/
double integral( int k ) {
	double a = 0.0;
	
	for( int i = 1; i < x_m - k; i += k ){
			for( int j = 1; j < y_m - k; j += k ) {
				if( i < 79 || i > 119 || j > 20 ) {
					a += ( pow ( ( phi_tab[ i + k ][j] - phi_tab[ i - k ][j]), 2 ) + pow( ( phi_tab[i][ j + k ] - phi_tab[i][ j - k ] ), 2 ) );
				}
			}
	}
	
	a /= 8.0;
	
	return a;
}

/**(3)
*	double u2(int, int)
*/
double u2( int i, int j ) {
	return ( phi_tab[ i + 1 ][j] - phi_tab[ i - 1 ][j] ) / 2.0;
}

/**(4)
*	double v2(int, int)
*/
double v2( int i, int j ) {
	return ( phi_tab[i][ j + 1 ] - phi_tab[i][ j - 1 ] ) / 2.0;
}

/**(5)
*	double p(int, int)
*/
double p( int i, int j ) {
	double p0 = 10.0;
	double r = 1.0;
	double u0 = 1.0;
	return p0 + r * pow( u0, 2 ) - r * ( pow( u2( i, j ), 2 ) + pow( v2( i, j ), 2 ) );
}


//################################## ZAD1 ############################################
void zad1(const char* fname) {
	double u0 = 1.0;
	
	double tol = pow( 10, -6 );
	double e = 0.0;
	
	double a1 = 0.0;
	double a2 = 0.0;
	int it = 0;


	for( int i = 0; i < x_m; i++ ) {
		for( int j = 0; j < y_m; j++ ) {
			phi_tab[i][j] = 0.0;
			
			if( i == 0 || i == x_m - 1 || j == y_m - 1 ){ 
				phi_tab[i][j] = u0 * ( j + 100 );
			}else if( j == 0 ) { 
				phi_tab[i][j] = phi_tab[0][0]; 
			}
		}
	}

	for( int i = 79; i <= 119; i++ ) {
		phi_tab[i][20] = phi_tab[0][0];
	}
	
	for( int i = 0; i < 20; i++ ) {
		phi_tab[79][i] = phi_tab[0][0];
		phi_tab[119][i] = phi_tab[0][0];
	}

	it = 0;
	e = 0.0;
	a2 = a1 = integral(1);
	FILE* fp;
	fp = fopen( fname, "w" );

	do{
		a2 = a1;
		for( int i = 1; i < x_m - 1; i++ ) {
			for( int j = 1; j < y_m - 1; j++ ) {
				if( j <= 20 && i >= 79 && i <= 119 ) 
					continue;
					phi_tab[i][j] = ( phi_tab[ i - 1 ][j] + phi_tab[i][ j - 1 ] + phi_tab[ i + 1 ][j] + phi_tab[i][ j + 1 ] ) / (4.0);
			}
		}

		fprintf( fp, "%d %g\n", it, a1 );
		a1 = integral(1);

		//printf("%d\t%10.7f\n", it, fabs( a2 - a1 ) );
		it++;
		e = fabs( a2 - a1 );
	} while( e > tol );
	
	fclose(fp);
}

void zad1b(const char* fname){
	FILE* fp = fopen( fname, "w" );
	for( int i = 0; i < x_m; i++ ) {
		for( int j = 0; j < y_m; j++ ) {
			fprintf( fp, "%d %d %g\n", i + 1, j + 100, phi_tab[i][j] );
		}
		fprintf( fp,"\n");
	}
	fclose(fp);
}


//################################## ZAD2 ############################################
void zad2(const char* fname){
	double dx = 1.0;
	double dy = 1.0;
	double u0 = 1.0;
	double tol = pow( 10, -6 );
	double e = 0.0;
	double a1 = 0.0;
	double a2 = 0.0;
	int it = 0;

	for( int i = 0; i < x_m; i++ ) {
		for( int j = 0; j < y_m; j++ ) {
			phi_tab[i][j] = u0 * ( i + 1 ); 
		}
	}

	for( int i = 79; i <= 119; i++ ){
		phi_tab[i][20] = phi_tab[0][0];
	}
		
	for( int i = 0; i < 20; i++ ) {
		phi_tab[79][i] = phi_tab[0][0];
		phi_tab[119][i] = phi_tab[0][0];
	}

	it = 0;
	e = 0.0;
	a2 = a1 = integral(1);
	FILE* fp;
	fp = fopen( fname, "w" );

	do{
		for( int i = 0; i < 79; i++ ) {
			phi_tab[i][0] = phi_tab[i][1];
		}
		for( int i = 120; i < 201; i++ ) {
			phi_tab[i][0] = phi_tab[i][1];
		}

		for( int i = 0; i < 20; i++ ) {
			phi_tab[79][i] = phi_tab[78][i];
			phi_tab[119][i] = phi_tab[120][i];
		}
		
		for( int i = 79; i < 120; i++ ){
			phi_tab[i][20] = phi_tab[i][21];
		}

		phi_tab[79][20] = ( phi_tab[78][20] + phi_tab[79][21] ) / 2.0 ;
		phi_tab[119][20] = ( phi_tab[120][20] + phi_tab[119][21] ) / 2.0 ;
		
		a2 = a1;
		for( int i = 1; i < x_m - 1; i++ ) {
			for( int j = 1; j < y_m - 1; j++ ){
				if( j <= 20 && i >= 79 && i <= 119 )
					continue;
					phi_tab[i][j] = ( phi_tab[ i - 1 ][j] + phi_tab[i][ j - 1 ] + phi_tab[ i + 1 ][j] + phi_tab[i][ j + 1 ] ) / (4.0);
			}
		}

		fprintf( fp, "%d %g\n", it, a1 );
		a1 = integral( 1 );

		it++;
		e = fabs( a2 - a1 );
	}while( e > tol );
	
	fclose(fp);
}

void zad2b(const char* fname){
	FILE* fp = fopen( fname, "w" );
	for( int i = 0; i < x_m; i++ ) {
		for( int j = 0; j < y_m; j++ ){
			if( j <= 20 && i >= 79 && i <= 119 )
				fprintf( fp, "%d %d %g\n", i + 1, j + 100, 0.0 );
			else
				fprintf( fp, "%d %d %g\n", i + 1, j + 100, phi_tab[i][j] );
		}
		fprintf(fp,"\n");
	}
	fclose(fp);
}

//################################## ZAD3 ############################################
void zad3(const char* fname){
	double p_tab[x_m][y_m];

	for( int i = 1; i < x_m - 1; i++ ) {
		for( int j = 1; j < y_m - 1; j++ ) {
			if( i < 79 || i > 119 || j > 20)
				p_tab[i][j] = p(i,j);
		}
	}

	FILE* fp = fopen( fname, "w" );
	for( int i = 1; i < x_m - 1; i++ ) {
		for( int j = 1; j < y_m - 1; j++ ) {
			fprintf( fp, "%d %d %g\n", i + 1, j + 100, p_tab[i][j] );
		}
		fprintf(fp,"\n");
	}
	fclose(fp);
}

//################################## MAIN ############################################
int main(){

	zad1("zad1.dat");
	zad1b("zad1b.dat");
	
	zad2("zad2.dat");
	zad2b("zad2b.dat");
	
	zad3("zad3.dat");

	return 0;
}
