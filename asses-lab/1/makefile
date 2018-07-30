all: listing.o dump.o misc.o calc.o main.o
	cc -o shell listing.o dump.o misc.o calc.o main.o

listing.o: listing.c
	cc -c listing.c

dump.o: dump.c
	cc -c dump.c

misc.o: misc.c
	cc -c misc.c

calc.o: calc.c
	cc -c calc.c

main.o: main.c
	cc -c main.c

clean:
	rm -rf listing.o dump.o misc.o calc.o main.o shell

