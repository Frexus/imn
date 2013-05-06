set term pngcairo size 1024,800
set out 'z3.png'
set logscale x
plot for [i in "0.50 0.60 0.70 0.80 0.90 1.00"] sprintf("z3_w%s.txt", i) t sprintf("w=%s", i) w l

set out 'z3_porownanie.png'
plot 'z3_w1.00.txt' t 'relaksacja globalna' w l, 'z1_w1.95.txt' t 'punktowa nadrelaksacja' w l
