set term wxt 0 size 800,1000

set multiplot layout 6,1
set title 'Wykres V(x) dla tolerancji 0.1'
plot 'z2_v_tol1.txt' t 'v(x)' w l

set title 'Wykres V(x) dla tolerancji 0.01'
plot 'z2_v_tol01.txt' t 'v(x)' w l

set title 'Wykres V(x) dla tolerancji 0.001'
plot 'z2_v_tol001.txt' t 'v(x)' w l

set title 'Wykres V(x) dla tolerancji 0.0001'
plot 'z2_v_tol0001.txt' t 'v(x)' w l

set title 'Wykres V(x) dla tolerancji 0.00001'
plot 'z2_v_tol00001.txt' t 'v(x)' w l

set title 'Wykres V(x) dla tolerancji 0.000001'
plot 'z2_v_tol000001.txt' t 'v(x)' w l

unset multiplot

set term wxt 1 size 800,1000

set multiplot layout 6,1
set title 'Wykres energii dla tolerancji 0.1'
plot 'z2_en_tol1.txt' t 'E(x,v)' w l

set title 'Wykres energii dla tolerancji 0.01'
plot 'z2_en_tol01.txt' t 'E(x,v)' w l

set title 'Wykres energii dla tolerancji 0.001'
plot 'z2_en_tol001.txt' t 'E(x,v)' w l

set title 'Wykres energii dla tolerancji 0.0001'
plot 'z2_en_tol0001.txt' t 'E(x,v)' w l

set title 'Wykres energii dla tolerancji 0.00001'
plot 'z2_en_tol00001.txt' t 'E(x,v)' w l

set title 'Wykres energii dla tolerancji 0.000001'
plot 'z2_en_tol000001.txt' t 'E(x,v)' w l

unset multiplot
pause -1
