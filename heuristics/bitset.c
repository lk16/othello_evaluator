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
    return (size_t)__builtin_popcountll(b);
}

size_t uint64_only_bit_index(uint64_t b) {
    return uint64_first_index(b);
}
