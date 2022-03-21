# Makefile
# Řešení IJC-DU1, 21.3.2022
# Autor: Josef Kuchař, FIT
# Přeloženo: gcc 9.3.0

CC = gcc
CFLAGS = -O2 -g -std=c11 -pedantic -Wall -Wextra
LDLIBS = -lm

.PHONY: all run clean pack

all: primes primes-i steg-decode

# Normal
eratosthenes.o: eratosthenes.c eratosthenes.h bitset.h error.h
error.o: error.c error.h
ppm.o: ppm.c ppm.h error.h
primes.o: primes.c bitset.h error.h eratosthenes.h
steg-decode.o: steg-decode.c bitset.h error.h eratosthenes.h ppm.h
bitset.o: bitset.c bitset.h error.h

# Inline
primes-i.o: primes.c eratosthenes.h bitset.h error.h
	$(CC) $(CFLAGS) -DUSE_INLINE -c primes.c -o primes-i.o
eratosthenes-i.o: eratosthenes.c eratosthenes.h bitset.h error.h
	$(CC) $(CFLAGS) -DUSE_INLINE -c eratosthenes.c -o eratosthenes-i.o
bitset-i.o: bitset.c bitset.h error.h
	$(CC) $(CFLAGS) -DUSE_INLINE -c bitset.c -o bitset-i.o

# Final executables
primes: primes.o eratosthenes.o error.o bitset.o
	$(CC) $(CFLAGS) $^ -o $@ $(LDLIBS)

primes-i: primes-i.o eratosthenes-i.o error.o bitset-i.o
	$(CC) -DUSE_INLINE $(CFLAGS) $^ -o $@ $(LDLIBS)

steg-decode: steg-decode.o ppm.o error.o eratosthenes.o bitset.o
	$(CC) $(CFLAGS) $^ -o $@ $(LDLIBS)

# Other
run: primes primes-i
	./primes
	./primes-i

clean:
	rm -f *.o *.out *.zip primes primes-i steg-decode

pack: all
	zip xkucha28.zip *.c *.h Makefile
