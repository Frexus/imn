# 408dfcac53577872ad3a7cae511d30dd
CFLAGS=-O$(O) 
O=2
LFLAGS=
OBJS=objs/nrutil.o objs/01.o


.PHONY: all
all: objs a.out

./a.out: $(OBJS)
	@ echo "    LINK ./a.out"
	@ $(CXX) $(OBJS) -o "./a.out" $(LFLAGS)

objs/nrutil.o: nrutil.c
	@ echo "    CC   ./nrutil.c"
	@ $(CC) $(CFLAGS) -c "./nrutil.c" -o $@
objs/01.o: 01.cpp nrutil.h
	@ echo "    CXX  ./01.cpp"
	@ $(CXX) $(CFLAGS) -c "./01.cpp" -o $@

objs:
	@ mkdir "objs"
.PHONY: c clean
c: clean
clean:
	@ if [ -d "objs" ]; then rm -r "objs"; fi
	@ rm -f "./a.out"
	@ echo "    CLEAN"
.PHONY: f fresh
f: fresh
fresh: clean
	@ make all --no-print-directory
.PHONY: r run
r: run
run: all
	@ ././a.out

.PHONY: d debug
d: debug
debug: CFLAGS += -DDEBUG -g3 -Wall -Wextra
debug: O=0
debug: all

.PHONY: check-syntax
check-syntax:
	$(CXX) $(CFLAGS) -fsyntax-only -Wall -o /dev/null -S $(CHK_SOURCES)
