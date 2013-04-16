zad1: z1.cpp
	g++ z1.cpp -o z1

zad2: nrutil gaussj z2.cpp
	g++ nrutil.o gaussj.o z2.cpp -o z2

gaussj: gaussj.c
	g++ -c gaussj.c -o gaussj.o

nrutil: nrutil.c
	g++ -c nrutil.c -o nrutil.o
