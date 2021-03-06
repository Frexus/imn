#include <iostream>
#include <ios>
#include <fstream>
#include <ostream>
#include <cstdio>
#include <cstdlib>
#include <cmath>

using namespace std;

#define EXP(x) pow(2.7182818, (x))

double euler(double un, double dt, double f)
{
	return un+dt*f;
}

double trapez(double un, double dt, double f1, double f2)
{
	return un+dt*(f1+f2)/2;
}

double z1f(double t)
{
	return 20.0 * t;
}

double z2f(double t, double u)
{
    return -10.0*(u-5.0*t*t)+10.0*t;
}

double dokladne_z1f(double t)
{
    return 10.0*t*t;
}

double dokladne_z2f(double t)
{
    return EXP(-10.0*t)+5.0*t*t;
}

double z3f(double t, double u, double dt)
{
    double tmpu = (u+50.0*pow(t,2)*dt+10.0*t*dt)/(1.0+10.0*dt);
    return tmpu;
}

double z4iter(double t, double u, double dt, double umi)
{
    return u + (-10.0*(umi - 5.0*t*t) + 10.0*t)*dt;
}

double z5iter(double t, double u, double dt, double umi)
{
    return umi - ((umi-u-dt*z2f(t, umi))/(1-dt*(-10.0)));
}

double z6fpoch(double u)
{
    return 3.0*u*u-6.0*u+2;
}

double z6f(double u)
{
    return u*(u-1.0)*(u-2.0);
}

double z6iter(double t, double u, double dt, double umi)
{
    return umi - ((umi-u-dt*z6f(umi))/(1-dt*(z6fpoch(umi))));
}

double z7filoraz(double u, double du)
{
    return (z6f(u+du)-z6f(u-du))/(2.0*du);
}

double z7iter(double t, double u, double dt, double umi, double du)
{
    return umi - ((umi-u-dt*z6f(umi))/(1-dt*(z7filoraz(umi, du))));
}

double z8filoraz(double u, double du, double t)
{
    return (z2f(t, u+du)-z2f(t, u-du))/(2.0*du);
}

double z8iter(double umi, double t, double prevt, double u, double dt, double du)
{
    return umi-(umi-u-(dt/2.0)*z2f(t,umi)+z2f(prevt,u))/(1.0-(dt/2.0)*z8filoraz(umi, du, t));
}

double z8u(double t, double u, double dt, double du)
{
    double z8it = u, z8it2;
    double epsilon = 1e-6;
    double counter;
    do{
        counter++;
        z8it2 = z8it;
        z8it = z8iter(z8it2, t, t-dt, u, dt, du);
        cout << std::fixed << z8it << "\n";
        if(counter == 1000) {
            cout << "Za duzo iteracji." << "\n";
            break;
        }
    } while(fabs(z8it2-z8it) >= epsilon);
    return z8it;
}


