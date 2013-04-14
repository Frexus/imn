set term pngcairo size 1024,800
set out 'z3.png'

set title 'Zadanie 3'
set multiplot layout 3,1
plot 'z3_1.txt' u 1:4 t 'blad globalny dt=0.1, f1 = analitycznie' w linespoints
plot 'z3_2.txt' u 1:4 t 'blad globalny dt=0.01, f1 = analitycznie' w linespoints
plot 'z3_3.txt' u 1:4 t 'blad globalny dt=0.1, f1 z zadania 1' w linespoints
unset multiplot

print 'Done!'
