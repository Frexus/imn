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
    cout << "Zadanie 4, dt=" << dt << "\n";
    do
    {
        z4it2 = z4it;
        z4it = z4iter(dt, u, dt, z4it);
        cout << std::fixed << z4it << "\n";
    } while(fabs(z4it2-z4it) >= epsilon);
//    cout << "Dokladne: " << dokladne_z2f(dt);
    dt = 0.1;
    z4it = 1;
    z4it2 = 999;
//    cout << "Zadanie 4, dt=" << dt << "\n";
//    do
//    {
//        z4it2 = z4it;
//        z4it = z4iter(dt, u, dt, z4it);
//        cout << std::fixed << z4it << "\n";
//    } while(fabs(z4it2-z4it) >= epsilon);
    dt = 0.11;
    z4it = 1;
    z4it2 = 999;
    cout << "Zadanie 4, dt=" << dt << "\n";
//    do
//    {
//        z4it2 = z4it;
//        z4it = z4iter(dt, u, dt, z4it);
//        cout << std::fixed << z4it << "\n";
//    } while(fabs(z4it2-z4it) >= epsilon);

    //ZADANIE 5
    dt = 1.33;
    u = 1;
    double z5it = 1;
    double z5it2;
    do{
        z5it2 = z5it;
        z5it = z5iter(dt, u, dt, z5it);
        cout << std::fixed << z5it << "\n";
    } while(fabs(z4it2-z4it) >= epsilon);

}
