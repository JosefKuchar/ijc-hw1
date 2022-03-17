# Makefile
# Řešení IJC-DU1, 20.3.2111
# Autor: Josef Kuchař, FIT
# Přeloženo: gcc 9.3.0

CC = gcc
CFLAGS = -O2 -g -std=c11 -pedantic -Wall -Wextra
LDLIBS = -lm

.PHONY: all run clean pack

all: primes primes-i steg-decode

eratosthenes.o: eratosthenes.c eratosthenes.h bitset.h error.h
error.o: error.c error.h
ppm.o: ppm.c ppm.h error.h
primes.o: primes.c bitset.h error.h eratosthenes.h
steg-decode.o: steg-decode.c bitset.h error.h eratosthenes.h ppm.h

primes: primes.o eratosthenes.o error.o
	$(CC) $(CFLAGS) $^ -o $@ $(LDLIBS)

primes-i: primes.o eratosthenes.o error.o
	$(CC) -DUSE_INLINE $(CFLAGS) $^ -o $@ $(LDLIBS)

steg-decode: steg-decode.o ppm.o error.o eratosthenes.o
	$(CC) $(CFLAGS) $^ -o $@ $(LDLIBS)

run: primes primes-i
	./primes
	./primes-i

clean:
	rm -f *.o *.out *.zip primes primes-i steg-decode

pack: all
	zip xkucha28.zip *.c *.h Makefile
