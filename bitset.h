#include <stdlib.h>

typedef unsigned long* bitset_t;

typedef unsigned long bitset_index_t;

#define bitset_create(name, size) \
    unsigned long name[2 + size / sizeof(bitset_index_t)] = {size};

#define bitset_alloc(name, size)                                          \
    unsigned long* name =                                                 \
        calloc(2 + size / sizeof(bitset_index_t), sizeof(unsigned long)); \
    name[0] = size;

#define bitset_free(a) free(a)

#define bitset_size(a) a[0]

#define bitset_setbit(name, index, exp)                \
    name[1 + (index / sizeof(bitset_index_t))] =       \
        (name[1 + index / sizeof(bitset_index_t)] &    \
         ~(1UL << (index % sizeof(bitset_index_t)))) | \
        ((!!exp) << (index % sizeof(bitset_index_t)))

#define bitset_getbit(name, index)                  \
    ((name[1 + (index / sizeof(bitset_index_t))] >> \
      (index % sizeof(bitset_index_t))) &           \
     1UL)

// static_assert(size > 0,
//                 "bitset_create: Bitset musi mit nezapornou velikost");
