#include <malloc.h>
#include <stdio.h>
#include <string.h>
#include "bot.h"

/**
    @brief cubed robot/AI
*/
struct cubed_bot {

    /** @brief bot name */
    char *name;

    /** @brief non-exact search depth */
    size_t search_depth;

    /** @brief exact search depth */
    size_t perfect_depth;

    /** @brief timer for performance measurement */
    GTimer *timer;

    /** @brief remaining depth in current search */
    size_t moves_left;

    /** @brief total visited nodes for performance measurement */
    size_t nodes;

    int_fast32_t last_best_heur;
};

int_fast32_t cubed_bot_get_last_best_heur(const struct cubed_bot *bot) {
    return bot->last_best_heur;
}


static void cubed_bot_print_stats(const struct cubed_bot *bot) {
    double seconds = g_timer_elapsed(bot->timer,NULL);
    size_t nps = (size_t)(bot->nodes / seconds);
    printf("%" PRIdFAST32 " nodes in %lf seconds: %" PRIdFAST32 " nodes/second\n",bot->nodes, seconds,nps);
}

static int_fast32_t cubed_bot_heuristic_moves_uint64(uint64_t me,uint64_t opp) {
    int_fast32_t me_move_count = (int_fast32_t)uint64_count(cubed_board_get_valid_moves(me,opp));
    int_fast32_t opp_move_count = (int_fast32_t)uint64_count(cubed_board_get_valid_moves(opp,me));
    int_fast32_t move_count_diff = me_move_count - opp_move_count;
    int_fast32_t corner_diff = 0;
    corner_diff += !!(me & 0x8000000000000000);
    corner_diff += !!(me & 0x0100000000000000);
    corner_diff += !!(me & 0x0000000000000080);
    corner_diff += !!(me & 0x0000000000000001);
    corner_diff -= !!(opp & 0x8000000000000000);
    corner_diff -= !!(opp & 0x0100000000000000);
    corner_diff -= !!(opp & 0x0000000000000080);
    corner_diff -= !!(opp & 0x0000000000000001);
    return move_count_diff + (3 * corner_diff);
}

int_fast32_t cubed_bot_heuristic_moves(const struct cubed_board *board) {
    return cubed_bot_heuristic_moves_uint64(board->me,board->opp);
}

static int_fast32_t cubed_bot_mtdf_polish(int_fast32_t heur,int_fast32_t alpha) {
    if (heur > alpha) {
        return alpha + 1;
    }
    return alpha;
}

static int_fast32_t cubed_bot_mtdf(struct cubed_bot *bot,uint64_t me,uint64_t opp,int_fast32_t alpha) {
    ++bot->nodes;
    if(bot->moves_left == 0) {
        int_fast32_t heur = cubed_bot_heuristic_moves_uint64(me,opp);
        return cubed_bot_mtdf_polish(heur,alpha);
    }
    uint64_t valid_moves = cubed_board_get_valid_moves(me,opp);
    if (!valid_moves) {
        if(!cubed_board_get_valid_moves(opp,me)) {
            int_fast32_t heur = EXACT_SCORE_FACTOR * cubed_board_get_disc_diff_uint64(me,opp);
            return cubed_bot_mtdf_polish(heur,alpha);
        }
        return -cubed_bot_mtdf(bot,opp,me,-(alpha+1));
    }
    do {
        uint64_t move_bit = uint64_first_bit(valid_moves);
        size_t move_index = uint64_only_bit_index(move_bit);
        uint64_t flipped_discs = cubed_board_get_flips_generic(me,opp,move_index);
        uint64_t child_opp = me | move_bit | flipped_discs;
        uint64_t child_me = opp & (~flipped_discs);
        --bot->moves_left;
        int_fast32_t heur = -cubed_bot_mtdf(bot,child_me,child_opp,-(alpha+1));
        ++bot->moves_left;
        if (heur > alpha) {
            return alpha + 1;
        }
        valid_moves ^= move_bit;
    }
    while (valid_moves);
    return alpha;
}

