set term pngcairo size 800,800
set out "z1_1.png"
set size square
plot 'z1_pot.txt' matrix w image
unset size
set out "z1_2.png"
set logscale x
plot 'z1_a.txt' t "calka" w lp
