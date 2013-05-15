#! /usr/bin/env gnuplot
set term png

set logscale x
set xlabel 'Numer iteracji iter'
set ylabel 'a(it)'
set out 'zad1a.png'
set title 'Calka a(it), siatka 257x257, tol=10^-9'
plot 'zad1_1.dat' u 1:2 w lp t 'a(it)'

unset logscale
set xlabel 'Numer iteracji iter'
set ylabel 'a(it)'
set out 'zad2a.png'
set title 'Calka a(it), siatka zalezna od k, tol=10^-9'
plot 'zad2a_k32.dat' u 1:2 w lp t 'k = 32', 'zad2a_k16.dat' u 1:2 w lp t 'k = 16', 'zad2a_k8.dat' u 1:2 w lp t 'k = 8', 'zad2a_k4.dat' u 1:2 w lp t 'k = 4', 'zad2a_k2.dat' u 1:2 w lp t 'k = 2', 'zad2a_k1.dat' u 1:2 w lp t 'k = 1'

set size square
unset logscale
unset key;
set view 0,0;
set xlabel 'x'
set ylabel 'y'
set xrange [-4:4]
set yrange [-4:4]
set pm3d map
set palette defined (-1 "blue", 0 "white", 1 "red")
set out 'zad1b.png'
set title 'Rozwiazanie analityczne - potencjal fi(x,y)=x^2-y^2'
splot 'zad1b.dat' u 1:2:3

set out 'zad2_32.png'
set title 'Rozwiazanie analityczne - potencjal fi(x,y)=x^2-y^2 k=32'
splot 'zad2b_k32.dat' u 1:2:3

set out 'zad2_16.png'
set title 'Rozwiazanie analityczne - potencjal fi(x,y)=x^2-y^2 k=16'
splot 'zad2b_k16.dat' u 1:2:3

set out 'zad2_k8.png'
set title 'Rozwiazanie analityczne - potencjal fi(x,y)=x^2-y^2 k=8'
splot 'zad2b_k8.dat' u 1:2:3

set out 'zad2_k4.png'
set title 'Rozwiazanie analityczne - potencjal fi(x,y)=x^2-y^2 k=4'
splot 'zad2b_k4.dat' u 1:2:3

set out 'zad2_k2.png'
set title 'Rozwiazanie analityczne - potencjal fi(x,y)=x^2-y^2 k=2'
splot 'zad2b_k2.dat' u 1:2:3

set out 'zad2_k1.png'
set title 'Rozwiazanie analityczne - potencjal fi(x,y)=x^2-y^2 k=1'
splot 'zad2b_k1.dat' u 1:2:3
