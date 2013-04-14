set term pngcairo size 1024,800
set out 'z5.png'

set title 'Zadanie 5'
set multiplot layout 3,1
plot 'z5_1.txt' u 1:4 t 'blad globalny dt=0.1, f1 = analitycznie' w linespoints
plot 'z5_2.txt' u 1:4 t 'blad globalny dt=0.01, f1 = analitycznie' w linespoints
plot 'z5_3.txt' u 1:4 t 'blad globalny dt=0.1, f1 z zadania 1' w linespoints
unset multiplot

print 'Done!'
