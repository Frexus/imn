/**
*   @author Wachulec Marcin
*   @date   30-03-2013
*   @file   main.c
*/
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define M 301
//M - całkowity rozmiar siatki

#define SAVE 1
//SAVE - włączenie/wyłączenie zapisu do plików

double f1 = 0.0;

/*(1)
*   double n(double)
*   gęstość ładunku elektronu
*   F używana tylko w procedurze double f(double)
*/
double n(double r){
    return -1.0 * ( ( pow(r,2.0) * exp(-r) ) / ( 32.0 * M_PI ) );
}

/*(2)
*   double f(double)
*   druga pochodna f (nasza funkcja z równania rozkładu poissona), rozwiązanie numeryczne
*   f(0) = 0 => skończony potencjał
*   f( +inf ) = -3 => proporcjonalnie do 1/r
*/
double f(double r){
    return -1.0 * ( 4.0 * M_PI * r * n(r) );
}

/*(3)
*   double f_analitic(double)
*   funkcja f analitycznie, rozwiązanie dokładne
*/
double f_analitic(double r){
    return exp(-r) * ( 0.125 * pow(r, 3.0) + 0.75 * pow(r, 2.0) + 2.25 * r + 3.0 ) - 3.0;
}

/*(5)
*   double f_m(double, double)
*   przekształcenie funkcji (2) oraz (3) w celu obliczenia f_m
*/
double f_m(double r, double dr, double pfm, double nfm, double (*f)(double) ){
    return ( f(r) * pow(dr, 2.0) - pfm - nfm )*-0.5;
}

/*(6)
*   double f_deriv
*/
double f_deriv2( double dr, double prev, double next ){
    return pow( (next - prev) / (2.0 * dr), 2.0 );
}

/*(7)
*   double prev_f_m
*   przekształcenie funkcji (2) oraz (3) w celu obliczenia f_m-1
*/
double prev_f_m(double r, double dr, double fm, double nfm, double (*f)(double) ){
    return f(r) * pow(dr, 2.0) - nfm + 2.0 * fm;
}

/*(8)
*   double prev_f_m
*   przekształcenie funkcji (2) oraz (3) w celu obliczenia f_m-1
*/
double next_f_m(double r, double dr, double pfm, double fm, double (*f)(double) ){
    return f(r) * pow(dr, 2.0) - pfm + 2.0 * fm;
}

/*(9)
*   double prev_f_m_num
*/
double prev_f_m_num(double r, double dr, double fm, double nfm, double (*f)(double) ){
    return ( pow(dr, 2.0) / 12 ) * ( f(r+dr) + 10.0 * f(r) + f(r-dr) ) + 2.0 * fm - nfm;
}

/*(10)
*   double next_f_m_num
*/
double next_f_m_num(double r, double dr, double pfm, double fm, double (*f)(double) ){
    return ( pow(dr, 2.0) / 12 ) * ( f(r+dr) + 10.0 * f(r) + f(r-dr) ) + 2.0 * fm - pfm;
}

/*(11)
*   double df
*/
double df(double t, double y1, double y2){
	return y2;
}

/*(12)
*   double dg
*/
double dg(double r, double y1, double y2){
	return f(r);
}

/*(13)
*   double RK2
*/
void RK2(double r, double* f, double* g, double dr){
	double k11, k12, k21, k22;
	k11 = df( r, *f, *g );
	k21 = dg( r, *f, *g );
	k12 = df( r + dr, *f + dr * k11, *g + dr * k21 );
	k22 = dg( r + dr, *f + dr * k11, *g + dr * k21 );
	*f = *f + dr * ( k11 + k12 ) / 2.0;
	*g = *g + dr * ( k21 + k22 ) / 2.0;
}

