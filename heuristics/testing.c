#ifdef NDEBUG
#undef NDEBUG
#endif

#include <assert.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <sys/time.h>

#include "board.h"
#include "bot.h"
#include "macros.h"
#include "testing.h"

static uint64_t rand64(void) {
    return (uint64_t)rand() | (((uint64_t)rand()) << 32);
}

static void uint64_print(uint64_t bitset) {
    printf("%s","+-----------------+\n");
    for(size_t f=0; f<64; f++) {
        if(f%8 == 0) {
            printf("%s","| ");
        }
        uint64_t thisbit = 1ull << f;
        if(bitset & thisbit) {
            printf("%s","@ ");
        }
        else {
            printf("%s","  ");
        }
        if(f%8 == 7) {
            printf("%s","|\n");
        }
    }
    printf("%s","+-----------------+\n");
}

static int cubed_bot_pvs_polish(int heuristic,int alpha,int beta) {
    assert(alpha <= beta);
    if(heuristic < alpha) {
        return alpha;
    }
    if(heuristic > beta) {
        return beta;
    }
    return heuristic;
}

static int cubed_bot_minimax(const struct cubed_board *board,bool is_max,size_t depth_left) {
    assert(is_max == TRUE || is_max == FALSE);
    assert(board);
    assert(depth_left <= 60);
    int res;
    uint64_t valid_moves;
    struct cubed_board child;
    if(depth_left == 0) {
        res = (is_max ? 1 : -1) * cubed_bot_heuristic_moves(board);
    }
    else {
        valid_moves = cubed_board_get_valid_moves(board->me,board->opp);
        if(valid_moves) {
            res = is_max ? MIN_NORMAL_HEURISTIC : MAX_NORMAL_HEURISTIC;
            while(valid_moves) {
                child = *board;
                uint64_t move_bit = uint64_first_bit(valid_moves);
                cubed_board_do_move(&child,uint64_only_bit_index(move_bit));
                int heur = cubed_bot_minimax(&child,!is_max,depth_left-1);
                valid_moves ^= move_bit;
                if(is_max && heur > res) {
                    res = heur;
                }
                if(!is_max && heur < res) {
                    res = heur;
                }
            }
        }
        else {
            struct cubed_board copy = *board;
            cubed_board_switch_turn(&copy);
            valid_moves = cubed_board_get_valid_moves(copy.me,copy.opp);
            if(valid_moves) {
                res = cubed_bot_minimax(&copy,!is_max,depth_left);
            }
            else {
                res = (is_max ? 1 : -1) * EXACT_SCORE_FACTOR * cubed_board_get_disc_diff(board);
            }
        }
    }
    assert(res >= MIN_NORMAL_HEURISTIC && res <= MAX_NORMAL_HEURISTIC);
    return res;
}

static int cubed_bot_minimax_exact(const struct cubed_board *board,bool is_max) {
    assert(is_max == TRUE || is_max == FALSE);
    assert(board);
    int res;
    struct cubed_board child;
    uint64_t valid_moves = cubed_board_get_valid_moves(board->me,board->opp);
    if(valid_moves) {
        res = is_max ? MIN_EXACT_HEURISTIC : MAX_EXACT_HEURISTIC;
        while(valid_moves) {
            child = *board;
            uint64_t move_bit = uint64_first_bit(valid_moves);
            cubed_board_do_move(&child,uint64_only_bit_index(move_bit));
            int heur = cubed_bot_minimax_exact(&child,!is_max);
            valid_moves ^= move_bit;
            if(is_max && heur > res) {
                res = heur;
            }
            if(!is_max && heur < res) {
                res = heur;
            }
        }
    }
    else {
        struct cubed_board copy = *board;
        cubed_board_switch_turn(&copy);
        valid_moves = cubed_board_get_valid_moves(copy.me,copy.opp);
        if(valid_moves) {
            res = cubed_bot_minimax_exact(&copy,!is_max);
        }
        else {
            res = (is_max ? 1 : -1) * cubed_board_get_disc_diff(board);
        }
    }
    assert(res >= MIN_EXACT_HEURISTIC && res <= MAX_EXACT_HEURISTIC);
    return res;
}