static int_fast32_t cubed_bot_mtdf_exact(struct cubed_bot *bot,uint64_t me,uint64_t opp,int_fast32_t alpha) {
    ++bot->nodes;
    uint64_t valid_moves = cubed_board_get_valid_moves(me,opp);
    if (!valid_moves) {
        if(!cubed_board_get_valid_moves(opp,me)) {
            int_fast32_t heuristic = cubed_board_get_disc_diff_uint64(me,opp);
            return cubed_bot_mtdf_polish(heuristic,alpha);
        }
        return -cubed_bot_mtdf_exact(bot,opp,me,-(alpha+1));
    }
    while (valid_moves) {
        uint64_t move_bit = uint64_first_bit(valid_moves);
        uint64_t move_index = uint64_only_bit_index(move_bit);
        uint64_t flipped_discs = cubed_board_get_flips_generic(me,opp,move_index);
        uint64_t child_opp = me | move_bit | flipped_discs;
        uint64_t child_me = opp & (~flipped_discs);
        --bot->moves_left;
        int_fast32_t heuristic = -cubed_bot_mtdf_exact(bot,child_me,child_opp,-(alpha+1));
        ++bot->moves_left;
        if (heuristic > alpha) {
            return alpha + 1;
        }
        valid_moves ^= move_bit;
    }
    return alpha;
}


static int_fast32_t cubed_bot_mtdf_wrapper_loop(struct cubed_bot *bot,struct cubed_board *board,
        int_fast32_t lower_bound,int_fast32_t upper_bound,int_fast32_t guess,int_fast32_t step,bool exact
                                               ) {
    int_fast32_t f = guess;
    if(f < lower_bound) {
        f = lower_bound;
    }
    if(f > upper_bound) {
        f = upper_bound;
    }
    while(upper_bound - lower_bound >= step) {
        int_fast32_t bound;
        if(exact) {
            bound = -cubed_bot_mtdf_exact(bot,board->me,board->opp,-(f+1));
        }
        else {
            bound = -cubed_bot_mtdf(bot,board->me,board->opp,-(f+1));
        }
        if(bound == f) {
            f -= step;
            upper_bound = bound;
        }
        else {
            f += step;
            lower_bound = bound;
        }
    }
    return upper_bound;
}

int_fast32_t cubed_bot_mtdf_wrapper(struct cubed_bot *bot,struct cubed_board *board,int_fast32_t lower_bound,
                                    int_fast32_t upper_bound,int_fast32_t guess
                                   ) {
    /*
        We run a capped version of cubed_bot_mtdf_wrapper_loop() first with stepsize 1
        This is because if this non-exact search happens to find an exact solution,
        then the value will be very far from guess. this results in a lot of calls to
        cubed_board_mtdf() and therefore slow execution time.
        We can prevent this by cutting off search with stepsize 1 when the result of the
        non-exact search is not within the upper and lower cap.
        When this happens we run a search with stepsize 2*EXACT_SCORE_FACTOR just like
        cubed_bot_mtdf_exact_wrapper does. Main difference is that we use exact flag as FALSE
        to obtain the disc difference multiplied by EXACT_SCORE_FACTOR.
    */
    const int_fast32_t upper_cap = 40;
    const int_fast32_t lower_cap = -upper_cap;
    int_fast32_t capped_upper_bound = upper_bound;
    if(capped_upper_bound > upper_cap) {
        capped_upper_bound = upper_cap;
    }
    int_fast32_t capped_lower_bound = lower_bound;
    if(capped_lower_bound < lower_cap) {
        capped_lower_bound = lower_cap;
    }
    int_fast32_t capped_result;
    capped_result = cubed_bot_mtdf_wrapper_loop(bot,board,capped_lower_bound,capped_upper_bound,guess,1,FALSE);
    if(capped_result > lower_cap && capped_result < upper_cap) {
        return capped_result;
    }
    return cubed_bot_mtdf_wrapper_loop(bot,board,lower_bound,upper_bound,guess,2*EXACT_SCORE_FACTOR,FALSE);
}

int_fast32_t cubed_bot_mtdf_exact_wrapper(struct cubed_bot *bot,struct cubed_board *board,int_fast32_t lower_bound,
        int_fast32_t upper_bound,int_fast32_t guess
                                         ) {
    return cubed_bot_mtdf_wrapper_loop(bot,board,lower_bound,upper_bound,guess,2,TRUE);
}

