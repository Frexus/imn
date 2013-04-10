#! /usr/bin/env gnuplot
set term png


set output "zad1_e-7.png"
set grid
set xlabel "r"
set ylabel "f(r)"
plot "zad1_e-7.dat" u 1:2 w lp title "f(r) numerycznie", "zad1_e-7.dat" u 1:3 w lp title "f(r) analitycznie"

set output "zad1_e-5.png"
set grid
set xlabel "r"
set ylabel "f(r)"
plot "zad1_e-5.dat" u 1:2 w lp title "f(r) numerycznie", "zad1_e-5.dat" u 1:3 w lp title "f(r) analitycznie"

set output "zad1_e-13.png"
set grid
set xlabel "r"
set ylabel "f(r)"
plot "zad1_e-13.dat" u 1:2 w lp title "f(r) numerycznie", "zad1_e-13.dat" u 1:3 w lp title "f(r) analitycznie"

set output "zad1_e-13_err.png"
set grid
set xlabel "r"
set ylabel "e(r)"
plot "zad1_e-13.dat" u 1:4 w lp title "blad globalny"

set output "zad2_err.png"
set grid
set xlabel "r"
set ylabel "e(r)"
plot "zad2.dat" u 1:4 w lp title "blad globalny"

set output "zad3_1_err.png"
set grid
set xlabel "r"
set ylabel "e(r)"
plot "zad3_1.dat" u 1:4 w lp title "blad globalny"

set output "zad3_2_err.png"
set grid
set xlabel "r"
set ylabel "e(r)"
plot "zad3_2.dat" u 1:4 w lp title "blad globalny"


set output "zad3_3_err.png"
set grid
set xlabel "r"
set ylabel "e(r)"
plot "zad3_3.dat" u 1:4 w lp title "blad globalny"

set output "zad4_err.png"
set grid
set xlabel "r"
set ylabel "e(r)"
plot "zad4.dat" u 1:4 w lp title "blad globalny"

set output "zad5_1_err.png"
set grid
set xlabel "r"
set ylabel "e(r)"
plot "zad5_1.dat" u 1:4 w lp title "blad globalny"

set output "zad5_2_err.png"
set grid
set xlabel "r"
set ylabel "e(r)"
plot "zad5_2.dat" u 1:4 w lp title "blad globalny"


set output "zad5_3_err.png"
set grid
set xlabel "r"
set ylabel "e(r)"
plot "zad5_3.dat" u 1:4 w lp title "blad globalny"

set output "zad6.png"
set grid
set xlabel "r"
set ylabel "f(r)"
plot "zad6.dat" u 1:2 w lp title "f(r) numerycznie", "zad6.dat" u 1:4 w lp title "f(r) analitycznie"

set output "zad6_err.png"
set grid
set xlabel "r"
set ylabel "e(r)"
plot "zad6.dat" u 1:5 w lp title "blad globalny"
