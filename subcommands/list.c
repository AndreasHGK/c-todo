#include "list.h"

#include <stdio.h>

#include "../todo_list.h"

int subcommand_list(const struct CommandOpts *opts) {
    printf("Current todo list:\n");

    struct TodoList list = {};
    if (!read_list(&list, opts->filepath)) {
        fprintf(stderr, "Could not read file `%s` or it does not exist.", opts->filepath);
        return 1;
    }

    for (int i = 0; i < list.count; i++) {
        struct TodoEntry entry = list.entries[i];

        printf("  [%c] %s\n", entry.completed ? 'x' : ' ', entry.desc);
    }
    return 0;
}
