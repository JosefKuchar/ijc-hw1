#include <stdio.h>
#include "bitset.h"
#include "eratosthenes.h"
#include "time.h"

#define MAX 300000000
#define LAST_COUNT 10

int main() {
    // Record start time
    clock_t start = clock();
    // Allocate bitset
    bitset_alloc(bitset, MAX);
    // Calculate prime numbers
    Eratosthenes(bitset);
    // Retrieve largest numbers
    bitset_index_t largest[LAST_COUNT];
    for (bitset_index_t i = MAX - 1, n = 0; n < 10; i--) {
        if (bitset_getbit(bitset, i) == 0) {
            largest[n++] = i;
        }
    }
    // Print primes
    for (int i = LAST_COUNT - 1; i >= 0; i--) {
        printf("%ld\n", largest[i]);
    }
    // Print time
    fprintf(stderr, "Time=%.3g\n", (double)(clock() - start) / CLOCKS_PER_SEC);
    return 0;
}
