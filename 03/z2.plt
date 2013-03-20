set term pngcairo size 1024,800
set out 'z2_lin.png'
set multiplot layout 3,1
set title 'funkcja y1'
plot 'z2.txt' u 1:3 t 'Wynik numeryczny', 'z2.txt' u 1:5 t 'Wynik dokładny' w l

set title 'funkcja y2'
plot 'z2.txt' u 1:4 t 'Wynik numeryczny', 'z2.txt' u 1:6 t 'Wynik dokładny' w l

set title 'krok dt'
plot 'z2.txt' u 1:2 t 'dt' w l

unset multiplot

set term pngcairo size 1024,800
set out 'z2_log_krok.png'
set multiplot layout 3,1
set logscale x
set title 'funkcja y1 w skali logarytmicznej'
plot 'z2.txt' u 1:3 t 'Wynik numeryczny', 'z2.txt' u 1:5 t 'Wynik dokładny' w l

set title 'funkcja y2 w skali logarytmicznej'
plot 'z2.txt' u 1:4 t 'Wynik numeryczny', 'z2.txt' u 1:6 t 'Wynik dokładny' w l

unset logscale

set title 'krok dt'
plot 'z2.txt' u 1:2 t 'dt' w l

unset multiplot
print 'Done!'
