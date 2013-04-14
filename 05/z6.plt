set term pngcairo size 1024,800
set out 'z6.png'

set title 'Zadanie 6'
set multiplot layout 1,1
plot 'z6.txt' u 1:5 t 'blad globalny' w linespoints
unset multiplot

print 'Done!'
