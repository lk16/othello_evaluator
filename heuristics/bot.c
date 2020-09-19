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

    int last_best_heur;
};

int cubed_bot_get_last_best_heur(const struct cubed_bot *bot) {
    return bot->last_best_heur;
}


static void cubed_bot_print_stats(const struct cubed_bot *bot) {
    double seconds = g_timer_elapsed(bot->timer,NULL);
    size_t nps = (size_t)(bot->nodes / seconds);
    printf("%ld nodes in %lf seconds: %ld nodes/second\n",bot->nodes, seconds,nps);
}



const uint64_t leftMask = 0x7F7F7F7F7F7F7F7F;
const uint64_t rightMask = 0xFEFEFEFEFEFEFEFE;

static int cubed_bot_heuristic_moves_uint64(uint64_t me,uint64_t opp) {

	uint64_t mePotentialMoves = (opp & leftMask) << 1;
	mePotentialMoves |= (opp & rightMask) >> 1;
	mePotentialMoves |= (opp & leftMask) << 9;
	mePotentialMoves |= (opp & rightMask) >> 9;
	mePotentialMoves |= (opp & rightMask) << 7;
	mePotentialMoves |= (opp & leftMask) >> 7;
	mePotentialMoves |= opp << 8;
	mePotentialMoves |= opp >> 8;
	mePotentialMoves &= ~(me | opp);

	uint64_t oppPotentialMoves = (me & leftMask) << 1;
	oppPotentialMoves |= (me & rightMask) >> 1;
	oppPotentialMoves |= (me & leftMask) << 9;
	oppPotentialMoves |= (me & rightMask) >> 9;
	oppPotentialMoves |= (me & rightMask) << 7;
	oppPotentialMoves |= (me & leftMask) >> 7;
	oppPotentialMoves |= me << 8;
	oppPotentialMoves |= me >> 8;
	oppPotentialMoves &= ~(me | opp);

    int potential_move_count_diff = (int)uint64_count(mePotentialMoves) - (int)uint64_count(oppPotentialMoves);

    int corner_diff = 0;
    corner_diff += !!(me & 0x8000000000000000);
    corner_diff += !!(me & 0x0100000000000000);
    corner_diff += !!(me & 0x0000000000000080);
    corner_diff += !!(me & 0x0000000000000001);
    corner_diff -= !!(opp & 0x8000000000000000);
    corner_diff -= !!(opp & 0x0100000000000000);
    corner_diff -= !!(opp & 0x0000000000000080);
    corner_diff -= !!(opp & 0x0000000000000001);

    return potential_move_count_diff + (3 * corner_diff);
}

int cubed_bot_heuristic_moves(const struct cubed_board *board) {
    return cubed_bot_heuristic_moves_uint64(board->me,board->opp);
}

static int cubed_bot_mtdf_polish(int heur,int alpha) {
    if (heur > alpha) {
        return alpha + 1;
    }
    return alpha;
}

static int cubed_bot_mtdf(struct cubed_bot *bot,uint64_t me,uint64_t opp,int alpha) {
    ++bot->nodes;
    if(bot->moves_left == 0) {
        int heur = cubed_bot_heuristic_moves_uint64(me,opp);
        return cubed_bot_mtdf_polish(heur,alpha);
    }
    uint64_t valid_moves = cubed_board_get_valid_moves(me,opp);
    if (!valid_moves) {
        if(!cubed_board_get_valid_moves(opp,me)) {
            int heur = EXACT_SCORE_FACTOR * cubed_board_get_disc_diff_uint64(me,opp);
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
        int heur = -cubed_bot_mtdf(bot,child_me,child_opp,-(alpha+1));
        ++bot->moves_left;
        if (heur > alpha) {
            return alpha + 1;
        }
        valid_moves ^= move_bit;
    }
    while (valid_moves);
    return alpha;
}

static int cubed_bot_mtdf_exact(struct cubed_bot *bot,uint64_t me,uint64_t opp,int alpha) {
    ++bot->nodes;
    uint64_t valid_moves = cubed_board_get_valid_moves(me,opp);
    if (!valid_moves) {
        if(!cubed_board_get_valid_moves(opp,me)) {
            int heuristic = cubed_board_get_disc_diff_uint64(me,opp);
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
        int heuristic = -cubed_bot_mtdf_exact(bot,child_me,child_opp,-(alpha+1));
        ++bot->moves_left;
        if (heuristic > alpha) {
            return alpha + 1;
        }
        valid_moves ^= move_bit;
    }
    return alpha;
}


static int cubed_bot_mtdf_wrapper_loop(struct cubed_bot *bot,struct cubed_board *board,
        int lower_bound,int upper_bound,int guess,int step,bool exact
                                               ) {
    int f = guess;
    if(f < lower_bound) {
        f = lower_bound;
    }
    if(f > upper_bound) {
        f = upper_bound;
    }
    while(upper_bound - lower_bound >= step) {
        int bound;
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

int cubed_bot_mtdf_wrapper(struct cubed_bot *bot,struct cubed_board *board,int lower_bound,
                                    int upper_bound,int guess
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
    const int upper_cap = 40;
    const int lower_cap = -upper_cap;
    int capped_upper_bound = upper_bound;
    if(capped_upper_bound > upper_cap) {
        capped_upper_bound = upper_cap;
    }
    int capped_lower_bound = lower_bound;
    if(capped_lower_bound < lower_cap) {
        capped_lower_bound = lower_cap;
    }
    int capped_result;
    capped_result = cubed_bot_mtdf_wrapper_loop(bot,board,capped_lower_bound,capped_upper_bound,guess,1,FALSE);
    if(capped_result > lower_cap && capped_result < upper_cap) {
        return capped_result;
    }
    return cubed_bot_mtdf_wrapper_loop(bot,board,lower_bound,upper_bound,guess,2*EXACT_SCORE_FACTOR,FALSE);
}

int cubed_bot_mtdf_exact_wrapper(struct cubed_bot *bot,struct cubed_board *board,int lower_bound,
        int upper_bound,int guess
                                         ) {
    return cubed_bot_mtdf_wrapper_loop(bot,board,lower_bound,upper_bound,guess,2,TRUE);
}

static void cubed_bot_sort_children(struct cubed_bot *bot,struct cubed_board_estimate *estimates,
                                    size_t estimate_length,size_t lookahead
                                   ) {
    int best_estimate = MIN_NORMAL_HEURISTIC;
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
    int best_heur;
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
        int heur;
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
        printf("move %zd/%zd: %d\n", i+1,total_children,best_heur);
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
    size_t empty_fields = uint64_count(~(in->me | in->opp));
    bool exact_search = empty_fields <= bot->perfect_depth;
    cubed_bot_search(bot,in,out,exact_search);
}


