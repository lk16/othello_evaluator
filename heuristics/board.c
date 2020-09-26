
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

#include "board.h"

void cubed_board_init_reset(struct cubed_board *board) {
    board->me = (1ull << 28) | (1ull << 35);
    board->opp = (1ul << 27) | (1ull << 36);
}

void cubed_board_print(const struct cubed_board *board) {
    uint64_t moves = cubed_board_get_valid_moves(board->me,board->opp);
    // top line
    printf("%s","+-a-b-c-d-e-f-g-h-+\n");
    for(size_t f=0; f<64; f++) {
        // left line
        if(f%8 == 0) {
            printf("%zu ",(f/8)+1);
        }
        uint64_t thisbit = 1ull << f;
        if(board->me & thisbit) {
            printf("%s","\033[31;1m\u2B24\033[0m ");
        }
        else if(board->opp & thisbit) {
            printf("%s","\033[34;1m\u2B24\033[0m ");
        }
        else if(moves & thisbit) {
            printf("%s","- ");
        }
        else {
            printf("%s","  ");
        }
        // right line
        if(f%8 == 7) {
            printf("%s","|\n");
        }
    }
    // bottom line
    printf("%s","+-----------------+\n");
}


uint64_t cubed_board_hash(const struct cubed_board *board) {
    uint64_t me_hash = (board->me << 15) | (board->me >> 49);
    uint64_t opp_hash = (board->opp << 42) | (board->opp >> 22);
    return me_hash ^ opp_hash;
}


int cubed_board_get_disc_diff(const struct cubed_board *board) {
    return cubed_board_get_disc_diff_uint64(board->me,board->opp);
}

int cubed_board_get_disc_diff_uint64(uint64_t me,uint64_t opp) {
    int me_count = (int)uint64_count(me);
    int opp_count = (int)uint64_count(opp);
    if (me_count > opp_count) {
        return 64 - (2* opp_count);
    }
    else if(me_count == opp_count) {
        return 0;
    }
    return -(64 - (2 * me_count));
}

size_t cubed_board_get_children(const struct cubed_board *board,struct cubed_board *output) {
    uint64_t valid_moves = cubed_board_get_valid_moves(board->me,board->opp);
    struct cubed_board *output_end = output;
    while (valid_moves) {
        uint64_t move_bit = uint64_first_bit(valid_moves);
        *output_end = *board;
        cubed_board_do_move(output_end,(size_t)uint64_only_bit_index(move_bit));
        valid_moves ^= move_bit;
        ++output_end;
    }
    return (size_t)(output_end - output);
}


size_t cubed_board_get_children_with_estimates(const struct cubed_board *board,struct cubed_board_estimate *output) {
    uint64_t valid_moves = cubed_board_get_valid_moves(board->me,board->opp);
    struct cubed_board_estimate *output_end = output;
    while (valid_moves) {
        uint64_t move_bit = uint64_first_bit(valid_moves);
        output_end->board = *board;
        output_end->estimate = 0;
        cubed_board_do_move(&output_end->board,(size_t)uint64_only_bit_index(move_bit));
        valid_moves ^= move_bit;
        ++output_end;
    }
    return (size_t)(output_end - output);
}

void cubed_board_switch_turn(struct cubed_board *board) {
    uint64_t tmp = board->me;
    board->me = board->opp;
    board->opp = tmp;
}

static uint64_t cubed_board_get_valid_moves_helper(uint64_t me,uint64_t mask,size_t n) {
    uint64_t flip_l, flip_r, mask_l, mask_r;
    flip_l = mask & (me << n);
    flip_l |= mask & (flip_l << n);
    mask_l = mask & (mask << n);
    flip_l |= mask_l & (flip_l << (2*n));
    flip_l |= mask_l & (flip_l << (2*n));
    flip_r = mask & (me >> n);
    flip_r |= mask & (flip_r >> n);
    mask_r = mask & (mask >> n);
    flip_r |= mask_r & (flip_r >> (2*n));
    flip_r |= mask_r & (flip_r >> (2*n));
    return (flip_l << n) | (flip_r >> n);
}


