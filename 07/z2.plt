set term pngcairo size 1024,800
set out 'z2.png'
plot 'z2.txt' u 1:2 t 'ro wyliczone' w lp, 'z2.txt' u 1:3 t 'ro ze wzoru' w lp
