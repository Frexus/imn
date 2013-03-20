set term pngcairo size 1024,800
set out 'z3_jaw.png'
set multiplot layout 3,2
set title 'tol = 0.01'
plot 'z3_euj_01.txt' u 1:3 t 'numeryczne', sin(x) t 'dokladne'
plot 'z3_euj_01.txt' u 1:2 t 'dt' w l

set title 'tol = 0.001'
plot 'z3_euj_001.txt' u 1:3 t 'numeryczne', sin(x) t 'dokladne'
plot 'z3_euj_001.txt' u 1:2 t 'dt' w l

set title 'tol = 0.0001'
plot 'z3_euj_0001.txt' u 1:3 t 'numeryczne', sin(x) t 'dokladne'
plot 'z3_euj_0001.txt' u 1:2 t 'dt' w l

unset multiplot

set term pngcairo size 1024,800
set out 'z3_njaw.png'
set multiplot layout 3,2
set title 'tol = 0.01'
plot 'z3_eunj_01.txt' u 1:3 t 'numeryczne', sin(x) t 'dokladne'
plot 'z3_eunj_01.txt' u 1:2 t 'dt' w l

set title 'tol = 0.001'
plot 'z3_eunj_001.txt' u 1:3 t 'numeryczne', sin(x) t 'dokladne'
plot 'z3_eunj_001.txt' u 1:2 t 'dt' w l

set title 'tol = 0.0001'
plot 'z3_eunj_0001.txt' u 1:3 t 'numeryczne', sin(x) t 'dokladne'
plot 'z3_eunj_0001.txt' u 1:2 t 'dt' w l

unset multiplot

print 'Done!'