static int cubed_bot_alphabeta_polish(int heuristic,int alpha,int beta) {
    assert(alpha <= beta);
    if(heuristic < alpha) {
        return alpha;
    }
    if(heuristic > beta) {
        return beta;
    }
    return heuristic;
}

static int cubed_bot_alphabeta(const struct cubed_board *board,int alpha,int beta,
                                        size_t depth_left
                                       ) {
    assert(board);
    assert(alpha <= beta);
    assert(depth_left <= 60);
    int res;
    struct cubed_board child;
    uint64_t valid_moves = cubed_board_get_valid_moves(board->me,board->opp);
    if (depth_left == 0) {
        res = cubed_bot_alphabeta_polish(cubed_bot_heuristic_moves(board),alpha,beta);
    }
    else {
        if (valid_moves) {
            res = alpha;
            while (valid_moves) {
                child = *board;
                uint64_t move_bit = uint64_first_bit(valid_moves);
                cubed_board_do_move(&child,uint64_only_bit_index(move_bit));
                int heur = -cubed_bot_alphabeta(&child, -beta, -res, depth_left-1);
                valid_moves ^= move_bit;
                if (heur > res) {
                    res = heur;
                }
                if (res >= beta) {
                    res = beta;
                    break;
                }
            }
        }
        else {
            struct cubed_board copy = *board;
            cubed_board_switch_turn(&copy);
            valid_moves = cubed_board_get_valid_moves(copy.me,copy.opp);
            if (valid_moves) {
                res = -cubed_bot_alphabeta(&copy, -beta, -alpha, depth_left);
            }
            else {
                res = cubed_bot_alphabeta_polish(EXACT_SCORE_FACTOR * cubed_board_get_disc_diff(board),alpha,beta);
            }
        }
    }
    assert(res >= alpha && res <= beta);
    return res;
}

static int cubed_bot_alphabeta_exact(const struct cubed_board *board,int alpha,int beta) {
    assert(board);
    assert(alpha <= beta);
    assert(alpha >= MIN_EXACT_HEURISTIC);
    assert(beta <= MAX_EXACT_HEURISTIC);
    int res;
    struct cubed_board child;
    uint64_t valid_moves = cubed_board_get_valid_moves(board->me,board->opp);
    if (valid_moves) {
        res = alpha;
        while (valid_moves) {
            child = *board;
            uint64_t move_bit = uint64_first_bit(valid_moves);
            cubed_board_do_move(&child,uint64_only_bit_index(move_bit));
            int heur = -cubed_bot_alphabeta_exact(&child, -beta, -res);
            valid_moves ^= move_bit;
            if (heur > res) {
                res = heur;
            }
            if (heur >= beta) {
                res = beta;
                break;
            }
        }
    }
    else {
        struct cubed_board copy = *board;
        cubed_board_switch_turn(&copy);
        valid_moves = cubed_board_get_valid_moves(copy.me,copy.opp);
        if (valid_moves) {
            res = -cubed_bot_alphabeta_exact(&copy, -beta, -alpha);
        }
        else {
            res = cubed_bot_alphabeta_polish(cubed_board_get_disc_diff(board),alpha,beta);
        }
    }
    assert(res >= alpha && res <= beta);
    return res;
}

static int cubed_bot_pvs_null_window(const struct cubed_board *board,int alpha,size_t moves_left) {
    int res;
    struct cubed_board child;
    uint64_t valid_moves;
    if (moves_left == 0) {
        res = cubed_bot_pvs_polish(cubed_bot_heuristic_moves(board),alpha,alpha+1);
    }
    else {
        valid_moves = cubed_board_get_valid_moves(board->me,board->opp);
        if (valid_moves) {
            res = alpha;
            while (valid_moves) {
                child = *board;
                uint64_t move_bit = uint64_first_bit(valid_moves);
                cubed_board_do_move(&child,uint64_only_bit_index(move_bit));
                int heur = -cubed_bot_pvs_null_window(&child, -(alpha+1),moves_left-1);
                valid_moves ^= move_bit;
                if (heur > alpha) {
                    res = alpha + 1;
                    break;
                }
            }
        }
        else {
            struct cubed_board copy = *board;
            cubed_board_switch_turn(&copy);
            valid_moves = cubed_board_get_valid_moves(copy.me,copy.opp);
            if (valid_moves) {
                res = -cubed_bot_pvs_null_window(&copy, -(alpha+1),moves_left);
            }
            else {
                res = cubed_bot_pvs_polish(
                          EXACT_SCORE_FACTOR * cubed_board_get_disc_diff(board),
                          alpha,alpha+1
                      );
            }
        }
    }
    assert(res == alpha || res == (alpha+1));
    return res;
}

