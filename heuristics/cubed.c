#include <stdio.h>
#include <string.h>
#include <time.h>

#include "bitset.h"
#include "bot.h"
#include "control.h"
#include "cubed.h"


int main(int argc,char **argv) {

	srand(time(NULL));

    struct cubed_control *control;
    control = cubed_control_new();
    cubed_control_parse_args(control,argc,(const char **)argv);
    cubed_control_run(control);
    cubed_control_destroy(control);
    return 0;
}
