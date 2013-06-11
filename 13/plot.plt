set term pngcairo enhanced size 1920,1080
set out 'z1.png'
files = "z10.25.dat z10.50.dat z10.75.dat z11.00.dat z11.25.dat z11.50.dat z11.75.dat z12.00.dat"
plot for [i in files] i w lp t i

set out 'z1_porownanie.png'
set yrange [-1:1]
plot 'z10.25.dat' t "obliczone" w lp, 'z10.25_a.dat' t "analityczne" w lp
set autoscale y

set out 'z2.png'
set pm3d map
set palette defined (0 "blue", 1 "white", 2 "red")
splot 'z2.dat' w pm3d

set out 'z2b.png'
set cbrange [-1:1]
splot 'z2b.dat' w pm3d

set out 'z3b0.2.png'
splot 'z3b0.20.dat' w pm3d

set out 'z3b1.00.png'
splot 'z3b1.00.dat' w pm3d

set out 'z3b4.00.png'
splot 'z3b4.00.dat' w pm3d

set out 'z4.png'
set autoscale cb
splot 'z4.dat' w pm3d
