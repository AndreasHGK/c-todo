#pragma once

#include <stdbool.h>

struct TodoEntry {
    char* desc;
    bool completed;
};

struct TodoList {
    int count;
    struct TodoEntry* entries;
};

void list_append(struct TodoList* list, struct TodoEntry entry);

bool read_list(struct TodoList* list, const char* file);
bool write_list(const struct TodoList* list, const char* file);
