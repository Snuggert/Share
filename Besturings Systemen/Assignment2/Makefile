CC=gcc
CFLAGS=-Wall -std=c99 -pedantic -lm -ggdb -D_GNU_SOURCE

%.o: %.c
	$(CC) $(CFLAGS) $< -c -o $@

scheduler: scheduler.c mt19937ar.o simul.o mem_alloc.o pcb.o
	$(CC) $^ $(CFLAGS) -o $@

all: sas

clean:
	rm -f *.o

run: scheduler
	./scheduler