static int cubed_bot_pvs(const struct cubed_board *board,int alpha,int beta,
                                  size_t moves_left
                                 ) {
    assert(board);
    assert(alpha <= beta);
    int res;
    struct cubed_board child;
    uint64_t valid_moves;
    if (moves_left == 0) {
        res = cubed_bot_pvs_polish(cubed_bot_heuristic_moves(board),alpha,beta);
    }
    else {
        valid_moves = cubed_board_get_valid_moves(board->me,board->opp);
        if (valid_moves) {
            int heur;
            bool first = TRUE;
            res = alpha;
            while (valid_moves) {
                child = *board;
                uint64_t move_bit = uint64_first_bit(valid_moves);
                cubed_board_do_move(&child,uint64_only_bit_index(move_bit));
                if (first) {
                    heur = -cubed_bot_pvs(&child,-beta, -res,moves_left-1);
                    first = FALSE;
                }
                else {
                    heur = -cubed_bot_pvs_null_window(&child, -(res+1),moves_left-1);
                    if (heur > res) {
                        heur = -cubed_bot_pvs(&child, -beta, -heur,moves_left-1);
                    }
                }
                valid_moves ^= move_bit;
                if (heur > res) {
                    res = heur;
                }
                if (heur >= beta) {
                    res = beta;
                    break;
                }
            }
        }
        else {
            struct cubed_board copy = *board;
            cubed_board_switch_turn(&copy);
            valid_moves = cubed_board_get_valid_moves(copy.me,copy.opp);
            if (valid_moves) {
                res = -cubed_bot_pvs(&copy, -beta, -alpha,moves_left);
            }
            else {
                res = cubed_bot_pvs_polish(EXACT_SCORE_FACTOR * cubed_board_get_disc_diff(board),alpha,beta);
            }
        }
    }
    assert(res >= alpha && res <= beta);
    return res;
}

static int cubed_bot_pvs_exact_null_window(const struct cubed_board *board,int alpha) {
    int res;
    uint64_t valid_moves = cubed_board_get_valid_moves(board->me,board->opp);
    struct cubed_board child;
    if (valid_moves) {
        res = alpha;
        while (valid_moves) {
            child = *board;
            uint64_t move_bit = uint64_first_bit(valid_moves);
            cubed_board_do_move(&child,uint64_only_bit_index(move_bit));
            int heur = -cubed_bot_pvs_exact_null_window(&child, -(alpha+1));
            valid_moves ^= move_bit;
            if (heur > alpha) {
                res = alpha + 1;
                break;
            }
        }
    }
    else {
        struct cubed_board copy = *board;
        cubed_board_switch_turn(&copy);
        valid_moves = cubed_board_get_valid_moves(copy.me,copy.opp);
        if (valid_moves) {
            res = -cubed_bot_pvs_exact_null_window(&copy,-(alpha+1));
        }
        else {
            res = cubed_bot_pvs_polish(cubed_board_get_disc_diff(board),alpha,alpha+1);
        }
    }
    assert(res == alpha || res == (alpha+1));
    return res;
}

