CC=gcc
CFLAGS=

all: atomic_append

atomic_append: atomic_append.o error_functions.o get_num.o
	$(CC) $(CFLAGS) $^ -o $@

atomic_append.o: atomic_append.c
	$(CC) $(CFLAGS) -c $^

error_functions.o: ../../lib/error_functions.c
	$(CC) $(CFLAGS) -c $^

get_num.o: ../../lib/get_num.c
	$(CC) $(CFLAGS) -c $^


clean:
	rm -rf atomic_append *.o
