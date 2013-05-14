#! /usr/bin/env gnuplot
set term png

set logscale x
set xlabel 'Numer iteracji it'
set ylabel 'a( it )'

set output 'zad1.png'
set title 'calka a( it ), tol = 10^-6'
plot 'zad1.dat' u 1:2 w lp t 'dat/zad1.dat'

set output 'zad2.png'
set title 'calka a(it), tol=10^-6'
plot 'zad2.dat' u 1:2 w lp t 'dat/zad2.dat'

unset logscale
unset key;
set view 0,0;
set xlabel 'x'
set ylabel 'y'
set xrange [1:201]
set yrange [100:201]
set pm3d map

set output 'zad3.png'
set title 'Mapa cisnienia'
splot 'zad3.dat' u 1:2:3

unset pm3d
set contour base
unset clabel
set cntrparam levels 80;
set view 0,0;
unset surface

set output 'zad1b.png'
set title 'Linie strumienia cieczy'
splot 'zad1b.dat' u 1:2:3 w l

set output 'zad2b.png'
set title 'Linie strumienia cieczy'
splot 'zad2b.dat' u 1:2:3 w l

set output 'zad_1b_2b.png'
set title 'Linie strumienia cieczy'
splot 'zad2b.dat' u 1:2:3 w l, 'zad1b.dat' u 1:2:3 w l

