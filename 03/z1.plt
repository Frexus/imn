set term wxt 0 size 1024,800
set multiplot layout 4,1
set title 'funkcja y1 RK4'
plot 'z1.txt' u 1:3 t 'Wynik numeryczny' w l, 'z1.txt' u 1:5 t 'Wynik dokładny' w l

set title 'funkcja y2 RK4'
plot 'z1.txt' u 1:4 t 'Wynik numeryczny' w l, 'z1.txt' u 1:6 t 'Wynik dokładny' w l

set title 'funkcja y1 RK2'
plot 'z1_rk2.txt' u 1:3 t 'Wynik numeryczny' w l, 'z1_rk2.txt' u 1:5 t 'Wynik dokładny' w l

set title 'funkcja y2 RK2'
plot 'z1_rk2.txt' u 1:4 t 'Wynik numeryczny' w l, 'z1_rk2.txt' u 1:6 t 'Wynik dokładny' w l
unset multiplot

set term wxt 1 size 1024,800
set logscale x
set multiplot layout 4,1
set title 'funkcja y1 (skala logarytmiczna) RK4'
plot 'z1.txt' u 1:3 t 'Wynik numeryczny' w l, 'z1.txt' u 1:5 t 'Wynik dokładny' w l

set title 'funkcja y2 (skala logarytmiczna) RK4'
plot 'z1.txt' u 1:4 t 'Wynik numeryczny' w l, 'z1.txt' u 1:6 t 'Wynik dokładny' w l

set title 'funkcja y1 (skala logarytmiczna) RK2'
plot 'z1_rk2.txt' u 1:3 t 'Wynik numeryczny' w l, 'z1_rk2.txt' u 1:5 t 'Wynik dokładny' w l

set title 'funkcja y2 (skala logarytmiczna) RK2'
plot 'z1_rk2.txt' u 1:4 t 'Wynik numeryczny' w l, 'z1_rk2.txt' u 1:6 t 'Wynik dokładny' w l
unset multiplot

unset logscale
set term wxt 2 size 1024,800
set multiplot layout 2,1
set title 'wykres kroku czasowego dt w zaleznosci od czasu RK4'
plot 'z1.txt' u 1:2 t 'dt(t)' w l

set title 'wykres kroku czasowego dt w zaleznosci od czasu RK2'
plot 'z1_rk2.txt' u 1:2 t 'dt(t)' w l
unset multiplot

set term wxt 3 size 1024,800
set multiplot layout 2,1
set title 'Wykres funcji y1,y2 dla RK2 z dt zafiksowanym dla T>5000'
plot 'z1_1.txt' u 1:3 t 'Wynik numeryczny y1' w l, 'z1_1.txt' u 1:5 t 'Wynik dokładny y1' w l
plot 'z1_1.txt' u 1:4 t 'Wynik numeryczny y2' w l, 'z1_1.txt' u 1:6 t 'Wynik dokładny y2' w l
unset multiplot

pause -1
