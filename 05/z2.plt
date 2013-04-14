set term pngcairo size 1024,800
set out 'z2e13.png'

set title 'Zadanie 2'
set multiplot layout 2,1
plot 'z2e13.txt' u 1:2 t 'rozw. numeryczne' w linespoints, 'z2e13.txt' u 1:3 t 'analityczne' w l
plot 'z2e13.txt' u 1:4 t 'blad globalny' w linespoints
unset multiplot

print 'Done!'
