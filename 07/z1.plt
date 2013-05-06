set term pngcairo size 1024,800
set out 'z1.png'
set logscale x
plot 'z1_w0.50.txt' t 'w=0.5' w l, 'z1_w0.75.txt' t 'w=0.75' w l, 'z1_w0.90.txt' t 'w=0.9' w l, 'z1_w1.00.txt' t 'w=1.0' w l, 'z1_w1.25.txt' t 'w=1.25' w l, 'z1_w1.50.txt' t 'w=1.5' w l, 'z1_w1.90.txt' t 'w=1.9'w l, 'z1_w1.95.txt' t 'w=1.95' w l, 'z1_w1.99.txt' t 'w=1.99' w l

set out 'z1_map.png'
set pm3d map
unset logscale x
splot 'z1_map.txt' matrix
