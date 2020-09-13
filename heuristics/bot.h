/**
    @file bot.h
    @brief cubed bot/AI
*/

#pragma once

#include <sys/time.h>

#include <inttypes.h>
#include <stdlib.h>
#include <glib.h>

#include "board.h"

/**
    @brief maximum search depth for a node to end up in hash table
*/
#define CUBED_BOT_MAX_HT_DEPTH (8)

struct cubed_bot;

/**
    @brief Allocate a new cubed_bot
    @return the new cubed_bot
*/
struct cubed_bot *cubed_bot_new(void);

/**
    @brief Destroy a bot
    @param bot the bot
*/
void cubed_bot_destroy(struct cubed_bot *bot);

/**
    @brief Set the name of the bot
    @param bot the bot
    @param name the new name
*/
void cubed_bot_set_name(struct cubed_bot *bot,char *name);

/**
    @brief Set search depth of bot
    @param bot the bot
    @param depth normal search depth
    @param exact_depth exact search depth
*/
void cubed_bot_set_search_depth(struct cubed_bot *bot,size_t depth,size_t exact_depth);


/**
    @brief Do a move
    @param bot the bot
    @param in the board before doing a move
    @param out the board after doing a move
*/
void cubed_bot_do_move(struct cubed_bot *bot,const struct cubed_board *in,struct cubed_board *out);

/**
    @brief Compute non-exact heuristic for a board
    @param board the board
    @return the heuristic
*/
int_fast32_t cubed_bot_heuristic_moves(const struct cubed_board *board);

/**
    @brief Call mtdf cubed_bot_mtdf repeatedly to find minimax value
    @param bot the bot
    @param board the board
    @param lower_bound lower bound
    @param upper_bound upper bound
    @param guess guessed minimax value
*/
int_fast32_t cubed_bot_mtdf_wrapper(struct cubed_bot *bot,struct cubed_board *board,int_fast32_t lower_bound,
                                    int_fast32_t upper_bound,int_fast32_t guess);


/**
    @brief Call mtdf cubed_bot_mtdf_exact repeatedly to find exact minimax value
    @param bot the bot
    @param board the board
    @param lower_bound lower bound
    @param upper_bound upper bound
    @param guess guessed minimax value
*/
int_fast32_t cubed_bot_mtdf_exact_wrapper(struct cubed_bot *bot,struct cubed_board *board,int_fast32_t lower_bound,
        int_fast32_t upper_bound,int_fast32_t guess);

int_fast32_t cubed_bot_get_last_best_heur(const struct cubed_bot *bot);