int main()
{
    cout.precision(6);
    // ZADANIE 1A
	double dt = 1.;
    std::ofstream eu_jaw_f("zad1A_jaw.txt");
    std::ofstream eu_njaw_f("zad1A_njaw.txt");
    std::ofstream trap_f("zad1A_trap.txt");
    double eu_jaw = 0;
    double eu_njaw = 0;
    double trap = 0;
    eu_jaw_f.precision(10);
    eu_njaw_f.precision(10);
    trap_f.precision(10);
    for(double t=0.0; t<51.0; t+=dt)
	{
        eu_jaw = euler(eu_jaw, dt, z1f(t-dt));
        eu_njaw = euler(eu_njaw, dt, z1f(t));
        trap = trapez(trap, dt, z1f(t-dt), z1f(t));
        eu_jaw_f << t << " " << fabs(eu_jaw-dokladne_z1f(t)) << "\n";
        eu_njaw_f << t << " " << fabs(eu_njaw-dokladne_z1f(t)) << "\n";
        trap_f << t << " " << fabs(trap-dokladne_z1f(t)) << "\n";
	}
    eu_jaw_f.close();
    eu_njaw_f.close();
    trap_f.close();

    //ZADANIE 2A
    eu_jaw = 1;
    eu_njaw = 1;
    trap = 1;
    dt = 0.01;
    eu_jaw_f.open("zad2_eu1.txt");
    std::ofstream dok_f("zad2_dok1.txt");
    std::ofstream err_f("zad2_err1.txt");
    dok_f.precision(10);
    err_f.precision(10);
    for(double t = 0.0; t < 8.0; t+=dt)
    {
        eu_jaw = euler(eu_jaw, dt, z2f(t, eu_jaw));
        eu_jaw_f << t << " " << eu_jaw << "\n";
        dok_f << t << " " << dokladne_z2f(t) << "\n";
        err_f << t << " " << fabs(eu_jaw - dokladne_z2f(t)) << "\n";
    }

    eu_jaw = 1;
    eu_jaw_f.close();
    dok_f.close();
    err_f.close();
    eu_jaw_f.open("zad2_eu2.txt");
    dok_f.open("zad2_dok2.txt");
    err_f.open("zad2_err2.txt");
    dt = 0.1;
    for(double t = 0.0; t < 8.0; t+=dt)
    {
        eu_jaw = euler(eu_jaw, dt, z2f(t, eu_jaw));
        eu_jaw_f << t << " " << eu_jaw << "\n";
        dok_f << t << " " << dokladne_z2f(t) << "\n";
        err_f << t << " " << fabs(eu_jaw - dokladne_z2f(t)) << "\n";
    }
    eu_jaw = 1;
    eu_jaw_f.close();
    dok_f.close();
    err_f.close();
    eu_jaw_f.open("zad2_eu3.txt");
    dok_f.open("zad2_dok3.txt");
    err_f.open("zad2_err3.txt");
    dt = 0.2;
    for(double t = 0.0; t < 8.0; t+=dt)
    {
        eu_jaw = euler(eu_jaw, dt, z2f(t, eu_jaw));
        eu_jaw_f << t << " " << eu_jaw << "\n";
        dok_f << t << " " << dokladne_z2f(t) << "\n";
        err_f << t << " " << fabs(eu_jaw - dokladne_z2f(t)) << "\n";
    }
    eu_jaw = 1;
    eu_jaw_f.close();
    dok_f.close();
    err_f.close();
    eu_jaw_f.open("zad2_eu4.txt");
    dok_f.open("zad2_dok4.txt");
    err_f.open("zad2_err4.txt");
    dt = 0.215;
    for(double t = 0.0; t < 8.0; t+=dt)
    {
        eu_jaw = euler(eu_jaw, dt, z2f(t, eu_jaw));
        eu_jaw_f << t << " " << eu_jaw << "\n";
        dok_f << t << " " << dokladne_z2f(t) << "\n";
        err_f << t << " " << fabs(eu_jaw - dokladne_z2f(t)) << "\n";
    }

    // ZADANIE 3
    eu_jaw_f.close();
    dok_f.close();
    err_f.close();
    eu_njaw_f.close();
    eu_njaw_f.open("zad3_eu1.txt");
    dok_f.open("zad3_dok1.txt");
    err_f.open("zad3_err1.txt");
    dt = 0.01;
    eu_njaw = 1;
    for(double t = 0.0; t <= 8.0; t+=dt)
    {
        eu_njaw = euler(eu_njaw, dt, z2f(t, eu_njaw));
        eu_njaw_f << t << " " << eu_njaw << "\n";
        dok_f << t << " " << dokladne_z2f(t) << "\n";
        err_f << t << " " << fabs(eu_njaw - dokladne_z2f(t)) << "\n";
    }

    dok_f.close();
    err_f.close();
    eu_njaw_f.close();
    eu_njaw_f.open("zad3_eu2.txt");
    dok_f.open("zad3_dok2.txt");
    err_f.open("zad3_err2.txt");
    dt = 0.1;
    eu_njaw = 1;
    for(double t = 0.0; t <= 8.0; t+=dt)
    {
        eu_njaw = euler(eu_njaw, dt, z2f(t, eu_njaw));
        eu_njaw_f << t << " " << eu_njaw << "\n";
        dok_f << t << " " << dokladne_z2f(t) << "\n";
        err_f << t << " " << fabs(eu_njaw - dokladne_z2f(t)) << "\n";
    }

    dok_f.close();
    err_f.close();
    eu_njaw_f.close();
    eu_njaw_f.open("zad3_eu3.txt");
    dok_f.open("zad3_dok3.txt");
    err_f.open("zad3_err3.txt");
    dt = 0.2;
    eu_njaw = 1;
    for(double t = 0.0; t <= 8.0; t+=dt)
    {
        eu_njaw = euler(eu_njaw, dt, z2f(t, eu_njaw));
        eu_njaw_f << t << " " << eu_njaw << "\n";
        dok_f << t << " " << dokladne_z2f(t) << "\n";
        err_f << t << " " << fabs(eu_njaw - dokladne_z2f(t)) << "\n";
    }

    dok_f.close();
    err_f.close();
    eu_njaw_f.close();
    eu_njaw_f.open("zad3_eu4.txt");
    dok_f.open("zad3_dok4.txt");
    err_f.open("zad3_err4.txt");
    dt = 0.215;
    eu_njaw = 1;
    for(double t = 0.0; t <= 8.0; t+=dt)
    {
        eu_njaw = euler(eu_njaw, dt, z2f(t, eu_njaw));
        eu_njaw_f << t << " " << eu_njaw << "\n";
        dok_f << t << " " << dokladne_z2f(t) << "\n";
        err_f << t << " " << fabs(eu_njaw - dokladne_z2f(t)) << "\n";
    }

    dok_f.close();
    err_f.close();
    eu_njaw_f.close();
    eu_njaw_f.open("zad3_eu5.txt");
    dok_f.open("zad3_dok5.txt");
    err_f.open("zad3_err5.txt");
    dt = 1.33;
    eu_njaw = 1;
    for(double t = 0.0; t <= 8.0; t+=dt)
    {
        eu_njaw = euler(eu_njaw, dt, z2f(t, eu_njaw));
        eu_njaw_f << t << " " << eu_njaw << "\n";
        dok_f << t << " " << dokladne_z2f(t) << "\n";
        err_f << t << " " << fabs(eu_njaw - dokladne_z2f(t)) << "\n";
    }

    //ZADANIE 4
    dt = 0.01;
    double z4it = 1;
    double u = 1;
    double epsilon = 1e-6;
    double z4it2;
    int counter = 0;
    cout << "Zadanie 4, dt=" << dt << "\n";
    do
    {
        counter++;
        z4it2 = z4it;
        z4it = z4iter(dt, u, dt, z4it);
        cout << std::fixed << z4it << "\n";
        if(counter == 1000) {
            cout << "Za duzo iteracji." << "\n";
            break;
        }
    } while(fabs(z4it2-z4it) >= epsilon);
    cout << "Liczba krokow: " << counter << "\n";

//    cout << "Dokladne: " << dokladne_z2f(dt);
    counter = 0;
    dt = 0.1;
    z4it = 1;
    z4it2 = 999;
    cout << "Zadanie 4, dt=" << dt << "\n";
    do
    {
        counter++;
        z4it2 = z4it;
        z4it = z4iter(dt, u, dt, z4it);
        cout << std::fixed << z4it << "\n";
        if(counter == 1000) {
            cout << "Za duzo iteracji." << "\n";
            break;
        }
    } while(fabs(z4it2-z4it) >= epsilon);
    cout << "Liczba krokow: " << counter << "\n";

    counter = 0;
    dt = 0.11;
    z4it = 1;
    z4it2 = 999;
    cout << "Zadanie 4, dt=" << dt << "\n";
    do
    {
        counter++;
        z4it2 = z4it;
        z4it = z4iter(dt, u, dt, z4it);
        cout << std::fixed << z4it << "\n";
        if(counter == 1000) {
            cout << "Za duzo iteracji." << "\n";
            break;
        }
    } while(fabs(z4it2-z4it) >= epsilon);
    cout << "Liczba krokow: " << counter << "\n";

    //ZADANIE 5
    dt = 1.33;
    u = 1;
    double z5it = 1;
    double z5it2;
    counter=0;
    cout << "Zadanie 5, dt=" << dt << "\n";
    do{
        counter++;
        z5it2 = z5it;
        z5it = z5iter(dt, u, dt, z5it);
        cout << std::fixed << z5it << "\n";
        if(counter == 1000) {
            cout << "Za duzo iteracji." << "\n";
            break;
        }
    } while(fabs(z5it2-z5it) >= epsilon);
    cout << "Liczba krokow: " << counter << "\n";

    //ZADANIE 6
    counter=0;
    dt = 1.0;
    u = 1.5;
    double z6it = u;
    double z6it2;
    cout << "Zadanie 6, dt=" << dt << "\n";
    do{
        counter++;
        z6it2 = z6it;
        z6it = z6iter(dt, u, dt, z6it);
        cout << std::fixed << z6it << "\n";
        if(counter == 1000) {
            cout << "Za duzo iteracji." << "\n";
            break;
        }
    } while(fabs(z6it2-z6it) >= epsilon);
    cout << "Liczba krokow: " << counter << "\n";

    //ZADANIE 7
    counter=0;
    dt = 1.0;
    u = 1.5;
    double z7it = u;
    double z7it2;
    double du = 0.3;
    cout << "Zadanie 7, dt=" << dt << "\n";
    do{
        counter++;
        z7it2 = z7it;
        z7it = z7iter(dt, u, dt, z7it, du);
        cout << std::fixed << z7it << "\n";
        if(counter == 1000) {
            cout << "Za duzo iteracji." << "\n";
            break;
        }
    } while(fabs(z7it2-z7it) >= epsilon);
    cout << "Liczba krokow: " << counter << "\n";

    //ZADANIE 8
    counter=0;
    dt = 0.2;
    u = 1.5;
    double z8it = u;
    double z8it2;
    double un_1;
    du = 0.3;
    cout << "Zadanie 8, dt=" << dt << "\n";
    ofstream z8_f("zadanie8.txt");
    for(double t=0; t < 30; t+=dt) {
//        z8it = u;
//        do{
//            counter++;
//            z8it2 = z8it;
//            z8it = z8iter(z8it2, t, t-dt, u, dt, du);
//            cout << std::fixed << z8it << "\n";
//            if(counter == 1000) {
//                cout << "Za duzo iteracji." << "\n";
//                break;
//            }
//        } while(fabs(z8it2-z8it) >= epsilon);
//        z8_f << euler(z8it2, dt, z2f(t-dt, z8it)) << "\n";
        un_1 = u;
        u = z8u(t, un_1, dt, du);
        z8_f << euler(un_1, dt, z2f(t, u)) << "\n";

    }
    cout << "Liczba krokow: " << counter << "\n";
}
