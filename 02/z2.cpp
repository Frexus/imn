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

void rk2_uklad(double& u1, double& u2, double prevu1, double prevu2, double prevt, double dt, double (*f1)(double t, double uf, double ut), double (*f2)(double t, double uf, double ut))
{
    double k11 = f1(prevt, prevu1, prevu2);
    double k12 = f2(prevt, prevu1, prevu2);
    double k21 = f1(prevt + dt, prevu1+dt * k11, prevu2 + dt * k12);
    double k22 = f2(prevt + dt, prevu1+dt * k11, prevu2 + dt * k12);
    u1 = prevu1 + (dt/2.0)*(k11 + k21);
    u2 = prevu2 + (dt/2.0)*(k12 + k22);
}

int main()
{
    double v1 = 0, x1 = 0.5, v2 = 0, x2 = 0.5;
    double S = 0.75;
    double tol = 0.1;
    double dt = 0.1;
    cout << "Licze dla tolreancji " << tol << "\n";
    ofstream x_f("z2_x_tol1.txt");
    ofstream v_f("z2_v_tol1.txt");
    ofstream en_f("z2_en_tol1.txt");
    for(double t = dt; t < 32; t += dt ){
        v1 = v2;
        x1 = x2;
        rk2_uklad(v2, x2, v1, x1, t-dt, dt, func1, func2);

        double Ev = err(v2, v1, 3);
        double Ex = err(x2, x1, 3);

        if(Ev < tol)
            v_f << t << " " << v2 << "\n";
        if(Ex < tol)
            x_f << t << " " << x2 << "\n";
        if(Ex < tol && Ev < tol)
            en_f << t << " " << 1.0/2.0 * (x2*x2 + v2*v2) << "\n";

        double vtime = new_time(S, tol, Ev, dt, 3);
        double xtime = new_time(S, tol, Ex, dt, 3);

        dt = vtime > xtime ? xtime : vtime;
        //cout << dt << endl;
    }
    x_f.close();
    v_f.close();
    en_f.close();
    en_f.open("z2_en_tol01.txt");
    x_f.open("z2_x_tol01.txt");
    v_f.open("z2_v_tol01.txt");
    dt = 0.1;
    v1 = 0; x1 = 0.5; v2 = 0; x2 = 0.5;
    tol = 0.01;
    cout << "Licze dla tolreancji " << tol << "\n";
    for(double t = dt; t < 32; t += dt ){
        v1 = v2;
        x1 = x2;
        rk2_uklad(v2, x2, v1, x1, t-dt, dt, func1, func2);

        double Ev = err(v2, v1, 3);
        double Ex = err(x2, x1, 3);

        if(Ev < tol)
            v_f << t << " " << v2 << "\n";
        if(Ex < tol)
            x_f << t << " " << x2 << "\n";
        if(Ex < tol && Ev < tol)
            en_f << t << " " << 1.0/2.0 * (x2*x2 + v2*v2) << "\n";

        double vtime = new_time(S, tol, Ev, dt, 3);
        double xtime = new_time(S, tol, Ex, dt, 3);

        dt = vtime > xtime ? xtime : vtime;
        //cout << dt << endl;
    }

    x_f.close();
    v_f.close();
    en_f.close();
    en_f.open("z2_en_tol001.txt");
    x_f.open("z2_x_tol001.txt");
    v_f.open("z2_v_tol001.txt");
    dt = 0.1;
    v1 = 0; x1 = 0.5; v2 = 0; x2 = 0.5;
    tol = 0.001;
    cout << "Licze dla tolreancji " << tol << "\n";
    for(double t = dt; t < 32; t += dt ){
        v1 = v2;
        x1 = x2;
        rk2_uklad(v2, x2, v1, x1, t-dt, dt, func1, func2);

        double Ev = err(v2, v1, 3);
        double Ex = err(x2, x1, 3);

        if(Ev < tol)
            v_f << t << " " << v2 << "\n";
        if(Ex < tol)
            x_f << t << " " << x2 << "\n";
        if(Ex < tol && Ev < tol)
            en_f << t << " " << 1.0/2.0 * (x2*x2 + v2*v2) << "\n";

        double vtime = new_time(S, tol, Ev, dt, 3);
        double xtime = new_time(S, tol, Ex, dt, 3);

        dt = vtime > xtime ? xtime : vtime;
        //cout << dt << endl;
    }

    x_f.close();
    v_f.close();
    en_f.close();
    en_f.open("z2_en_tol0001.txt");
    x_f.open("z2_x_tol0001.txt");
    v_f.open("z2_v_tol0001.txt");
    dt = 0.1;
    v1 = 0; x1 = 0.5; v2 = 0; x2 = 0.5;
    tol = 0.0001;
    cout << "Licze dla tolreancji " << tol << "\n";
    for(double t = dt; t < 32; t += dt ){
        v1 = v2;
        x1 = x2;
        rk2_uklad(v2, x2, v1, x1, t-dt, dt, func1, func2);

        double Ev = err(v2, v1, 3);
        double Ex = err(x2, x1, 3);

        if(Ev < tol)
            v_f << t << " " << v2 << "\n";
        if(Ex < tol)
            x_f << t << " " << x2 << "\n";
        if(Ex < tol && Ev < tol)
            en_f << t << " " << 1.0/2.0 * (x2*x2 + v2*v2) << "\n";

        double vtime = new_time(S, tol, Ev, dt, 3);
        double xtime = new_time(S, tol, Ex, dt, 3);

        dt = vtime > xtime ? xtime : vtime;
        //cout << dt << endl;
    }

    x_f.close();
    v_f.close();
    en_f.close();
    en_f.open("z2_en_tol00001.txt");
    x_f.open("z2_x_tol00001.txt");
    v_f.open("z2_v_tol00001.txt");
    dt = 0.1;
    v1 = 0; x1 = 0.5; v2 = 0; x2 = 0.5;
    tol = 0.00001;
    cout << "Licze dla tolreancji " << tol << "\n";
    for(double t = dt; t < 32; t += dt ){
        v1 = v2;
        x1 = x2;
        rk2_uklad(v2, x2, v1, x1, t-dt, dt, func1, func2);

        double Ev = err(v2, v1, 5);
        double Ex = err(x2, x1, 5);

        if(Ev < tol)
            v_f << t << " " << v2 << "\n";
        if(Ex < tol)
            x_f << t << " " << x2 << "\n";
        if(Ex < tol && Ev < tol)
            en_f << t << " " << 1.0/2.0 * (x2*x2 + v2*v2) << "\n";

        double vtime = new_time(S, tol, Ev, dt, 3);
        double xtime = new_time(S, tol, Ex, dt, 3);

        dt = vtime > xtime ? xtime : vtime;
        //cout << dt << endl;
    }

    x_f.close();
    v_f.close();
    en_f.close();
    en_f.open("z2_en_tol000001.txt");
    x_f.open("z2_x_tol000001.txt");
    v_f.open("z2_v_tol000001.txt");
    dt = 0.1;
    v1 = 0; x1 = 0.5; v2 = 0; x2 = 0.5;
    tol = 0.000001;
    cout << "Licze dla tolreancji " << tol << "\n";
    for(double t = dt; t < 32; t += dt ){
        v1 = v2;
        x1 = x2;
        rk2_uklad(v2, x2, v1, x1, t-dt, dt, func1, func2);

        double Ev = err(v2, v1, 3);
        double Ex = err(x2, x1, 3);

        if(Ev < tol)
            v_f << t << " " << v2 << "\n";
        if(Ex < tol)
            x_f << t << " " << x2 << "\n";
        if(Ex < tol && Ev < tol)
            en_f << t << " " << 1.0/2.0 * (x2*x2 + v2*v2) << "\n";

        double vtime = new_time(S, tol, Ev, dt, 3);
        double xtime = new_time(S, tol, Ex, dt, 3);

        dt = vtime > xtime ? xtime : vtime;
        //cout << dt << endl;
    }
}
