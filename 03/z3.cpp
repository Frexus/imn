#include <iostream>
#include <ios>
#include <fstream>
#include <ostream>
#include <cstdio>
#include <cstdlib>
#include <cmath>

using namespace std;

double euler(double prevY, double t, double dt, double (*f)(double t, double y))
{
    return prevY + dt*f(t-dt, prevY);
}

double rk2(double prevY, double t, double dt, double (*f)(double t, double y))
{
    return prevY + dt * f(t-dt + (dt/2.0), prevY + (1.0*dt*f(t-dt, prevY))/(2.0));
}

double richardson(double y1, double y2, int n)
{
    return y1 + (y2 - y1)/(pow(2, n-1) - 1);
}

double err(double y2, double y1, double n)
{
    return (y2-y1)/(pow(2.0,n-1.0) - 1.0);
}

double new_time(double S, double tol, double E, double dt, double n)
{
    return pow((S*tol)/abs(E), 1.0/n)*dt;
}

double func1 (double t, double x, double v)
{
    return (8.0/32.0) * 3.1415 * v;
}

double func2(double t, double x, double v)
{
    return -(8.0/32.0) * 3.1415 * x;
}

void rk4_uklad(double& u1, double& u2, double prevu1, double prevu2, double prevt, double dt, double (*f1)(double t, double uf, double ut), double (*f2)(double t, double uf, double ut))
{
    double k11 = f1(prevt, prevu1, prevu2);
    double k12 = f2(prevt, prevu1, prevu2);
    double k21 = f1(prevt + dt/2.0, prevu1+dt * k11/2.0, prevu2 + dt * k12/2.0);
    double k22 = f2(prevt + dt, prevu1+dt * k11/2.0, prevu2 + dt * k12/2.0);
    double k31 = f1(prevt + dt/2.0, prevu1 + dt*k21/2.0, prevu2+dt*k22/2.0);
    double k32 = f2(prevt + dt/2.0, prevu1 + dt*k21/2.0, prevu2+dt*k22/2.0);
    double k41 = f1(prevt + dt, prevu1 + dt * k31, prevu2 + dt * k32);
    double k42 = f2(prevt + dt, prevu1 + dt * k31, prevu2 + dt * k32);
    u1 = prevu1 + (dt/6.0)*(k11 + 2.*k21 + 2.*k31 + k41);
    u2 = prevu2 + (dt/6.0)*(k12 + 2.*k22 + 2.*k32 + k42);
}

void task(double v1, double x1, double v2, double x2, double tol, char* x_f, char* en_f, char* dt_f)
{

}

