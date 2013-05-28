set term pngcairo size 1500,1500

zad(n,i)=sprintf("Zadanie%d: po %d iteracji", n, i)

set out 'z1_calka.png'
plot 'z1i.dat' t "Zadanie1: Calka"

set out 'z1_srodek.png'
plot 'z1srodek.dat' t "Zadanie1: Srodek"

set out 'z2_calka.png'
plot 'z2i.dat' t "Zadanie2: Calka"

set out 'z2_srodek.png'
plot 'z2srodek.dat' t "Zadanie2: Srodek"

set pm3d map

set out 'z3u0.png'
splot 'z3u0.dat' t zad(3,1);

set out 'z3u1512.png'
splot 'z3u1512.dat' t zad(3,1512);

set out 'z3u2520.png'
splot 'z3u2520.dat' t zad(3,2520);

set out 'z3u10000.png'
splot 'z3u10000.dat' t zad(3,10000);

set out 'z3u6000.png'
splot 'z3u6000.dat' t zad(3,6000);

set cbrange [0:1]
set out 'z1u0.png'
splot 'z1u0.dat' t zad(1,1)

set out 'z1u200.png' 
splot 'z1u200.dat' t zad(1,200)

set out 'z1u320.png' 
splot 'z1u320.dat' t zad(1,320)

set out 'z1u600.png'
splot 'z1u600.dat' t zad(1,600)

set out 'z1u3201.png'
splot 'z1u3201.dat' t zad(1,3201)

set out 'z2u0.png'
splot 'z2u0.dat' t zad(2,1)

set out 'z2u200.png' 
splot 'z2u200.dat' t zad(2,200)

set out 'z2u320.png' 
splot 'z2u320.dat' t zad(2,320)

set out 'z2u600.png'
splot 'z2u600.dat' t zad(2,600)

set out 'z2u1300.png'
splot 'z2u1300.dat' t zad(2,1300)