#include <stdbool.h>
#include <stdio.h>
#include "bitset.h"
#include "eratosthenes.h"
#include "error.h"
#include "ppm.h"

#define PRIME_START 23

int main(int argc, char* argv[]) {
    if (argc != 2) {
        error_exit("You have to supply path to input image!\n");
    }

    struct ppm* ppm = ppm_read(argv[1]);

    if (ppm == NULL) {
        error_exit("ppm_read: Error reading\n");
    }

    const bitset_index_t size = ppm->xsize * ppm->ysize * 3;
    bitset_alloc(bitset, size);

    // Calculate primes
    Eratosthenes(bitset);

    char current_c = 0;
    int index = 0;
    bool end = false;

    // Search for primes in bitset
    for (int i = PRIME_START; i < size; i++) {
        // Prime found
        if (bitset_getbit(bitset, i) == 0) {
            // Construct byte bit by bit
            current_c |= (ppm->data[i] & 1) << index;
            index++;
            // We have whole byte
            if (index == 8) {
                // String end
                if (current_c == '\0') {
                    end = true;
                    break;
                }
                // Print decoded byte
                putc(current_c, stdout);

                index = 0;
                current_c = 0;
            }
        }
    }

    if (!end) {
        error_exit("String end \"\\0\" not found!");
    }

    bitset_free(bitset);
    ppm_free(ppm);
    return 0;
}