int main()
{
    double v1 = 0, x1 = 0.5, v2 = 0, x2 = 0.5;
    double S = 0.75;
    double tol = 0.1;
    double dt = 0.1;
    double prevdt = 0.1;
    cout << "Licze dla tolreancji " << tol << "\n";
    ofstream x_f("z3_x_tol1.txt");
    ofstream en_f("z3_en_tol1.txt");
    ofstream dt_f("z3_dt_tol1.txt");
    int krok = 0;
    for(double t = 0, prevt = 0; t < 32; ){
        v1 = v2;
        x1 = x2;
        rk4_uklad(v1, x1, v1, x1, t, dt*2, func1, func2);

        rk4_uklad(v2, x2, v2, x2, t, dt, func1, func2);
        rk4_uklad(v2, x2, v2, x2, t + dt, dt, func1, func2);

        double Ev = err(v2, v1, 5);
        double Ex = err(x2, x1, 5);

//        if(Ev < tol)
//            v_f << t << " " << v2 << "\n";
//        if(Ex < tol)
//            x_f << t << " " << x2 << "\n";
        if(Ex < tol && Ev < tol)
        {
            t+=dt+dt;
            x_f << x2 << " " << v2 << "\n";
            en_f << t << " " << 1.0/2.0 * (x2*x2 + v2*v2) << "\n";
        }

        double vtime = new_time(S, tol, Ev, dt, 5);
        double xtime = new_time(S, tol, Ex, dt, 5);
        prevt = t;
        dt = vtime > xtime ? xtime : vtime;
        dt_f << t << " " << dt << " " << x2*x2 << " " << v2*v2 << "\n";
        //cout << dt << endl;
    }
    x_f.close();
    en_f.close();
    dt_f.close();
    dt_f.open("z3_dt_tol01.txt");
    krok = 0;
    v1 = 0, x1 = 0.5, v2 = 0, x2 = 0.5;
    tol = 0.01;
    cout << "Licze dla tolreancji " << tol << "\n";
    x_f.open("z3_x_tol01.txt");
    en_f.open("z3_en_tol01.txt");
    for(double t = 0, prevt = 0; t < 32; ){
        v1 = v2;
        x1 = x2;
        rk4_uklad(v1, x1, v1, x1, t, dt*2, func1, func2);

        rk4_uklad(v2, x2, v2, x2, t, dt, func1, func2);
        rk4_uklad(v2, x2, v2, x2, t + dt, dt, func1, func2);

        double Ev = err(v2, v1, 5);
        double Ex = err(x2, x1, 5);

//        if(Ev < tol)
//            v_f << t << " " << v2 << "\n";
//        if(Ex < tol)
//            x_f << t << " " << x2 << "\n";
        if(Ex < tol && Ev < tol)
        {
            t+=dt+dt;
            x_f << x2 << " " << v2 << "\n";
            en_f << t << " " << 1.0/2.0 * (x2*x2 + v2*v2) << "\n";
        }

        double vtime = new_time(S, tol, Ev, dt, 5);
        double xtime = new_time(S, tol, Ex, dt, 5);
        prevt = t;
        dt = vtime > xtime ? xtime : vtime;
        dt_f << t << " " << dt << " " << x2*x2 << " " << v2*v2 << "\n";

        //cout << dt << endl;
    }
    x_f.close();
    en_f.close();
    dt_f.close();
    dt_f.open("z3_dt_tol001.txt");
    krok = 0;
    v1 = 0, x1 = 0.5, v2 = 0, x2 = 0.5;
    tol = 0.001;
    cout << "Licze dla tolreancji " << tol << "\n";
    x_f.open("z3_x_tol001.txt");
    en_f.open("z3_en_tol001.txt");
    for(double t = 0, prevt = 0; t < 32; ){
        v1 = v2;
        x1 = x2;
        rk4_uklad(v1, x1, v1, x1, t, dt*2, func1, func2);

        rk4_uklad(v2, x2, v2, x2, t, dt, func1, func2);
        rk4_uklad(v2, x2, v2, x2, t + dt, dt, func1, func2);

        double Ev = err(v2, v1, 5);
        double Ex = err(x2, x1, 5);

//        if(Ev < tol)
//            v_f << t << " " << v2 << "\n";
//        if(Ex < tol)
//            x_f << t << " " << x2 << "\n";
        if(Ex < tol && Ev < tol)
        {
            t+=dt+dt;
            x_f << x2 << " " << v2 << "\n";
            en_f << t << " " << 1.0/2.0 * (x2*x2 + v2*v2) << "\n";
        }

        double vtime = new_time(S, tol, Ev, dt, 5);
        double xtime = new_time(S, tol, Ex, dt, 5);
        prevt = t;
        dt = vtime > xtime ? xtime : vtime;
        dt_f << t << " " << dt << " " << x2*x2 << " " << v2*v2 << "\n";

        //cout << dt << endl;
    }
    x_f.close();
    en_f.close();
    dt_f.close();
    dt_f.open("z3_dt_tol0001.txt");
    krok = 0;
    v1 = 0, x1 = 0.5, v2 = 0, x2 = 0.5;
    tol = 0.0001;
    cout << "Licze dla tolreancji " << tol << "\n";
    x_f.open("z3_x_tol0001.txt");
    en_f.open("z3_en_tol0001.txt");
    for(double t = 0, prevt = 0; t < 32; ){

        rk4_uklad(v1, x1, v1, x1, t, dt*2, func1, func2);

        rk4_uklad(v2, x2, v2, x2, t, dt, func1, func2);
        rk4_uklad(v2, x2, v2, x2, t + dt, dt, func1, func2);

        double Ev = err(v2, v1, 5);
        double Ex = err(x2, x1, 5);

//        if(Ev < tol)
//            v_f << t << " " << v2 << "\n";
//        if(Ex < tol)
//            x_f << t << " " << x2 << "\n";
        if(Ex < tol && Ev < tol)
        {
            v1 = v2;
            x1 = x2;
            t+=dt+dt;
            x_f << x2 << " " << v2 << "\n";
            en_f << t << " " << 1.0/2.0 * (x2*x2 + v2*v2) << "\n";
        }

        double vtime = new_time(S, tol, Ev, dt, 5);
        double xtime = new_time(S, tol, Ex, dt, 5);
        prevt = t;
        dt = vtime > xtime ? xtime : vtime;
        dt_f << t << " " << dt << " " << x2*x2 << " " << v2*v2 << "\n";

        //cout << dt << endl;
    }
    x_f.close();
    en_f.close();
    dt_f.close();
    dt_f.open("z3_dt_tol00001.txt");
    krok = 0;
    v1 = 0, x1 = 0.5, v2 = 0, x2 = 0.5;
    tol = 0.00001;
    cout << "Licze dla tolreancji " << tol << "\n";
    x_f.open("z3_x_tol00001.txt");
    en_f.open("z3_en_tol00001.txt");
    for(double t = 0, prevt = 0; t < 32; ){
        v1 = v2;
        x1 = x2;
        rk4_uklad(v1, x1, v1, x1, t, dt*2, func1, func2);

        rk4_uklad(v2, x2, v2, x2, t, dt, func1, func2);
        rk4_uklad(v2, x2, v2, x2, t + dt, dt, func1, func2);

        double Ev = err(v2, v1, 5);
        double Ex = err(x2, x1, 5);

//        if(Ev < tol)
//            v_f << t << " " << v2 << "\n";
//        if(Ex < tol)
//            x_f << t << " " << x2 << "\n";
        if(Ex < tol && Ev < tol)
        {
            t+=dt+dt;
            x_f << x2 << " " << v2 << "\n";
            en_f << t << " " << 1.0/2.0 * (x2*x2 + v2*v2) << "\n";
        }

        double vtime = new_time(S, tol, Ev, dt, 5);
        double xtime = new_time(S, tol, Ex, dt, 5);
        prevt = t;
        dt = vtime > xtime ? xtime : vtime;
        dt_f << t << " " << dt << " " << x2*x2 << " " << v2*v2 << "\n";

        //cout << dt << endl;
    }
    x_f.close();
    en_f.close();
    dt_f.close();
    dt_f.open("z3_dt_tol000001.txt");
    krok = 0;
    v1 = 0, x1 = 0.5, v2 = 0, x2 = 0.5;
    tol = 0.000001;
    cout << "Licze dla tolreancji " << tol << "\n";
    x_f.open("z3_x_tol000001.txt");
    en_f.open("z3_en_tol000001.txt");
    for(double t = 0, prevt = 0; t < 32;){
        v1 = v2;
        x1 = x2;
        rk4_uklad(v1, x1, v1, x1, t, dt*2, func1, func2);

        rk4_uklad(v2, x2, v2, x2, t, dt, func1, func2);
        rk4_uklad(v2, x2, v2, x2, t + dt, dt, func1, func2);

        double Ev = err(v2, v1, 5);
        double Ex = err(x2, x1, 5);

//        if(Ev < tol)
//            v_f << t << " " << v2 << "\n";
//        if(Ex < tol)
//            x_f << t << " " << x2 << "\n";
        if(Ex < tol && Ev < tol)
        {

            t+=dt+dt;
            x_f << x2 << " " << v2 << "\n";
            en_f << t << " " << 1.0/2.0 * (x2*x2 + v2*v2) << "\n";
        }

        double vtime = new_time(S, tol, Ev, dt, 5);
        double xtime = new_time(S, tol, Ex, dt, 5);
        prevt = t;
        dt = vtime > xtime ? xtime : vtime;
        dt_f << t << " " << dt << " " << x2*x2 << " " << v2*v2 << "\n";

        //cout << dt << endl;
    }
    x_f.close();
    en_f.close();
}
