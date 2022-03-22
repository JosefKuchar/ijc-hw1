// eratosthenes.c
// Řešení IJC-DU1, příklad a), 22.3.2022
// Autor: Josef Kuchař, FIT
// Přeloženo: gcc 9.3.0

#include "eratosthenes.h"
#include <math.h>
#include <stdio.h>
#include "bitset.h"

// Calculate prime numbers
void Eratosthenes(bitset_t bitset) {
    // Retrieve the size of the bitset
    bitset_index_t size = bitset_size(bitset);

    // Calculate end of the calculation
    // +1 just to be sure because of rounding down
    bitset_index_t end = sqrt(size) + 1;

    // 0 and 1 are not primes
    bitset_setbit(bitset, 0, 1);
    bitset_setbit(bitset, 1, 1);

    for (bitset_index_t i = 2; i < end; i++) {
        if (bitset_getbit(bitset, i) == 0) {
            for (bitset_index_t n = 2 * i; n < size; n += i) {
                bitset_setbit(bitset, n, 1);
            }
        }
    }
}
