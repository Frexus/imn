OUT=./z1.out ./z2.out

all: $(OUT) run plot clean_txt

./z1.out: 01.cpp
	g++ 01.cpp -o $@

./z2.out: 02.cpp
	g++ 02.cpp -o $@
run:
	./z1.out
	./z2.out

plot: z1.gp z2.gp z2_2.gp
	gnuplot z1.gp
	gnuplot z2.gp
	gnuplot z2_2.gp

clean_txt:
	rm -f *.txt

clean_all:
	rm -f $(OUT) *.txt *.png
