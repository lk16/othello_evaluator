#include <stdio.h>

#include "board.h"
#include "bot.h"

#define SEARCH_DEPTH 8
#define PERFECT_DEPTH 12


int main(int argc, char **argv) {
    if(argc < 3) {
        printf("error: wrong arguments. Use %s <me> <opp>\n", argv[0]);
        return 1;
    }

    uint64_t me, opp;

    if(sscanf(argv[1], "%lx", &me) < 1){
        printf("error: syntax of me\n");
        return 1;
    }

    if(sscanf(argv[2], "%lx", &opp) < 1){
        printf("error: syntax of opp\n");
        return 1;
    }

    printf("me = %lx\nopp = %lx\n", me, opp);

    struct cubed_board board = (struct cubed_board){
        me: me,
        opp: opp
    };

    cubed_board_print(&board);


    struct cubed_bot *bot = cubed_bot_new();
    cubed_bot_set_search_depth(bot, SEARCH_DEPTH, PERFECT_DEPTH);

    struct cubed_board afterwards;

    cubed_bot_do_move(bot, &board, &afterwards);
    cubed_board_print(&afterwards);


    printf("result = %" PRIdFAST32 "\n", cubed_bot_get_last_best_heur(bot));

    cubed_bot_destroy(bot);
    return 0;
}
