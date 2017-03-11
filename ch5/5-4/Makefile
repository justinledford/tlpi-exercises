CC=gcc
CFLAGS=

all: dups

dups: dups.o error_functions.o
	$(CC) $(CFLAGS) $^ -o $@

dups.o: dups.c
	$(CC) $(CFLAGS) -c $^

error_functions.o: ../../lib/error_functions.c
	$(CC) $(CFLAGS) -c $^

clean:
	rm -rf dups *.o
