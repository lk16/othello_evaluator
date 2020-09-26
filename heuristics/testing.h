/**
    @file testing.h
    @brief testing and debugging
*/
#pragma once

#include "bitset.h"

/**
    @brief square root of number of testing samples for nested loops
*/
#define CUBED_TESTING_SAMPLES_SQRT (50)

/**
    @brief number of testing samples
*/
#define CUBED_TESTING_SAMPLES (CUBED_TESTING_SAMPLES_SQRT*CUBED_TESTING_SAMPLES_SQRT)

void cubed_sanity_check(bool seeded);