//################## ZADANIE_1 ###########################//
double zad1(double r_min, double r_max, double dr, double epsilon, const char* filename){
    double r;

    double f_tab[ M ] = {0};
    //wartości dla każdej iteracji, na początku zerujemy

    int idx = 1;
    //iterator

    double a_prev;
    double a;
    //^^ wartości całek działania (aktualna i poprzednia)


    double diff;
    //różnica całek (sprawdzenie zbieżności na końcu każdej iteracji)

    f_tab[0] = 0;   //r1 = 0
    f_tab[M-1] = -3;  //rM = 30
    //warunki brzegowe, czyli wartość f w r = 0 i r = 30

    a_prev = a = 0.0;

    do {
        a_prev = a;
        a = 0.0;

        //obliczanie kolejnych elementów siatki

        for(r = r_min + dr, idx = 1; r < r_max; r += dr, idx++){
              f_tab[idx] = f_m(r, dr, f_tab[idx-1], f_tab[idx+1], f);
        }

        //obliczanie wartości całek działania
        for(idx = 1, r = r_min + dr; idx < M - 1; idx++, r+= dr){
            a += (0.5 * f_deriv2(dr, f_tab[idx-1], f_tab[idx+1]) + f(r) * f_tab[idx] ) * dr;
        }

        //obliczanie różnicy wartości całek działania iteracji poprzednij i aktualnej
        diff = fabs(a_prev - a);

    } while(diff > epsilon);

    //------ zapis do pliku --------
    if(SAVE){
        FILE* fp = fopen(filename, "w");
        for(r = r_min, idx = 0; idx < M; idx++, r+=dr){
            fprintf( fp, "%g %g %g %g\n", r, f_tab[idx], f_analitic(r), fabs( f_tab[idx] - f_analitic(r) ) );
        }
        fclose(fp);
    }

    return f_tab[1];
}

//################## ZADANIE_2 ###########################//
void zad2(double r_min, double r_max, double dr, const char* filename){
    double r;

    double f_tab[ M ] = {0};
    //wartości dla każdej iteracji, na początku zerujemy

    int idx = 1;
    //iterator

    f_tab[ M-1 ] = f_tab[ M-2 ] = -3.0;
    //warunki brzegowe, czyli wartość f w r = 29 i r = 30


    //obliczanie kolejnych elementów siatki
    for(r = r_max - 1.0 * dr, idx = M - 2; idx > 0; r -= dr, idx--){
          f_tab[idx-1] = prev_f_m(r, dr, f_tab[idx], f_tab[idx+1], f);
    }

    //------ zapis do pliku --------
    if(SAVE){
        FILE* fp = fopen(filename, "w");
        for(r = r_min, idx = 0; idx < M; idx++, r+=dr){
            fprintf( fp, "%g %g %g %g\n", r, f_tab[idx], f_analitic(r), fabs( f_tab[idx] - f_analitic(r) ) );
        }
        fclose(fp);
    }
}


//################## ZADANIE_3 ###########################//
void zad3(double r_min, double r_max, double dr, int bullet, const char* filename){
    double r;
    int size = (int)(r_max/dr);

    double* f_tab = malloc( size * sizeof(double) );
    int i = 0;
    for(i = 0; i < size; i++ )
        f_tab[i] = 0.0;

    //wartości dla każdej iteracji, na początku zerujemy

    int idx = 1;
    //iterator

    f_tab[1] = (bullet == 3 ? f1 : f_analitic(r_min+dr) );

    //obliczanie kolejnych elementów siatki
    for(r = r_min + dr, idx = 1; idx < size-1; r += dr, idx++){
          f_tab[idx+1] = next_f_m(r, dr, f_tab[idx-1], f_tab[idx], f);
    }

    //------ zapis do pliku --------
    if(SAVE){
        FILE* fp = fopen(filename, "w");
        for(r = r_min, idx = 0; idx < size; idx++, r+=dr){
            fprintf( fp, "%g %g %g %g\n", r, f_tab[idx], f_analitic(r), f_analitic(r) - f_tab[idx] );
        }
        fclose(fp);
    }
    free(f_tab);
}

