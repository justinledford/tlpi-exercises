CC=gcc
CFLAGS=-g

all: env

env: env.o error_functions.o
	$(CC) $(CFLAGS) $^ -o $@

env.o: env.c
	$(CC) $(CFLAGS) -c $^

error_functions.o: ../../lib/error_functions.c
	$(CC) $(CFLAGS) -c $^

clean:
	rm -rf env *.o
