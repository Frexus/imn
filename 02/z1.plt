set term wxt size 800,600
set multiplot layout 2,1
set title 'Bledy globalne metod numerycznych'
plot 'z1_eu_err.txt' title 'metoda eulera' w l, 'z1_rk2_err.txt' title 'metoda RK2' w l
set title 'Blady globalne metod numerycznych po ekstrapolacji Richardsona
plot 'z1_rich_eu_err.txt' title 'metoda eulera' w l, 'z1_rich_rk2_err.txt' title 'metoda RK2' w l
unset multiplot
pause -1
