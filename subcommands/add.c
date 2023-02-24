#include "add.h"

#include <stdio.h>
#include <string.h>

#include "../todo_list.h"

int subcommand_add(const struct CommandOpts *opts) {
    struct TodoList list = {};
    if (!read_list(&list, opts->filepath)) {
        printf("Generating a new file: `%s`\n", opts->filepath);
    }

    char str_buf[64];
    printf("Please enter your new task:\n");
    if (!fgets(str_buf, sizeof(str_buf), stdin)) {
        fprintf(stderr, "Please enter a valid task.\n");
        return 1;
    }
    // Remove the newline at the end of the string.
    size_t str_len = strlen(str_buf);
    str_buf[str_len - 1] = '\0';

    list_append(&list, (struct TodoEntry) {
        .completed = false,
        .desc = str_buf,
    });

    printf("Added new todo entry: `%s`", str_buf);
    write_list(&list, opts->filepath);
    return 0;
}
