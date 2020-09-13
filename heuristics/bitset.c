#include <stdint.h>
#include <stdio.h>
#include <malloc.h>

#include "bitset.h"
#include "config.h"

size_t uint64_first_bit(uint64_t b) {
    return b & -b;
}

size_t uint64_first_index(uint64_t b) {
    return (size_t)(__builtin_ffsll((long long)b) - 1);
}

size_t uint64_count(uint64_t b) {
    const size_t bits_per_lookup = CUBED_UINT64_COUNT_LOOKUPTABLE_SIZE;
    const size_t lookup_table_size = 1ull << CUBED_UINT64_COUNT_LOOKUPTABLE_SIZE;
    const uint64_t mask = lookup_table_size - 1;
    static size_t *uint64_count_lookup;
    if(!uint64_count_lookup) {
        // TODO this is a memory leak
        uint64_count_lookup = (size_t *)malloc(lookup_table_size * sizeof(*uint64_count_lookup));
        for(size_t i=0; i<lookup_table_size; ++i) {
            uint64_count_lookup[i] = (size_t)__builtin_popcountll(i);
        }
    }
    size_t result = 0u;
    for(size_t i=0; i<64; i += bits_per_lookup) {
        result += uint64_count_lookup[(b >> i) & mask];
    }
    return result;
}

size_t uint64_only_bit_index(uint64_t b) {
    return uint64_first_index(b);
}


void uint64_reset_before(uint64_t *b,size_t i) {
    if(i < 63) {
        *b &= 0xFFFFFFFFFFFFFFFF << (i+1);
    }
    else {
        *b = 0ull;
    }
}

void uint64_reset_after(uint64_t *b,size_t i) {
    if((i & 0x3F) == 0) {
        *b = 0ull;
    }
    else {
        *b &= 0xFFFFFFFFFFFFFFFF >> (64-i);
    }
}

size_t uint64_last_index(uint64_t b) {
    if (!b) {
        return 64u;
    }
    return (size_t)(63 - __builtin_clzl(b));
}

uint64_t uint64_last_bit(uint64_t b) {
    size_t index = uint64_last_index(b);
    if(index == 64) {
        return 0;
    }
    return 1ull << index;
}