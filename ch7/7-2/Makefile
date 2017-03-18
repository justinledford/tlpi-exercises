CC=gcc
CFLAGS=-g

all: test

test: test.o malloc.o error_functions.o
	$(CC) $(CFLAGS) $^ -o $@

test.o: test.c
	$(CC) $(CFLAGS) -c $^

malloc.o: malloc.c
	$(CC) $(CFLAGS) -c $^

error_functions.o: ../../lib/error_functions.c
	$(CC) $(CFLAGS) -c $^

clean:
	rm -rf *.o test
