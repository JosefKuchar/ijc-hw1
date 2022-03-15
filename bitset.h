#include <assert.h>
#include <stdlib.h>
#include "error.h"

// Typedefs for external use
typedef unsigned long* bitset_t;
typedef unsigned long bitset_index_t;

/* INTERNAL MACROS */

// Get index of the bit inside the bitset array
#define _get_a_index(index) (1 + ((index) / sizeof(bitset_index_t)))

// Get bit index inside one bitset_index_t element
#define _get_b_index(index) ((index) % sizeof(bitset_index_t))

/* PUBLIC MACROS */

// Create static bitset
#define bitset_create(name, size)                 \
    static_assert(size > 0 && size <= 300000000); \
    unsigned long name[2 + size / sizeof(bitset_index_t)] = {size};

// Create dynamically allocated bitset
#define bitset_alloc(name, size)                                                            \
    assert(size > 0 && size <= 300000000);                                                  \
    unsigned long* name = calloc(2 + size / sizeof(bitset_index_t), sizeof(unsigned long)); \
    if (name == NULL) {                                                                     \
        error_exit("bitset_alloc: Chyba alokace paměti\n");                                 \
    }                                                                                       \
    name[0] = size;

// Free dynamically allocated bitset
#define bitset_free(name) free(name)

// Get bitset size
#define bitset_size(name) name[0]

// Set bit [index] to [exp]
#define bitset_setbit(name, index, exp)                                                       \
    name[_get_a_index(index)] = (name[_get_a_index(index)] & ~(1UL << _get_b_index(index))) | \
                                ((!!exp) << _get_b_index(index));

// Get bit from [index]
#define bitset_getbit(name, index) ((name[_get_a_index(index)] >> _get_b_index(index)) & 1UL)

#ifdef USE_INLINE

inline bitset_free(bitset_t bitset) {
    free(bitset);
}

inline bitset_size(bitset_t bitset) {
    return bitset[0];
}

#endif  // USE_INLINE
