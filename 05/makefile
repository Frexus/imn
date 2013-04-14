all: zad plot

zad: zad1 zad2 zad3 zad4 zad5 zad6

plot: plot1 plot2 plot3 plot4 plot5 plot6

zad1: z1.cpp
	g++ z1.cpp -o z1
	./z1
	
zad2: z2.cpp
	g++ z2.cpp -o z2
	./z2

zad3: z3.cpp
	g++ z3.cpp -o z3
	./z3
	
zad4: z4.cpp
	g++ z4.cpp -o z4
	./z4
	
zad5: z5.cpp
	g++ z5.cpp -o z5
	./z5

zad6: z6.cpp
	g++ z6.cpp -o z6
	./z6
			
plot1: zad1
	gnuplot z1.plt
	
plot2: zad2
	gnuplot z2.plt

plot3: zad3
	gnuplot z3.plt

plot4: zad4
	gnuplot z4.plt

plot5: zad5
	gnuplot z5.plt

plot6: zad6
	gnuplot z6.plt

clean:
	rm -f *.txt *.png z1 z2 z3 z4 z5 z6 2> /dev/null