static int cubed_bot_pvs_exact(const struct cubed_board *board,int alpha,int beta) {
    assert(alpha <= beta);
    int res;
    struct cubed_board child;
    uint64_t valid_moves = cubed_board_get_valid_moves(board->me,board->opp);
    if (valid_moves) {
        int heur;
        bool first = TRUE;
        res = alpha;
        while (valid_moves) {
            child = *board;
            uint64_t move_bit = uint64_first_bit(valid_moves);
            cubed_board_do_move(&child,uint64_only_bit_index(move_bit));
            if (first) {
                heur = -cubed_bot_pvs_exact(&child, -beta, -res);
                first = FALSE;
            }
            else {
                heur = -cubed_bot_pvs_exact_null_window(&child, -(res+1));
                if (heur > res) {
                    heur = -cubed_bot_pvs_exact(&child, -beta, -res);
                }
            }
            valid_moves ^= move_bit;
            if (heur > res) {
                res = heur;
            }
            if (heur >= beta) {
                res = beta;
                break;
            }
        }
    }
    else {
        struct cubed_board copy = *board;
        cubed_board_switch_turn(&copy);
        valid_moves = cubed_board_get_valid_moves(copy.me,copy.opp);
        if (valid_moves) {
            res = -cubed_bot_pvs_exact(&copy, -beta, -alpha);
        }
        else {
            res = cubed_bot_pvs_polish(cubed_board_get_disc_diff(board),alpha,beta);
        }
    }
    assert(res >= alpha && res <= beta);
    return res;
}







static void cubed_sanity_check_init(bool seeded) {
    unsigned seed = 0;
    if(seeded) {
        struct timeval tv;
        gettimeofday(&tv,NULL);
        seed = (unsigned)(tv.tv_sec ^ tv.tv_usec);
    }
    printf("Running sanity check with seed %d\n",seed);
    srand(seed);
}

static size_t debug_uint64_first_index(uint64_t bitset) {
    for(size_t i=0; i<64; ++i) {
        if(bitset & (1ull << i)) {
            return i;
        }
    }
    // this should never happen
    return 99999;
}

static size_t debug_uint64_only_bit_index(uint64_t bitset) {
    return debug_uint64_first_index(bitset);
}

static uint64_t debug_uint64_first_bit(uint64_t bitset) {
    return 1ull << debug_uint64_first_index(bitset);
}

static size_t debug_uint64_count(uint64_t bitset) {
    size_t count = 0;
    for(size_t i=0; i<64; ++i) {
        if(bitset & (1ull << i)) {
            ++count;
        }
    }
    return count;
}

static void debug_cubed_board_check_valid_state(const struct cubed_board *board) {
    assert((board->me & board->opp) == 0ull);
    assert(((board->opp | board->me) & 0x0000001818000000) == 0x0000001818000000);
}

static void debug_cubed_board_init_reset(struct cubed_board *board) {
    board->me = 0x0000000810000000;
    board->opp = 0x0000001008000000;
}

static uint64_t debug_cubed_board_get_valid_moves(const struct cubed_board *board) {
    const uint64_t empty = ~(board->me | board->opp);
    uint64_t moves = 0ull;
    for(int f=0; f<64; ++f) {
        if(empty & (1ull << f)) {
            for(int dx=-1; dx<=1; ++dx) {
                for(int dy=-1; dy<=1; ++dy) {
                    if(dx == 0 && dy == 0) {
                        continue;
                    }
                    int s = 1;
                    while(TRUE) {
                        int curx = (f%8) + (dx*s);
                        int cury = (f/8) + (dy*s);
                        if(curx >= 8 || cury >= 8 || curx < 0 || cury < 0 ) {
                            break;
                        }
                        int cur = 8*cury + curx;
                        if(board->opp & (1ull << cur)) {
                            ++s;
                        }
                        else {
                            if((board->me & (1ull << cur)) && s >= 2) {
                                moves |= (1ull << f);
                            }
                            break;
                        }
                    }
                }
            }
        }
    }
    return moves;
}


static int debug_cubed_board_get_disc_diff(const struct cubed_board *board) {
    int me_count = (int)uint64_count(board->me);
    int opp_count = (int)uint64_count(board->opp);
    if(me_count > opp_count) {
        return 64 - (2 * opp_count);
    }
    if(opp_count > me_count) {
        return -64 + (2 * me_count);
    }
    return 0;
}

