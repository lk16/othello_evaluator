/**
    @file macros.h
    @brief macro constants
*/

#pragma once

/**
    @brief type for booleans
*/
#define bool _Bool

/**
    @brief constant representing black player
*/
#define BLACK (0)

/**
    @brief constant representing white player
*/
#define WHITE (1)

/**
    @brief multiplication factor for exact scores in non-exact search
*/
#define EXACT_SCORE_FACTOR (1000)

/**
    @brief maximum heuristic in exact search
*/
#define MAX_EXACT_HEURISTIC (64)

/**
    @brief minimum heuristic in exact search
*/
#define MIN_EXACT_HEURISTIC (-(MAX_EXACT_HEURISTIC))

/**
    @brief maximum heuristic in non-exact search
*/
#define MAX_NORMAL_HEURISTIC (MAX_EXACT_HEURISTIC*EXACT_SCORE_FACTOR)

/**
    @brief minimum heuristic in non-exact search
*/
#define MIN_NORMAL_HEURISTIC (-(MAX_NORMAL_HEURISTIC))