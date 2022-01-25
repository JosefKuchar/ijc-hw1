eratosthenes.o: eratosthenes.c eratosthenes.h bitset.h
primes.o: primes.c bitset.h eratosthenes.h

primes: primes.o eratosthenes.o
