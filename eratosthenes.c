#include "eratosthenes.h"
#include <math.h>
#include <stdio.h>
#include "bitset.h"

// Calculate prime numbers
void Eratosthenes(bitset_t bitset) {
    // Retrieve the size of the bitset
    bitset_index_t size = bitset_size(bitset);

    // Calculate end of the calculation
    bitset_index_t end = sqrt(size) + 2;

    // 0 and 1 are not primes
    bitset_setbit(bitset, 0, 1);
    bitset_setbit(bitset, 1, 1);

    for (bitset_index_t i = 2; i < end; i++) {
        // Skip non prime numbers
        if (bitset_getbit(bitset, i) == 0) {
            for (bitset_index_t n = 2 * i; n < size; n += i) {
                bitset_setbit(bitset, n, 1);
            }
        }
    }
}
