// bitset.h
// Řešení IJC-DU1, příklad a), 20.3.2111
// Autor: Josef Kuchař, FIT
// Přeloženo: gcc 9.3.0

#ifndef BITSET_H_INCLUDED
#define BITSET_H_INCLUDED

#include <assert.h>
#include <limits.h>
#include <stdlib.h>
#include "error.h"

typedef unsigned long* bitset_t;
typedef unsigned long bitset_index_t;

#define bitset_create(name, size)                                                         \
    static_assert((size) > 0 && (size) <= 300000000, "bitset_create: Neplatná velikost"); \
    unsigned long name[2 + ((size)-1) / (sizeof(bitset_index_t) * CHAR_BIT)] = {size}

#define bitset_alloc(name, size)                                                              \
    assert((size) > 0 && (size) <= 300000000);                                                \
    bitset_t name =                                                                           \
        calloc(2 + ((size)-1) / (sizeof(bitset_index_t) * CHAR_BIT), sizeof(bitset_index_t)); \
    if (name == NULL) {                                                                       \
        error_exit("bitset_alloc: Chyba alokace paměti\n");                                   \
    }                                                                                         \
    name[0] = size

#ifndef USE_INLINE

/* MACRO VERSIONS */

#define bitset_free(name) free(name)

#define bitset_size(name) name[0]

#define bitset_setbit(name, index, exp)                                                      \
    (index >= bitset_size(name))                                                             \
        ? (error_exit("bitset_setbit: Index %lu mimo rozsah 0..%lu", (unsigned long)(index), \
                      bitset_size(name)),                                                    \
           0)                                                                                \
        : ((exp) ? (bitset[1 + ((index) / (sizeof(bitset_index_t) * CHAR_BIT))] |=           \
                    (1UL << ((index) % (sizeof(bitset_index_t) * CHAR_BIT))))                \
                 : (bitset[1 + ((index) / (sizeof(bitset_index_t) * CHAR_BIT))] &=           \
                    ~(1UL << ((index) % (sizeof(bitset_index_t) * CHAR_BIT)))),              \
           0)

#define bitset_getbit(name, index)                                                           \
    (index >= bitset_size(name))                                                             \
        ? (error_exit("bitset_setbit: Index %lu mimo rozsah 0..%lu", (unsigned long)(index), \
                      bitset_size(name)),                                                    \
           0)                                                                                \
        : ((name[(1 + ((index) / (sizeof(bitset_index_t) * CHAR_BIT)))] >>                   \
            ((index) % (sizeof(bitset_index_t) * CHAR_BIT))) &                               \
           1UL)

#else

/* INLINE VERSIONS */

inline void bitset_free(bitset_t bitset) {
    free(bitset);
}

inline bitset_index_t bitset_size(bitset_t bitset) {
    return bitset[0];
}

inline void bitset_setbit(bitset_t bitset, bitset_index_t index, int exp) {
    if (index >= bitset_size(bitset)) {
        error_exit("bitset_setbit: Index %lu mimo rozsah 0..%lu", index, bitset_size(bitset));
    }

    const unsigned long arr_index = 1 + index / (sizeof(bitset_index_t) * CHAR_BIT);
    const unsigned long bit_index = index % (sizeof(bitset_index_t) * CHAR_BIT);

    if (exp) {
        bitset[arr_index] |= (1UL << bit_index);
    } else {
        bitset[arr_index] &= ~(1UL << bit_index);
    }
}

inline unsigned long bitset_getbit(bitset_t bitset, bitset_index_t index) {
    if (index >= bitset_size(bitset)) {
        error_exit("bitset_setbit: Index %lu mimo rozsah 0..%lu", index, bitset_size(bitset));
    }

    const unsigned long arr_index = 1 + (index / (sizeof(bitset_index_t) * CHAR_BIT));
    const unsigned long bit_index = index % (sizeof(bitset_index_t) * CHAR_BIT);

    return (bitset[arr_index] >> bit_index) & 1UL;
}

#endif  // USE_INLINE

#endif  // BITSET_H_INCLUDED
