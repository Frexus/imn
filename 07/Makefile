all: zad run plot

zad: zad1 zad2 zad3

plot: plot1 plot2 plot3

run: run1 run2 run3

zad1: z1.cpp
	g++ z1.cpp -o z1
	
zad2: z2.cpp
	g++ z2.cpp -o z2
	
zad3: z3.cpp
	g++ z3.cpp -o z3
	
plot1: z1.plt
	gnuplot z1.plt

plot2: z2.plt
	gnuplot z2.plt

plot3: z3.plt
	gnuplot z3.plt

run1: zad1
	./z1

run2: zad2
	./z2

run3: zad3
	./z3
