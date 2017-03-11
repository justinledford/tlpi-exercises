CC=gcc
CFLAGS=

all: ex5-2

ex5-2: ex5-2.o error_functions.o
	$(CC) $(CFLAGS) $^ -o $@

ex5-2.o: ex5-2.c
	$(CC) $(CFLAGS) -c $^

error_functions.o: ../../lib/error_functions.c
	$(CC) $(CFLAGS) -c $^

clean:
	rm -rf ex5-2 *.o
