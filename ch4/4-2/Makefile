CC=gcc
CFLAGS=

all: copy-holes

copy-holes: copy-holes.o error_functions.o
	$(CC) $(CFLAGS) $^ -o $@

copy-holes.o: copy-holes.c
	$(CC) $(CFLAGS) -c $^

error_functions.o: ../../lib/error_functions.c
	$(CC) $(CFLAGS) -c $^

clean:
	rm -rf copy-holes *.o
