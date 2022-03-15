# Makefile
# Řešení IJC-DU1, TBD
# Autor: Josef Kuchař, FIT
# Přeloženo: gcc 9.3.0

CC = gcc
CFLAGS = -O2 -g -std=c11 -pedantic -Wall -Wextra

.PHONY: all run clean pack

all: primes primes-i steg-decode

error.o: error.c error.h
eratosthenes.o: eratosthenes.c eratosthenes.h bitset.h error.h
primes.o: primes.c eratosthenes.o
ppm.o: ppm.c ppm.h

primes: primes.o eratosthenes.o error.o
	$(CC) $(CFLAGS) $^ -o $@ -lm

primes-i: primes.o eratosthenes.o error.o
	$(CC) -DUSE_INLINE $(CFLAGS) $^ -o $@ -lm

steg-decode: steg-decode.c ppm.o error.o eratosthenes.o
	$(CC) $(CFLAGS) $^ -o $@ -lm

run: primes primes-i
	./primes
	./primes-i

clean:
	rm -f *.o *.out *.zip primes primes-i steg-decode

pack:
	zip xkucha28.zip *.c *.h Makefile
