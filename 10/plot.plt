set border 0
set xzeroaxis lc 'black'
set yzeroaxis lc 'black'

set terminal png size 1600,800

set out 'z1e0.png'
plot 'z1e.dat' u 1:2 t "x=0 obliczone", 'z1e_a.dat' u 1:2 t "x=0 analityczne"

set out 'z1e7.png'
plot 'z1e.dat' u 1:3 t "x=0.7 obliczone", 'z1e_a.dat' u 1:3 t "x=0.7 analityczne"

set out 'z1p0.png'
plot 'z1p.dat' u 1:2 t "x=0 obliczone", 'z1p_a.dat' u 1:2 t "x=0 analityczne"

set out 'z1p7.png'
plot 'z1p.dat' u 1:3 t "x=0.7 obliczone", 'z1p_a.dat' u 1:3 t "x=0.7 analityczne"

set out 'z1u.png'
plot 'z1u.dat' u 1:2 t 'u analityczne', 'z1u.dat' u 1:3 t 'u obliczone'

set pm3d map
set palette defined (-1 "blue", 0 "white", 1 "red")
set xlabel 'x'
set ylabel 'y'
set contour both
unset surface

set out 'z2p-1.png'
splot 'z2p-1.dat' w pm3d 

set out 'z2p-100.png'
splot 'z2p-100.dat' w pm3d 

set out 'z2p-200.png'
splot 'z2p-200.dat' w pm3d 

set out 'z2p-350.png'
splot 'z2p-350.dat' w pm3d 

set out 'z2p-500.png'
splot 'z2p-500.dat' w pm3d 
