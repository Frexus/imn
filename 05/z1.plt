set term pngcairo size 1024,800
set out 'z1e13.png'

set title 'Zadanie 1 Dokladnosc 10e-13'
set multiplot layout 2,1
plot 'z1e13.txt' u 1:2 t 'rozw. numeryczne' w linespoints, 'z1e13.txt' u 1:3 t 'analityczne' w l
plot 'z1e13.txt' u 1:4 t 'blad globalny' w linespoints
unset multiplot

set term pngcairo size 1024,800
set out 'z1e7.png'

set title 'Zadanie 1 Dokladnosc 10e-7'
set multiplot layout 1,1
plot 'z1e7.txt' u 1:2 t 'rozw. numeryczne' w linespoints, 'z1e7.txt' u 1:3 t 'analityczne' w l
unset multiplot

set term pngcairo size 1024,800
set out 'z1e5.png'

set title 'Zadanie 1 Dokladnosc 10e-5'
set multiplot layout 1,1
plot 'z1e5.txt' u 1:2 t 'rozw. numeryczne' w linespoints, 'z1e5.txt' u 1:3 t 'analityczne' w l
unset multiplot

print 'Done!'
