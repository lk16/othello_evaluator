#pragma once

#include <malloc.h>
#include <string.h>

#include "bot.h"
#include "macros.h"
#include "testing.h"
#include "board.h"

#define CUBED_CONTROL_HISTORY_SIZE (100)

enum cubed_display_mode {
    CUBED_MODE_CLI,
    CUBED_MODE_GUI
};

struct cubed_control;

struct cubed_control *cubed_control_new(void);

void cubed_control_destroy(struct cubed_control *control);

void cubed_control_run(struct cubed_control *control);

void cubed_control_parse_args(struct cubed_control *control,int argc,const char **argv);
