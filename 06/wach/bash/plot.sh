#! /usr/bin/env gnuplot

set term png
set grid
set key off

set xlabel 'E'
set ylabel 'psi(x=L;E)'
set out 'zad1a.png'
set title 'zad1a'
plot 'zad1a.dat' u 1:2 w lp 

set xlabel 'x'
set ylabel 'psi(x)'
set out 'zad1b.png'
set title 'zad1b'
plot 'zad1b.dat' u 1:2 w lp 

set xlabel 'x(s)'
set ylabel 'y(s)'
set out 'zad2a.png'
set title 'zad2a'
plot 'zad210.dat' u 4:3 w lp, 'zad211.dat' u 4:3 w lp,  'zad212.dat' u 4:3 w lp, 'zad213.dat' u 4:3 w lp

set xlabel 's'
set ylabel 'theta(s)'
set out 'zad2a2.png'
set title 'zad2a'
plot 'zad210.dat' u 1:2 w lp,  'zad211.dat' u 1:2 w lp,  'zad212.dat' u 1:2 w lp, 'zad213.dat' u 1:2 w lp

set xlabel 'x(s)'
set ylabel 'y(s)'
set out 'zad2b.png'
set title 'zad2b'
plot 'zad220.dat' u 4:3 w lp,  'zad221.dat' u 4:3 w lp,  'zad222.dat' u 4:3 w lp, 'zad223.dat' u 4:3 w lp

set xlabel 's'
set ylabel 'theta(s)'
set out 'zad2b2.png'
set title 'zad2b2'
plot 'zad220.dat' u 1:2 w lp,'zad221.dat' u 1:2 w lp,  'zad222.dat' u 1:2 w lp, 'zad223.dat' u 1:2 w lp


