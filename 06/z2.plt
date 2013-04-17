set term pngcairo size 1024,800
set out "zad2a_th.png"
set title "Wykres theta dla th = random"
plot for [i=0:2] sprintf("zad2a_it%d.txt", i) u 1:3 t sprintf("Iteracja %d", i) w lp

set out "zad2a_xy.png"
set title "Wykres xy dla th = random"
plot for [i=0:2] sprintf("zad2a_it%d.txt", i) u 2:4 t sprintf("Iteracja %d", i) w lp

set out "zad2b_th.png"
set title "Wykres theta dla th zaleznego od s"
plot for [i=0:2] sprintf("zad2b_it%d.txt", i) u 1:3 t sprintf("Iteracja %d", i) w lp

set out "zad2b_xy.png"
set title "Wykres xy dla th zaleznego od s"
plot for [i=0:2] sprintf("zad2b_it%d.txt", i) u 2:4 t sprintf("Iteracja %d", i) w lp