//################## ZADANIE_4 ###########################//
void zad4(double r_min, double r_max, double dr, const char* filename){
    double r;

    double f_tab[ M ] = {0};
    //wartości dla każdej iteracji, na początku zerujemy

    int idx = 1;
    //iterator

    f_tab[ M-1 ] = f_tab[ M-2 ] = -3.0;
    //warunki brzegowe, czyli wartość f w r = 29 i r = 30


    //obliczanie kolejnych elementów siatki
    for(r = r_max - 1.0 * dr, idx = M - 2; idx > 0; r -= dr, idx--){
          //f_tab[idx-1] = prev_f_m(r, dr, f_tab[idx], f_tab[idx+1], f);
          f_tab[idx-1] = prev_f_m_num(r, dr, f_tab[idx], f_tab[idx+1], f);
    }

    //------ zapis do pliku --------
    if(SAVE){
        FILE* fp = fopen(filename, "w");
        for(r = r_min, idx = 0; idx < M; idx++, r+=dr){
            fprintf( fp, "%g %g %g %g\n", r, f_tab[idx], f_analitic(r), f_analitic(r) - f_tab[idx] );
        }
        fclose(fp);
    }
}


//################## ZADANIE_5 ###########################//
void zad5(double r_min, double r_max, double dr, int bullet, const char* filename){
    double r;
    int size = (int)(r_max/dr);

    double* f_tab = malloc( size * sizeof(double) );
    int i = 0;
    for(i = 0; i < size; i++ )
        f_tab[i] = 0.0;

    //wartości dla każdej iteracji, na początku zerujemy

    int idx = 1;
    //iterator

    f_tab[1] = (bullet == 3 ? f1 : f_analitic(r_min+dr) );

    //obliczanie kolejnych elementów siatki
    for(r = r_min + dr, idx = 1; idx < size-1; r += dr, idx++){
		f_tab[idx+1] = next_f_m_num(r, dr, f_tab[idx-1], f_tab[idx], f);          
    }

    //------ zapis do pliku --------
    if(SAVE){
        FILE* fp = fopen(filename, "w");
        for(r = r_min, idx = 0; idx < size; idx++, r+=dr){
            fprintf( fp, "%g %g %g %g\n", r, f_tab[idx], f_analitic(r), f_analitic(r) - f_tab[idx] );
        }
        fclose(fp);
    }
    free(f_tab);
}

//################## ZADANIE_6 ###########################//
void zad6(double r_min, double r_max, double dr, const char* filename) {
    FILE* fp = fopen(filename, "w");
        
	double r;
	double tmpf, tmpg;
	double df = -3.0;
	double dg = 0.0;

	for( r = r_max; r > r_min + dr; r -= dr ) {
		RK2(r, &df, &dg, -dr);
		fprintf(fp,"%g %g %g %g %g\n", r - dr, df, dg, f_analitic( r - dr ), fabs( df - f_analitic( r - dr ) ) );
	}

    fclose(fp);
}


int main(void) {
    f1 = zad1(0.0, 30.0, 0.1, 1e-13, "zad1_e-13.dat");
    zad1(0.0, 30.0, 0.1, 1e-7, "zad1_e-7.dat");
    zad1(0.0, 30.0, 0.1, 1e-5, "zad1_e-5.dat");

    zad2(0.0, 30.0, 0.1, "zad2.dat");

    zad3(0.0, 30.0, 0.1, 1, "zad3_1.dat");
    zad3(0.0, 30.0, 0.01, 2, "zad3_2.dat");
    zad3(0.0, 30.0, 0.1, 3, "zad3_3.dat");
    
    zad4(0.0, 30.0, 0.1, "zad4.dat");

    zad5(0.0, 30.0, 0.1, 1, "zad5_1.dat");
    zad5(0.0, 30.0, 0.01, 2, "zad5_2.dat");
    zad5(0.0, 30.0, 0.1, 3, "zad5_3.dat");
    
    zad6(0.0, 30.0, 0.1, "zad6.dat");

    return 0;
}

