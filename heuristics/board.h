/**
    @file board.h
    @brief othello board
*/

#pragma once

#include <stdint.h>

#include "macros.h"
#include "bitset.h"

/**
    @brief an othello board
*/
struct cubed_board {

    /** @brief bitset containing discs of the player to move */
    uint64_t me;

    /** @brief bitset containing discs of the opponent of the player to move */
    uint64_t opp;
};

/**
    @brief Initilaise a board
    @param board the board
*/
void cubed_board_init_reset(struct cubed_board *board);

/**
    @brief Initialise a board randomly
    @param board the board
    @param ndiscs the number of discs board should have
*/
void cubed_board_init_random(struct cubed_board *board,size_t ndiscs);

/**
    @brief Check if two boards are equal
    @param lhs a board
    @param rhs a board
    @return TRUE if they are equal; else FALSE
*/
bool cubed_board_equals(const struct cubed_board *lhs,const struct cubed_board *rhs);

/**
    @brief Compute a hash for a board
    @param board the board
*/
uint64_t cubed_board_hash(const struct cubed_board *board);

/**
    @brief Print a board to stdout
    @param board a board
*/
void cubed_board_print(const struct cubed_board *board);

/**
    @brief Switch turns without doing a move
    @param board the board
*/
void cubed_board_switch_turn(struct cubed_board *board);


/**
    @brief Compute valid moves for a board
    @param me the bitset with discs of the player to move
    @param opp the bitset with discs of the other player
    @return a bitset containing valid moves
*/
uint64_t cubed_board_get_valid_moves(uint64_t me,uint64_t opp);

/**
    @brief Count disc difference, empties are for winning party
    @param board the board
    @return the disc difference
*/
int cubed_board_get_disc_diff(const struct cubed_board *board);

/**
    @brief Count disc difference, empties are for winning party
    @param me bitset of player to move
    @param opp bitset of other player
    @return the disc difference
*/
int cubed_board_get_disc_diff_uint64(uint64_t me,uint64_t opp);

/**
    @brief Generate all children of a board
    @param board the board
    @param output output array
    @return number of children
*/
size_t cubed_board_get_children(const struct cubed_board *board,struct cubed_board *output);

/**
    @brief Do a move
    @param board the board
    @param field_id index of field to move
    @return bitset of flipped discs
*/
uint64_t cubed_board_do_move(struct cubed_board *board,size_t field_id);

/**
    @brief Get flipped discs
    @param me bitset of player to move
    @param opp bitset of other player
    @param move_id id of move
*/
uint64_t cubed_board_get_flips_generic(uint64_t me,uint64_t opp,size_t move_id);

/**
    @brief Undo a move
    @param board the board
    @param move_bit bitset of bit of the move to undo
    @param undo_data bitset of the flipped discs
*/
void cubed_board_undo_move(struct cubed_board *board,uint64_t move_bit,uint64_t undo_data);

/**
    @brief Compute field that was moved between two boards
    @param before the board before the move
    @param after the board afterwards
    @return the field index
*/
size_t cubed_board_get_move_index(const struct cubed_board *before,const struct cubed_board *after);

/**
    @brief Board with estimated heuristic
*/
struct cubed_board_estimate {

    /** @brief the board */
    struct cubed_board board;

    /** @brief the estimate */
    int estimate;
};

/**
    @brief Compute all children but as cubed_board_estimate
    @param board the parent
    @param output the output array
    @return the number of children
*/
size_t cubed_board_get_children_with_estimates(const struct cubed_board *board,struct cubed_board_estimate *output);

/**
    @brief Compare two cubed_board_estimate instances
    @param lhs a cubed_board_estimate
    @param rhs a cubed_board_estimate
    @return <0 if lhs estimate is smaller; >0 if rhs estimate is smaller; else 0
*/
int cubed_board_estimate_compare(const void *lhs,const void *rhs);

