set terminal pngcairo size 800,800
set out "z2_map.png"
set pm3d map
set size square
set multiplot layout 3,2
filename(k)=sprintf("z2_k%d.txt", k)
plot filename(32) matrix w image t "k=32" 
plot filename(16) matrix w image t "k=16" 
plot filename(8) matrix w image t "k=8" 
plot filename(4) matrix w image t "k=4" 
plot filename(2) matrix w image t "k=2" 
plot filename(1) matrix w image t "k=1" 
unset multiplot