static uint64_t debug_cubed_board_do_move(struct cubed_board *board,size_t field_id) {
    if((board->me | board->opp) & (1ull << field_id)) {
        return 0ull;
    }
    uint64_t flipped = 0ull;
    for(int dx=-1; dx<=1; ++dx) {
        for(int dy=-1; dy<=1; ++dy) {
            if(dx == 0 && dy == 0) {
                continue;
            }
            int s = 1;
            while(TRUE) {
                int curx = (int)(field_id%8) + (dx*s);
                int cury = (int)(field_id/8) + (dy*s);
                int cur = 8*cury + curx;
                if(curx < 0 || curx >= 8 || cury < 0 || cury >= 8) {
                    break;
                }
                if(board->opp & (1ull << cur)) {
                    ++s;
                }
                else {
                    if((board->me & (1ull << cur)) && s >= 2) {
                        for(size_t p=1; p<(size_t)s; ++p) {
                            flipped |= 1ull << (field_id + (8*(size_t)dy*p) + ((size_t)dx*p));
                        }
                    }
                    break;
                }
            }
        }
    }
    board->me |= flipped | (1ull << field_id);
    board->opp &= ~board->me;
    cubed_board_switch_turn(board);
    return flipped;
}

static size_t debug_cubed_board_get_children(const struct cubed_board *board,struct cubed_board *output) {
    struct cubed_board *output_end = output;
    uint64_t moves = debug_cubed_board_get_valid_moves(board);
    while(moves) {
        *output_end = *board;
        size_t move_field = uint64_first_index(moves);
        debug_cubed_board_do_move(output_end,move_field);
        moves ^= (1ull << move_field);
        ++output_end;
    }
    return (size_t)(output_end - output);
}



static void debug_cubed_board_init_random(struct cubed_board *board,size_t ndiscs) {
    cubed_board_init_reset(board);
    struct cubed_board children[32];
    size_t child_count;
    while(uint64_count(board->me | board->opp) != ndiscs) {
        child_count = debug_cubed_board_get_children(board,children);
        if(child_count == 0) {
            cubed_board_switch_turn(board);
            child_count = debug_cubed_board_get_children(board,children);
            if(child_count == 0) {
                debug_cubed_board_init_reset(board);
                continue;
            }
        }
        *board = children[(size_t)rand() % child_count];
    }
}

