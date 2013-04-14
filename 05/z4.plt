set term pngcairo size 1024,800
set out 'z4.png'

set title 'Zadanie 4'
set multiplot layout 1,1
plot 'z4.txt' u 1:4 t 'blad globalny' w linespoints
unset multiplot

print 'Done!'
