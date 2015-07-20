all: traverse

run: traverse
	./traverse

traverse: traverse.o
	gcc traverse.o -o traverse

traverse.o : traverse.c
	gcc -c traverse.c

clean:
	rm -f traverse.o traverse
