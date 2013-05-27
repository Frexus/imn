#include <iostream>
#include <fstream>
#include <cmath>

#define X 201
#define Y 102
#define EPSILON 10e-6

using namespace std;

void zad1()
{
	// x to y!!!
	ofstream calka("z1a.dat");
	ofstream map("z1map.dat");
	double phi[X][Y] = {0};

	/*
	for(int i = 0; i < X; ++i)
	{
		for(int j = 0; j < Y; ++j)
		{
			if(i == 0 || i == X - 1 || j == Y - 1)
			{
				phi[i][j] = j + 100;
			}
			else if(j == 0)
			{
				phi[i][j] = phi[0][0];
			}
			else
			{
				phi[i][j] = 0;
			}
		}
	}*/
	
	for(int i = 0; i < Y; ++i)
	{
		phi[0][i] = i+100;
		phi[X-1][i] = i+100;
	}
	for(int i = 0; i < X; ++i)
	{
 		phi[i][Y-1] = Y-1 + 100;
        phi[i][0] = 100;
	}
	
	for(int i = 0; i < 20; ++i)
	{
		phi[79][i] = 100;
		phi[119][i] = 100;
	}
	for(int i = 79; i < 120; ++i)
	{
		phi[i][20] = 100;
	}
	double a = 0, preva;
	
	int it = 0;
	
	do
	{
		preva = a;
		a = 0;
		for( int i = 1; i < X - 1; i++ )
		{
			for( int j = 1; j < Y - 1; j++ )
			{
				if(j <= 20 && i >= 79 && i < 120)
				{
					//phi[i][j] = 0;
					continue;
				}
				else 
				{
					phi[i][j] = (phi[i - 1][j] + phi[i][j - 1] + phi[i + 1][j] + phi[i][j + 1] ) / 4.;
				}
			}
		}

		for(int i = 1; i < X - 1; ++i)
		{
			for(int j = 1; j < Y - 1; ++j)
			{
				if(j <= 20 && i >= 79 && i < 120)
				{
					continue;
				}
				else
				{
					a += pow(phi[i+1][j]-phi[i-1][j], 2) + pow(phi[i][j + 1] - phi[i][j - 1], 2);
				}
			}
		}
		a /= 8.;
		calka << it++ << " " << a << "\n";
	}
	while( fabs(preva - a) > EPSILON );
	
	for(int i = 0; i < X; ++i)
	{
		for(int j = 0; j < Y; ++j)
		{
			map << i + 1 << " " << j + 100 << " " << phi[i][j] << "\n";
		}
		map << "\n";
	}

}

void zad2()
{
	ofstream calka("z2a.dat");
	ofstream map("z2map.dat");
	double phi[X][Y];
	phi[0][0] = 1;
	for( int i = 0; i < X; i++ )
	{
		for( int j = 0; j < Y; j++)
		{
		/*
			if((i >= 79 && i < 120 && j == 20) || ((i == 79 || i == 119) && (j >= 0 && j <20)))
			{
				phi[i][j] = phi[0][0];
			}
			*/
			//else //if (i != 79 && i != 119)
			{
				phi[i][j] = i + 1; 
			}
		}
	}
	
	double a = 0, preva;
	int it = 0;
	do
	{
		// Neumann
		for(int i = 0; i < X; i++)
		{
			phi[i][0] = phi[i][1];
		}

		for(int i = 0; i < 20; i++)
		{
			phi[79][i] = phi[78][i];
			phi[119][i] = phi[120][i];
		}
		
		for(int i = 79; i < 120; i++)
		{
			phi[i][20] = phi[i][21];
		}
		
		phi[79][20] = (phi[78][20] + phi[79][21]) / 2.;
		phi[119][20] = (phi[120][20] + phi[119][21]) / 2.;
		
		preva = a;
		a = 0;
		for( int i = 1; i < X - 1; i++ )
		{
			for( int j = 1; j < Y - 1; j++ )
			{
				if(j <= 20 && i >= 79 && i < 120)
				{
					continue;
				}
				else 
				{
					phi[i][j] = ( phi[i - 1][j] + phi[i][j - 1] + phi[i + 1][j] + phi[i][j + 1]  ) / (4.0);
				}
			}
		}

		for(int i = 1; i < X - 1; ++i)
		{
			for(int j = 1; j < Y - 1; ++j)
			{
				if(j <= 20 && i >= 79 && i < 120)
				{
					continue;
				}
				else
				{
					a += pow(phi[i+1][j]-phi[i-1][j], 2) + pow(phi[i][j + 1] - phi[i][j - 1], 2);
				}
			}
		}
		a /= 8.;
		calka << it++ << " " << a << "\n";
	}
	while(fabs(preva - a) > EPSILON);
	
	
	for(int i = 0; i < X; ++i)
	{
		for(int j = 0; j < Y; ++j)
		{
			if(j < 20 && i >= 79 && i < 120)
			{
				phi[i][j] = 0;
			}
			map << i + 1 << " " << j + 100 << " " << phi[i][j] << "\n";
		}
		map << "\n";
	}

    ofstream cisnienie("z3.dat");
    double pe[X][Y] = {0};
    for(int i=79; i < 120; ++i)
    {
    	for(int j = 0; j <20; ++j)
    	{
    	phi[i][j] = 0;
    	}
    }
 		for( int i = 1; i < X - 1; i++ )
		{
			for( int j = 1; j < Y - 1; j++ )
			{
				if(i < 79 || i > 119 || j > 20)
				{
					pe[i][j] = 10. + 1. - pow((phi[i+1][j] - phi[i-1][j])/2.,2) - pow((phi[i][j+1] - phi[i][j-1])/2.,2); 
					//continue;
				}
				else
				{
                   //pe[i][j] = 10. + 1. - pow((phi[i+1][j] - phi[i-1][j])/2.,2) - pow((phi[i][j+1] - phi[i][j-1])/2.,2); 
				}
                cisnienie << i << " " << j+99 << " " << pe[i][j] << '\n';
			}
            cisnienie << '\n';
		}

}

int main()
{
#ifdef Z1
	zad1();
#endif
#ifdef Z2
	zad2();
#endif
}
