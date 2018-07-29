all: main.o getting_time.o
	cc -o getting_time main.o getting_time.o -g

main.o: main.c getting_time.h
	cc -c main.c -g

getting_time.o: getting_time.c getting_time.h
	cc -c getting_time.c -g

clean:
	rm -rf main.o getting_time.o getting_time 