static void cubed_sanity_check(bool seeded) {
#ifdef NDEBUG
    printf("%s","WARNING: not running sanity check completely.\n");
    printf("%s","This binary is compiled with NDEBUG.\n");
#endif
    cubed_sanity_check_init(seeded);
    {
        printf("%s","Generating uint64_t samples\n");
        assert(CUBED_TESTING_SAMPLES >= 66);
        uint64_t *bitsets = malloc(CUBED_TESTING_SAMPLES * sizeof(*bitsets));
        bitsets[0] = 0ull;
        bitsets[1] = ~0ull;
        for(size_t i=0; i<64; ++i) {
            bitsets[2+i] = 1ull << i;
        }
        for(size_t i=66; i<CUBED_TESTING_SAMPLES; ++i) {
            bitsets[i] = rand64();
        }
        const uint64_t *start,*iter,*end;
        start = bitsets;
        end = bitsets + CUBED_TESTING_SAMPLES;
        printf("Testing %s\n","uint64_first_index");
        for(iter=start; iter!=end; ++iter) {
            if(!*iter) {
                continue;
            }
            assert(uint64_first_index(*iter) == debug_uint64_first_index(*iter));
        }
        printf("Testing %s\n","uint64_only_bit_index");
        for(iter=start; iter!=end; ++iter) {
            if(uint64_count(*iter) <= 1) {
                if(!*iter) {
                    continue;
                }
                assert(uint64_only_bit_index(*iter) == debug_uint64_only_bit_index(*iter));
            }
        }
        printf("Testing %s\n","uint64_first_bit");
        for(iter=start; iter!=end; ++iter) {
            if(!*iter) {
                continue;
            }
            assert(uint64_first_bit(*iter) == debug_uint64_first_bit(*iter));
        }
        printf("Testing %s\n","uint64_count");
        for(iter=start; iter!=end; ++iter) {
            assert(uint64_count(*iter) == debug_uint64_count(*iter));
        }
        free(bitsets);
    }
    {
        struct cubed_board *boards = malloc(CUBED_TESTING_SAMPLES * sizeof(*boards));
        debug_cubed_board_init_reset(&boards[0]);
        debug_cubed_board_check_valid_state(&boards[0]);
        printf("%s","Generating cubed_board samples\n");
        for(size_t i=1; i<CUBED_TESTING_SAMPLES; ++i) {
            size_t ndiscs = 5 + i%60;
            debug_cubed_board_init_random(&boards[i],ndiscs);
            debug_cubed_board_check_valid_state(&boards[i]);
            assert(uint64_count(boards[i].me | boards[i].opp) == ndiscs);
        }
        const struct cubed_board *start,*iter,*end;
        struct cubed_board copy[2];
        start = boards;
        end = boards + CUBED_TESTING_SAMPLES;
        printf("Testing %s\n","cubed_board_switch_turn");
        for(iter=start; iter!=end; ++iter) {
            copy[0] = *iter;
            cubed_board_switch_turn(&copy[0]);
            debug_cubed_board_check_valid_state(&copy[0]);
            assert(copy[0].me == iter->opp && copy[0].opp == iter->me);
        }
        printf("Testing %s\n","cubed_board_get_valid_moves");
        for(iter=start; iter!=end; ++iter) {
            assert(cubed_board_get_valid_moves(iter->me,iter->opp) == debug_cubed_board_get_valid_moves(iter));
        }
        printf("Testing %s\n","cubed_board_get_disc_diff");
        for(iter=start; iter!=end; ++iter) {
            assert(cubed_board_get_disc_diff(iter) == debug_cubed_board_get_disc_diff(iter));
        }
        printf("Testing %s\n","cubed_board_do_move");
        for(iter=start; iter!=end; ++iter) {
            uint64_t moves = debug_cubed_board_get_valid_moves(iter);
            for(size_t i=0; i<64; ++i) {
                if(moves & (1ull << i)) {
                    copy[0] = copy[1] = *iter;
                    uint64_t lhs,rhs;
                    lhs = cubed_board_do_move(&copy[0],i);
                    rhs = debug_cubed_board_do_move(&copy[1],i);
                    if(lhs != rhs) {
                        printf("Test case %ld went wrong.\n",iter-start);
                        cubed_board_print(iter);
                        uint64_print(lhs);
                        cubed_board_switch_turn(&copy[0]);
                        cubed_board_print(&copy[0]);
                        uint64_print(rhs);
                        cubed_board_switch_turn(&copy[1]);
                        cubed_board_print(&copy[1]);
                        assert(0);
                    }
                    assert(cubed_board_equals(&copy[0],&copy[1]));
                    debug_cubed_board_check_valid_state(copy + 0);
                    debug_cubed_board_check_valid_state(copy + 1);
                }
            }
        }
        printf("Testing %s\n","cubed_board_get_children");
        struct cubed_board lhs_children[32];
        struct cubed_board rhs_children[32];
        for(iter=start; iter!=end; ++iter) {
            size_t child_count = uint64_count(cubed_board_get_valid_moves(iter->me,iter->opp));
            assert(child_count == cubed_board_get_children(iter,lhs_children));
            assert(child_count == debug_cubed_board_get_children(iter,rhs_children));
            for(size_t i=0; i<child_count; ++i) {
                bool found = FALSE;
                for(size_t j=0; j<child_count; ++j) {
                    if(cubed_board_equals(lhs_children + i,rhs_children + j)) {
                        found = TRUE;
                        break;
                    }
                }
                assert(found);
                debug_cubed_board_check_valid_state(lhs_children + i);
                debug_cubed_board_check_valid_state(rhs_children + i);
            }
        }
        printf("Testing %s\n","cubed_board_undo_move");
        for(iter=start; iter!=end; ++iter) {
            uint64_t moves = debug_cubed_board_get_valid_moves(iter);
            for(size_t i=0; i<64; ++i) {
                if(moves & (1ull << i)) {
                    copy[0] = *iter;
                    uint64_t undo_data = cubed_board_do_move(&copy[0],i);
                    cubed_board_undo_move(&copy[0],1ull << i,undo_data);
                    assert(cubed_board_equals(&copy[0],iter));
                    debug_cubed_board_check_valid_state(copy);
                }
            }
        }
        free(boards);
    }
    {
        printf("Testing %s\n","alphabeta functions");
        struct cubed_board board;
        struct cubed_bot *bot;
        bot = cubed_bot_new();
        int pvs_heur,mtdf_heur,high,low;
        int ab_heur,mm_heur;
        size_t loop_count = 0;
        size_t ok_count = 0;
        while(loop_count < 1000000) {
            ++loop_count;
            size_t search_depth = 1 + (rand() % 4);
            size_t exact_depth = 1 + (rand() % 4);
            cubed_bot_set_search_depth(bot,search_depth,exact_depth);
            size_t discs = 4 + rand() % 61;
            cubed_board_init_random(&board,discs);
            struct cubed_board copy = board;
            if(discs >= (64 - exact_depth)) {
                low = MIN_EXACT_HEURISTIC;
                high = MAX_EXACT_HEURISTIC;
                mtdf_heur = cubed_bot_mtdf_exact_wrapper(bot,&board,low,high,0);
                assert(cubed_board_equals(&board,&copy));
                cubed_bot_set_search_depth(bot,search_depth,exact_depth);
                pvs_heur = -cubed_bot_pvs_exact(&board,low,high);
                assert(cubed_board_equals(&board,&copy));
                cubed_bot_set_search_depth(bot,search_depth,exact_depth);
                ab_heur = -cubed_bot_alphabeta_exact(&board,low,high);
                assert(cubed_board_equals(&board,&copy));
                cubed_bot_set_search_depth(bot,search_depth,exact_depth);
                mm_heur = -cubed_bot_minimax_exact(&board,TRUE);
                assert(cubed_board_equals(&board,&copy));
                cubed_bot_set_search_depth(bot,search_depth,exact_depth);
            }
            else {
                low = MIN_NORMAL_HEURISTIC;
                high = MAX_NORMAL_HEURISTIC;
                mtdf_heur = cubed_bot_mtdf_wrapper(bot,&board,low,high,0);
                assert(cubed_board_equals(&board,&copy));
                cubed_bot_set_search_depth(bot,search_depth,exact_depth);
                pvs_heur = -cubed_bot_pvs(&board,low,high,search_depth);
                assert(cubed_board_equals(&board,&copy));
                cubed_bot_set_search_depth(bot,search_depth,exact_depth);
                ab_heur = -cubed_bot_alphabeta(&board,low,high,search_depth);
                assert(cubed_board_equals(&board,&copy));
                cubed_bot_set_search_depth(bot,search_depth,exact_depth);
                mm_heur = -cubed_bot_minimax(&board,TRUE,search_depth);
                assert(cubed_board_equals(&board,&copy));
                cubed_bot_set_search_depth(bot,search_depth,exact_depth);
            }
            if(mtdf_heur == pvs_heur && mtdf_heur == ab_heur && mtdf_heur == mm_heur) {
                ok_count++;
            }
            else {
                printf("mtdf_heur = %d\n",mtdf_heur);
                printf("pvs_heur = %d\n",pvs_heur);
                printf("ab_heur = %d\n",ab_heur);
                printf("mm_heur = %d\n",mm_heur);
                cubed_board_print(&board);
                printf("%lx %lx\n",board.me,board.opp);
            }
            if(loop_count % 1000 == 0) {
                printf("Ran %lu tests, %lu were ok: %lf %%\n",loop_count,ok_count,(100.0*ok_count)/loop_count);
            }
        }
        cubed_bot_destroy(bot);
    }
}

int main(int argc,char **argv) {
    bool seeded = FALSE;
    if(argc >= 2) {
        if(strcmp(argv[1],"-s") == 0) {
            seeded = TRUE;
        }
    }
    cubed_sanity_check(seeded);
    return 0;
}
