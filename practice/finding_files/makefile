CC=i686-win64-mingw32-gcc

out: main.o stuff.o
	cc -o out main.o stuff.o

main.o: main.c stuff.h
	cc -c main.c

stuff.o: stuff.c stuff.h
	cc -c stuff.c

clean:
	rm out main.o stuff.o
