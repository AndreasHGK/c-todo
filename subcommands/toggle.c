#include "toggle.h"

#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "../todo_list.h"

int subcommand_toggle(const struct CommandOpts *opts) {
    struct TodoList list = {};
    if (!read_list(&list, opts->filepath)) {
        fprintf(stderr, "Could not read file `%s` or it does not exist.\n", opts->filepath);
        return 1;
    }

    printf("Enter the entry number you want to toggle: ");
    char buf[8];
    scanf("%s", buf);

    errno = 0;
    long entry_num = strtol(buf, NULL, 10);
    if (errno != 0) {
        fprintf(stderr, "Could not parse `%s` as an integer.\n", buf);
        return 1;
    }

    if (entry_num >= list.count || entry_num < 0) {
        fprintf(stderr, "That entry does not exist!\n");
        return 1;
    }

    list.entries[entry_num].completed = !list.entries[entry_num].completed;
    printf("Success! The following entry has been marked as %s:\n`%s`\n",
           list.entries[entry_num].completed ? "completed" : "incomplete", list.entries[entry_num].desc);

    write_list(&list, opts->filepath);
    return 0;
}