uint64_t cubed_board_get_valid_moves(uint64_t me,uint64_t opp) {
    // this function is a modified version of code from Edax
    const uint64_t mask = opp & 0x7E7E7E7E7E7E7E7Eull;
    uint64_t res = cubed_board_get_valid_moves_helper(me,mask,1);
    res |= cubed_board_get_valid_moves_helper(me,mask,7);
    res |= cubed_board_get_valid_moves_helper(me,mask,9);
    res |= cubed_board_get_valid_moves_helper(me,opp,8);
    return res & ~(me | opp);
}

void cubed_board_init_random(struct cubed_board *board,size_t ndiscs) {
    cubed_board_init_reset(board);
    struct cubed_board children[32];
    size_t child_count;
    while(uint64_count(board->me | board->opp) != ndiscs) {
        child_count = cubed_board_get_children(board,children);
        if(child_count == 0) {
            cubed_board_switch_turn(board);
            child_count = cubed_board_get_children(board,children);
            if(child_count == 0) {
                cubed_board_init_reset(board);
                continue;
            }
        }
        *board = children[(size_t)rand() % child_count];
    }
}

size_t cubed_board_get_move_index(const struct cubed_board *before,const struct cubed_board *after) {
    uint64_t before_discs = before->me | before->opp;
    uint64_t after_discs = after->me | after->opp;
    uint64_t diff = before_discs ^ after_discs;
    if(!diff) {
        // this should not happen
        // no new disc was placed
        return 64;
    }
    return uint64_first_index(diff);
}

#include "flip_sse.c"

static unsigned long long(*const cubed_move_funcs[64])(unsigned long long,unsigned long long) = {
    flip_A1,
    flip_B1,
    flip_C1,
    flip_D1,
    flip_E1,
    flip_F1,
    flip_G1,
    flip_H1,
    flip_A2,
    flip_B2,
    flip_C2,
    flip_D2,
    flip_E2,
    flip_F2,
    flip_G2,
    flip_H2,
    flip_A3,
    flip_B3,
    flip_C3,
    flip_D3,
    flip_E3,
    flip_F3,
    flip_G3,
    flip_H3,
    flip_A4,
    flip_B4,
    flip_C4,
    flip_D4,
    flip_E4,
    flip_F4,
    flip_G4,
    flip_H4,
    flip_A5,
    flip_B5,
    flip_C5,
    flip_D5,
    flip_E5,
    flip_F5,
    flip_G5,
    flip_H5,
    flip_A6,
    flip_B6,
    flip_C6,
    flip_D6,
    flip_E6,
    flip_F6,
    flip_G6,
    flip_H6,
    flip_A7,
    flip_B7,
    flip_C7,
    flip_D7,
    flip_E7,
    flip_F7,
    flip_G7,
    flip_H7,
    flip_A8,
    flip_B8,
    flip_C8,
    flip_D8,
    flip_E8,
    flip_F8,
    flip_G8,
    flip_H8
};


uint64_t cubed_board_get_flips_generic(uint64_t me,uint64_t opp,size_t move_id) {
    return (unsigned long long)cubed_move_funcs[move_id]((unsigned long long)me,(unsigned long long)opp);
}



uint64_t cubed_board_do_move(struct cubed_board *board,size_t move_id) {
    uint64_t flipped = cubed_board_get_flips_generic(board->me,board->opp,move_id);
    board->me |= flipped | (1ull << move_id);
    board->opp &= ~board->me;
    cubed_board_switch_turn(board);
    return flipped;
}

bool cubed_board_equals(const struct cubed_board *lhs,const struct cubed_board *rhs) {
    return lhs->me == rhs->me && lhs->opp == rhs->opp;
}

void cubed_board_undo_move(struct cubed_board *board,uint64_t move_bit,uint64_t undo_data) {
    uint64_t tmp = board->me;
    board->me = board->opp & ~(undo_data | move_bit);
    board->opp = tmp | undo_data;
}

int cubed_board_estimate_compare(const void *lhs,const void *rhs) {
    const struct cubed_board_estimate *l,*r;
    l = (const struct cubed_board_estimate *)lhs;
    r = (const struct cubed_board_estimate *)rhs;
    return (int)(r->estimate - l->estimate);
}
