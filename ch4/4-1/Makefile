CC=gcc

all: tee

tee: tee.o error_functions.o
	$(CC) $^ -o $@

tee.o: tee.c
	$(CC) -c $^

error_functions.o: ../../lib/error_functions.c
	$(CC) -c $^

clean:
	rm -rf tee *.o
