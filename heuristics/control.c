#include "control.h"

struct cubed_game_state {
    struct cubed_board board;
    bool white_to_move;
};

struct cubed_control {
    enum cubed_display_mode display_mode;
    struct cubed_game_state *history;
    struct cubed_game_state *current_state;
    struct cubed_game_state *redo_max;
    struct cubed_bot *bot[2];
    bool use_xot;
    bool use_forced_moves;
    struct cubed_board *xot_boards;
};

typedef size_t(*control_modifier_t)(struct cubed_control *control,
                                    const char **args,size_t remaining_args);

struct cubed_control_modifier {
    const char *flag;
    control_modifier_t modifier;
};


static void cubed_game_state_print(const struct cubed_game_state *state) {
    struct cubed_board copy = state->board;
    if(state->white_to_move) {
        cubed_board_switch_turn(&copy);
    }
    uint64_t moves = cubed_board_get_valid_moves(state->board.me,state->board.opp);
    // top line
    char move_char = 'a';
    printf("%s","+-a-b-c-d-e-f-g-h-+\n");
    for(int f=0; f<64; f++) {
        // left line
        if(f%8 == 0) {
            printf("%d ",(f/8)+1);
        }
        uint64_t thisbit = 1ull << f;
        if(copy.me & thisbit) {
            printf("%s","\033[31;1m\u2B24\033[0m ");
        }
        else if(copy.opp & thisbit) {
            printf("%s","\033[34;1m\u2B24\033[0m ");
        }
        else if(moves & thisbit) {
            printf("\033[33;1m%c\033[0m ",move_char);
            ++move_char;
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




static void cubed_human_do_cli_move(const struct cubed_control *control,const struct cubed_board *board,
    struct cubed_board *output
) {
    char buff[20];
    *output = *board;
    struct cubed_board children[32];
    size_t child_count = cubed_board_get_children(board,children);
    if(child_count == 1 && control->use_forced_moves){
        printf("%s","Human has only one move.\n");
        *output = children[0];
        return;
    }

    size_t move_num;
    int scanf_value;
    do {
        printf("%s","Enter a move: ");
        scanf_value = scanf("%19s",buff);
        move_num = (size_t)(buff[0] - 'a');
    } while(scanf_value != 1 && move_num >= child_count);

    *output = children[move_num];
}

static void cubed_cli_game(struct cubed_control *control) {
    struct cubed_game_state *state,*next_state;
    struct cubed_bot *bot;
    while(1) {
        state = control->current_state;
        cubed_game_state_print(state);
        next_state = state + 1;
        *next_state = *state;
        if(cubed_board_get_valid_moves(state->board.me,state->board.opp)) {
            bot = control->bot[(size_t)state->white_to_move];
            if(bot) {
                cubed_bot_do_move(bot,&next_state->board,&next_state->board);
            }
            else {
                cubed_human_do_cli_move(control,&next_state->board,&next_state->board);
            }
        }
        else {
            if(!cubed_board_get_valid_moves(state->board.opp,state->board.me)) {
                break;
            }
            cubed_board_switch_turn(&next_state->board);
        }
        next_state->white_to_move = !next_state->white_to_move;
        control->current_state = next_state;
    }
    cubed_game_state_print(state);
    size_t me_count = uint64_count(state->board.me);
    size_t opp_count = uint64_count(state->board.opp);
    if(state->white_to_move) {
        printf("White (%zu) - Black (%zu)\n",me_count,opp_count);
    }
    else {
        printf("White (%zu) - Black (%zu)\n",opp_count,me_count);
    }
}

static size_t cubed_flag_bot(struct cubed_control *control,const char **args,size_t remaining_args){
    if(remaining_args < 4){
        printf("%s","Insufficient arguments.\n");
        return 0;
    }

    struct cubed_bot **bot = NULL;

    if((strcmp(args[1],"b") == 0) || (strcmp(args[1],"black")) == 0){
        bot = &control->bot[0];
    }


    if((strcmp(args[1],"w") == 0) || (strcmp(args[1],"white")) == 0){
        bot = &control->bot[1];
    }

    if(!bot){
        printf("%s","Bot colour not recognised.\n");
        return 0;
    }

    size_t depth,perfect_depth;
    if ((sscanf(args[2],"%zu",&depth) < 0) || (sscanf(args[3],"%zu",&perfect_depth) < 0)){
        printf("%s","Search depth or perfect search depth not recognised.\n");
        return 0;
    }

    if(depth == 0 || depth > 60 || perfect_depth == 0 || perfect_depth > 60){
        printf("%s","Search depth or perfect search depth out of bounds.\n");
        return 0;
    }

    if(*bot){
        // old bot found, free memory to prevent leaks
        cubed_bot_destroy(*bot);
        *bot = NULL;
    }

    *bot = cubed_bot_new();
    cubed_bot_set_search_depth(*bot,depth,perfect_depth);
    return 4;
}

static size_t cubed_flag_xot(struct cubed_control *control,const char **args,size_t remaining_args){
    (void)args;
    (void)remaining_args;
    control->use_xot = 1;
    return 1;
}

static size_t cubed_flag_forced_moves(struct cubed_control *control,const char **args,size_t remaining_args){
    (void)args;
    (void)remaining_args;
    control->use_forced_moves = 1;
    return 1;
}

static const struct cubed_control_modifier control_modifiers[] = {
    {"-b",cubed_flag_bot},
    {"--bot",cubed_flag_bot},
    {"-x",cubed_flag_xot},
    {"--xot",cubed_flag_xot},
    {"-f",cubed_flag_forced_moves}
};

static void cubed_board_init_xot(struct cubed_board *board,struct cubed_control *control){

    const size_t n_xot_boards = 10784;

    if(!control->xot_boards){
        struct cubed_board *xot_boards;
        xot_boards = malloc(n_xot_boards * sizeof(*control->xot_boards));

        FILE *xot_file = fopen("resources/xot","r");
        const size_t buff_size = 100;
        char buff[buff_size];

        struct cubed_board *xot_board = xot_boards;
        while(fgets(buff,buff_size,xot_file)){
            int res = sscanf(buff, "0x%lx 0x%lx",&xot_board->me,&xot_board->opp);
            if(res < 0){
                printf("%s","Reading xot file failed.\n");
                exit(1);
            }
            ++xot_board;
            if(xot_board - xot_boards > (int)n_xot_boards){
                printf("%s","Xot file too long.\n");
                exit(1);
            }
        }
        fclose(xot_file);

        control->xot_boards = xot_boards;
    }

    *board = control->xot_boards[rand() % n_xot_boards];
}



struct cubed_control *cubed_control_new(void) {
    struct cubed_control *control = malloc(sizeof(*control));
    control->display_mode = CUBED_MODE_CLI;
    control->history = malloc(CUBED_CONTROL_HISTORY_SIZE * sizeof(*control->history));
    control->current_state = control->history;
    control->redo_max = control->history;
    control->bot[0] = NULL;
    control->bot[1] = NULL;
    control->use_xot = 0;
    control->use_forced_moves = 0;
    control->xot_boards = NULL;
    cubed_board_init_reset(&control->current_state->board);
    control->current_state->white_to_move = 0;
    return control;
}

void cubed_control_destroy(struct cubed_control *control) {
    for(size_t i=0; i<2; ++i) {
        if(control->bot[i]) {
            cubed_bot_destroy(control->bot[i]);
        }
    }
    free(control->history);
    if(control->xot_boards){
        free(control->xot_boards);
    }
    free(control);
}


void cubed_control_parse_args(struct cubed_control *control,int argc,const char **argv) {
    const char **argv_end = argv + argc;
    const char **arg = argv + 1;
    const size_t control_modifiers_length = sizeof(control_modifiers) / sizeof(*control_modifiers);
    while(arg != argv_end) {
        control_modifier_t modifier = NULL;
        for(size_t i=0; i<control_modifiers_length; ++i) {
            if(strcmp(*arg,control_modifiers[i].flag) == 0) {
                modifier = control_modifiers[i].modifier;
                break;
            }
        }
        if(!modifier) {
            printf("Invalid flag: %s\n",*arg);
            exit(1);
        }
        size_t remaining_args = argv_end - arg;
        size_t used_arguments = modifier(control,arg,remaining_args);
        if(used_arguments == 0) {
            printf("Error parsing flag %s\n",*arg);
            exit(1);
        }
        arg += used_arguments;
    }
}


void cubed_control_run(struct cubed_control *control) {
    if(control->use_xot){
        cubed_board_init_xot(&control->current_state->board,control);
    }
    switch(control->display_mode) {
        case CUBED_MODE_CLI:
            cubed_cli_game(control);
            break;
        case CUBED_MODE_GUI:
            printf("%s","GUI mode is not implemented yet.\n");
            break;
        default:
            printf("%s","Display mode not recognised.\n");
            break;
    }
}
