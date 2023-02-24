#include <stdio.h>
#include <string.h>

#include "subcommands/add.h"
#include "subcommands/list.h"
#include "cmd.h"

struct Subcommand {
    const char *name;
    const char *description;

    int (*handler)(const struct CommandOpts *);
};

int main(int argc, char *argv[]) {
    struct Subcommand subcommands[] = {
            {
                    .name = "add",
                    .description = "ads a new task to the todo list",
                    .handler = subcommand_add,
            },
            {
                    .name = "list",
                    .description = "lists the current todo tasks",
                    .handler = subcommand_list,
            },
    };

    // Show the help menu if no subcommand is provided.
    if (argc <= 1) {
        printf("A simple terminal todo application written in C\n\nAvailable subcommands:\n");
        for (struct Subcommand *i = &subcommands[0];
             i < &subcommands[sizeof(subcommands) / sizeof(struct Subcommand)]; i++) {
            printf("  %s - %s\n", i->name, i->description);
        }
        return 0;
    }

    // Parse the command line options.
    struct CommandOpts commandOpts = {};
    parse_opts(&commandOpts, argc, argv);

    // Figure out which subcommand was called.
    const char *subcommand = argv[1];
    for (struct Subcommand *i = &subcommands[0];
         i < &subcommands[sizeof(subcommands) / sizeof(struct Subcommand)]; i++) {
        if (strcmp(i->name, subcommand) != 0) continue;

        i->handler(&commandOpts);
        return 0;
    }

    // If we reach this, no match was found for our subcommand.
    fprintf(stderr, "Unknown subcommand `%s`", subcommand);
    return 1;
}
