CC=gcc
CFLAGS=-O2 -Wall -ansi -pedantic -lm -ggdb -D_GNU_SOURCE

%.o: %.c
	$(CC) $(CFLAGS) $< -c -o $@

next-fit: next-fit.c address.o mem_test2-64.o
	$(CC) $^ $(CFLAGS) -o $@

best-fit: best-fit.c address.o mem_test2-64.o
	$(CC) $^ $(CFLAGS) -o $@

all: next-fit best-fit

clean:
	rm -f next-fit.o

run: best-fit
	./best-fit
