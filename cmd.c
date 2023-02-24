#include "cmd.h"

void parse_opts(struct CommandOpts * opts, int argc, char *argv[]) {
    // Write default values
    opts->filepath = "./todo.tl";

    // Parse command line arguments
    for (int i = 2; i < argc; i++) {
        continue; // todo
    }
}
