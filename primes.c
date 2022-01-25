#include <stdio.h>
#include "bitset.h"
#include "eratosthenes.h"

#define MAX 200000000
#define LAST_COUNT 10

int main() {
    // Allocate bitset
    bitset_alloc(bitset, MAX);
    // Calculate prime numbers
    Eratosthenes(bitset);
    // Get 10 largest numbers
    bitset_index_t largest[LAST_COUNT];
    for (bitset_index_t i = MAX - 1, n = 0; n < 10; i--) {
        if (bitset_getbit(bitset, i) == 0) {
            largest[n++] = i;
        }
    }
    // Print numbers
    for (int i = LAST_COUNT - 1; i >= 0; i--) {
        printf("%ld\n", largest[i]);
    }
    return 0;
}
