/**
*   @author Wachulec Marcin
*   @date   24-04-2013
*   @brief  main.c lab08 imn
*/
#include <stdio.h>
#include <math.h>

/*(0)
*   const int S(257)
*   stała opisująca rozmiar siatki (257 x 257)
*/
const int S = 257;

/*(1)
*    double** fi
*       globalna tablica dwuwymiarowa
*/
double fi[257][257];

/*(2)
*    double integral(int)
*       procedura obliczająca całkę zbierzności
*/
double integral(int k){
    double a=0.0;
    int i,j;
    for(i=0;i<S-k;i+=k){
            for(j=0;j<S-k;j+=k){
                a+=(pow((fi[i+k][j]+fi[i+k][j+k]-fi[i][j]-fi[i][j+k]),2)+pow((fi[i][j+k]+fi[i+k][j+k]-fi[i][j]-fi[i+k][j]),2));
            }
        }
    a/=8.0;
    return a;
}

//#################################### zad1a ###############################################
void zad1(const char* fname){
    int i, j;
    double a1 = 0.0;
    double a2 = 0.0;
    double xmin=-4.0;
    double dx = 1.0 / 32.0;
    double dy = 1.0 / 32.0;
    double e = 0.0;
    double tol = pow( 10, -9 );
    int iter = 0;

    for( i = 0; i < S; i++ ) {
        for( j = 0; j < S ; j++ ) {
            fi[i][j] = 0.0;
            if( i == 0 || i == S - 1 || j == 0 || j == S - 1 ){
                fi[i][j] = pow( i * dx + xmin, 2 ) - pow( j * dy + xmin, 2 );
            }
        }
    }

    iter = 0;
    e = 0.0;
    a2 = a1 = integral(1);
    FILE* fp;
    fp = fopen( fname, "w" );

    do{
        a2 = a1;
        for( i = 1; i < S - 1; i++ ) {
            for( j = 1; j < S - 1; j++ ) {
                fi[i][j] = ( fi[ i - 1 ][j] + fi[i][ j - 1 ] + fi[ i + 1 ][j] + fi[i][ j + 1 ] ) / ( 4.0 );
            }
        }

        fprintf( fp, "%d %f\n", iter, a1 );
        a1 = integral( 1 );

        printf( "%d %g\n", iter, fabs( a2 - a1 ) );
        iter++;
        e = fabs( a2 - a1 );
    } while( e > tol );

    fclose(fp);
}

//#################################### zad1b ###############################################
void zad1b(const char* fname){
    int i,j;
    double xmin = -4.0;
    double dx = 1.0 / 32.0;
    double dy = 1.0 / 32.0;
    FILE* fp = fopen( fname, "w" );
    for( i = 0; i < S; i++ ) {
        for( j = 0; j < S; j++ )
            fprintf( fp,"%g %g %g\n", i * dx + xmin, j * dy + xmin, fi[i][j] );
        fprintf( fp, "\n" );
    }
    fclose(fp);
}

void zad2b(int k, const char* fname){
        int i, j;
        double xmin=-4.0;
            double dx=1./32;
            double dy=1./32;
        FILE *fp = fopen(fname,"w");
            for(i=0;i<S;i+=k){
                for(j=0;j<S;j+=k)
                    fprintf(fp,"%f\t%f\t%f\n",i*dx+xmin,j*dy+xmin,fi[i][j]);
                fprintf(fp,"\n");
            }
            fclose(fp);
}

//#################################### zad2 ###############################################
void zad2(){
    int i, j, k;
    double xmin = -4.0;
    double a1 = 0.0;
    double a2 = 0.0;
    double dx = 1.0 / 32.0;
    double dy = 1.0 / 32.0;
    double tol = pow( 10, -9 );
    double e = 0.0;
    int iter = 0;
    char name[50];

    for( i = 0; i < S; i++ ) {
        for( j = 0; j < S; j++ ) {
            fi[i][j] = 0.0;

            if( i == 0 || i == S - 1 || j == 0 || j == S - 1 ) {
                fi[i][j] = pow( i * dx + xmin, 2 ) - pow( j * dy + xmin, 2 );
            }
        }
    }

	for(k = 32; k >= 1; k/=2) {
		e = 0.0;

		FILE* fp;
		sprintf(name, "zad2a_k%d.dat", k);
		fp = fopen( name, "w" );


		do{
		    a2 = a1;
		    for( i = k; i < S - 1; i += k ) {
		        for( j = k; j < S - 1; j += k ) {
		            fi[i][j] = ( fi[ i - k ][j] + fi[i][ j - k ] + fi[ i + k ][j] + fi[i][ j + k ] ) / 4.0;
		        }
		    }

		    a1 = integral( k );
		    fprintf( fp, "%d %f\n", iter, a1 );
		    printf( "%d %f\n", iter, fabs( a2 - a1 ) );
		    iter++;
		    e = fabs( a2 - a1 );
		} while( e > tol ); //end do while

		fclose(fp);

		sprintf(name, "zad2b_k%d.dat", k);
		zad2b(k, name);


		if( k > 1 ) {//przeliczenie dla k większych od 1
		    int dk = k/2;
		    for( i = dk; i < S - dk; i += dk ) {
		        for( j = dk; j < S - dk; j += dk ) {
		            if( j % k ){
		                if( i % k )
		                    fi[i][j] = ( fi[ i - dk ][ j - dk ] + fi[ i - dk ][ j + dk ] + fi[ i + dk ][ j - dk ] + fi[ i + dk ][ j + dk ] ) / 4.0;
		                else
		                    fi[i][j] = ( fi[i][ j - dk ] + fi[i][ j + dk ] ) / 2.0;
		            } else if( i % k ){
		                fi[i][j] = ( fi[ i - dk ][j] + fi[ i + dk ][j] ) / 2.0;
		            }//end elseif
		        }//end for j
		    }//end for i
		} //enf if
	}//end for k
}//end zad2

int main(){

    zad1( "zad1_1.dat" );
    zad1b( "zad1b.dat" );

    zad2( 32 );


    return 0;
}
