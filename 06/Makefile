all: zad1 zad2 runz1 runz2 plot

zad1: z1.cpp
	g++ z1.cpp -o z1

zad2: nrutil gaussj z2.cpp
	g++ nrutil.o gaussj.o z2.cpp -o z2
	
runz1: zad1
	./z1

runz2: zad2
	./z2

plot:
	gnuplot z1.plt
	gnuplot z2.plt

gaussj: gaussj.c
	g++ -c gaussj.c -o gaussj.o

nrutil: nrutil.c
	g++ -c nrutil.c -o nrutil.o
