#include <stdio.h>
#include <string.h>

#include "subcommands/list.h"
#include "cmd.h"
#include "todo_list.h"

struct Subcommand {
    const char *name;
    const char *description;

    int (*handler)(const struct CommandOpts *);
};

// todo: remove
void test() {
    struct TodoList list = {
            .count = 0,
            .entries = NULL,
    };
    list_append(&list, (struct TodoEntry) {
            .desc = "This is an entry",
            .completed = false,
    });
    list_append(&list, (struct TodoEntry) {
            .desc = "aThis is another entry",
            .completed = true,
    });
    list_append(&list, (struct TodoEntry) {
            .desc = "This is a third",
            .completed = false,
    });
    list_append(&list, (struct TodoEntry) {
            .desc = "BRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRR",
            .completed = false,
    });

    write_list(&list, "./todo.tl");

    struct TodoList list2 = {};
    read_list(&list2, "./todo.tl");
    printf("%i entries\n", list2.count);
    for (int i = 0; i < list2.count; i++) {
        printf("Entry: %i - %s\n", list2.entries[i].completed, list2.entries[i].desc);
    }
}

int main(int argc, char *argv[]) {
    struct Subcommand subcommands[] = {
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
