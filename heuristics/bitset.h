/**
    @file bitset.h
    @brief bitset constants and operations
*/

#pragma once

#include <stdint.h>
#include <stdlib.h>

#include "macros.h"

/**
    @brief Compute first set bit in bitset
    @param bitset the bitset, shall not be 0ull
    @return index of first set bit
*/
size_t uint64_first_index(uint64_t bitset);

/**
    @brief Compute index of bitset with at most one set bit
    @param bitset the bitset, shall not be 0ull
    @return index of the only set bit or 64 if none are set
*/
size_t uint64_only_bit_index(uint64_t bitset);

/**
    @brief Compute first set bit in bitset
    @param bitset the bitset
    @return bitset with at most one set bit
*/
uint64_t uint64_first_bit(uint64_t bitset);

/**
    @brief Compute most significant bit in bitset
    @param n input bitset, shall not be 0ull
    @return bitset with only the most significant bit set
*/
uint64_t uint64_last_bit(uint64_t b);

/**
    @brief Compute the number of set bits in a bitset
    @param bitset the bitset, shall not be 0ull
    @return the number of set bits
*/
size_t uint64_count(uint64_t bitset);