static void cubed_bot_sort_children(struct cubed_bot *bot,struct cubed_board_estimate *estimates,
                                    size_t estimate_length,size_t lookahead
                                   ) {
    int_fast32_t best_estimate = MIN_NORMAL_HEURISTIC;
    bot->moves_left = lookahead;
    for(size_t i=0; i<estimate_length; ++i) {
        estimates[i].estimate = cubed_bot_mtdf_wrapper(bot,&estimates[i].board,best_estimate,
                                MAX_NORMAL_HEURISTIC,estimates[i].estimate);
    }
    qsort(estimates,estimate_length,sizeof(*estimates),cubed_board_estimate_compare);
    bot->nodes = 0;
}


static void cubed_bot_search(struct cubed_bot *bot,const struct cubed_board *board,struct cubed_board *res,
                             bool exact
                            ) {
    bot->nodes = 0;
    struct cubed_board_estimate estimates[32];
    size_t total_children = cubed_board_get_children_with_estimates(board,estimates);
    if(bot->search_depth > 4) {
        for(size_t d=2; d <= bot->search_depth-4; d+=2) {
            cubed_bot_sort_children(bot,estimates,total_children,d);
        }
    }
    int_fast32_t best_heur;
    if(exact) {
        best_heur = MIN_EXACT_HEURISTIC;
        size_t empty_count = uint64_count(~(board->me | board->opp));
        printf("bot_%s searching perfectly at depth %zu\n", bot->name,empty_count);
    }
    else {
        best_heur = MIN_NORMAL_HEURISTIC;
        bot->moves_left = bot->search_depth;
        printf("bot_%s searching at depth %zd\n", bot->name, bot->moves_left);
    }
    g_timer_reset(bot->timer);
    g_timer_start(bot->timer);
    *res = estimates[0].board;
    for(size_t i=0; i<total_children; ++i) {
        int_fast32_t heur;
        struct cubed_board *current_child = &estimates[i].board;
        if(exact) {
            heur = cubed_bot_mtdf_exact_wrapper(bot,current_child,best_heur,MAX_EXACT_HEURISTIC,best_heur);
        }
        else {
            --bot->moves_left;
            heur = cubed_bot_mtdf_wrapper(bot,current_child,best_heur,MAX_NORMAL_HEURISTIC,estimates[i].estimate);
            ++bot->moves_left;
        }
        if (heur > best_heur) {
            best_heur = heur;
            *res = estimates[i].board;
        }
        g_timer_stop(bot->timer);
        printf("move %zd/%zd: %" PRIdFAST32 "\n", i+1,total_children,best_heur);
        g_timer_continue(bot->timer);
    }
    bot->last_best_heur = best_heur;
    g_timer_stop(bot->timer);
    cubed_bot_print_stats(bot);
}



struct cubed_bot *cubed_bot_new(void) {
    struct cubed_bot *bot = malloc(sizeof(*bot));
    bot->name = (char *)malloc(10);
    strncpy(bot->name,"default",10);
    bot->search_depth = 6;
    bot->perfect_depth = 12;
    bot->timer = g_timer_new();
    bot->moves_left = 0;
    bot->nodes = 0;
    bot->last_best_heur = 0;
    return bot;
}

void cubed_bot_destroy(struct cubed_bot *bot) {
    free(bot->name);
    g_timer_destroy(bot->timer);
    free(bot);
}

void cubed_bot_set_search_depth(struct cubed_bot *bot,size_t depth,size_t exact_depth) {
    bot->moves_left = bot->search_depth = depth;
    bot->perfect_depth = exact_depth;
}

void cubed_bot_do_move(struct cubed_bot *bot,const struct cubed_board *in,struct cubed_board *out) {
    uint64_t moves = cubed_board_get_valid_moves(in->me,in->opp);
    size_t empty_fields = uint64_count(~(in->me | in->opp));
    bool exact_search = empty_fields <= bot->perfect_depth;
    cubed_bot_search(bot,in,out,exact_search);
}


