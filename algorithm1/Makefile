test: test.o spritz.o
	gcc -o test test.o spritz.o

test.o: test.c
	gcc -c test.c

spritz.o: spritz.c spritz.h
	gcc -c spritz.c

clean:
	rm test.o spritz.o test
