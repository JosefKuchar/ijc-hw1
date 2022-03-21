// bitset.c
// Řešení IJC-DU1, příklad a), 21.3.2022
// Autor: Josef Kuchař, FIT
// Přeloženo: gcc 9.3.0

#include "bitset.h"

#ifdef USE_INLINE

extern inline void bitset_free(bitset_t bitset);
extern inline bitset_index_t bitset_size(bitset_t bitset);
extern inline void bitset_setbit(bitset_t bitset, bitset_index_t index, int exp);
extern inline unsigned long bitset_getbit(bitset_t bitset, bitset_index_t index);

#endif  // USE_INLINE
