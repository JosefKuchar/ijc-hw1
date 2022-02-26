# Makefile
# Řešení IJC-DU1, TBD
# Autor: Josef Kuchař, FIT
# Přeloženo: gcc 9.3.0

CC = gcc
CFLAGS = -O2 -g -std=c11 -pedantic -Wall -Wextra

.PHONY: all run clean pack

all: primes primes-i steg-decode

eratosthenes.o: eratosthenes.c eratosthenes.h bitset.h
primes.o: primes.c bitset.h eratosthenes.h
error.o: error.c error.h
ppm.o: ppm.c ppm.h error.o

primes: primes.o eratosthenes.o
	$(CC) $(CFLAGS) $^ -o $@ -lm

primes-i: primes.o eratosthenes.o
	$(CC) -DUSE_INLINE $(CFLAGS) $^ -o $@ -lm

steg-decode: steg-decode.c ppm.o error.o eratosthenes.o
	$(CC) $(CFLAGS) $^ -o $@ -lm

run: all
	./primes
	./primes-i

clean:
	rm -f *.o *.out *.zip primes primes-i steg-decode

pack:
	zip xkucha28.zip *.c *.h Makefile
