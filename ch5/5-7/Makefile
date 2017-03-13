CC=gcc
CFLAGS=

all: scattergather

scattergather: scattergather.o error_functions.o
	$(CC) $(CFLAGS) $^ -o $@

scattergather.o: scattergather.c
	$(CC) $(CFLAGS) -c $^

error_functions.o: ../../lib/error_functions.c
	$(CC) $(CFLAGS) -c $^

clean:
	rm -rf scattergather *.o
