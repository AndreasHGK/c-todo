#include "todo_list.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

bool read_list(struct TodoList *list, const char *file) {
    list->count = 0;
    free(list->entries);
    list->entries = NULL;

    FILE *fp;
    fp = fopen(file, "r");
    if (fp == NULL) return false;

    // Version byte
    if (fgetc(fp) != 1) {
        return false;
    }

    struct TodoEntry *entry;
    while (true) {
        int byte = fgetc(fp);
        if (byte == '\0') break;

        list->count++;
        list->entries = realloc(list->entries, sizeof(struct TodoEntry) * list->count);

        entry = &list->entries[list->count - 1];
        entry->completed = byte == '1';

        unsigned int textLen = fgetc(fp);
        entry->desc = malloc(sizeof(char) * textLen + 1);

        for (int i = 0; i < textLen; i++) {
            entry->desc[i] = (char)fgetc(fp);
        }
        entry->desc[textLen] = '\0';
    }
    fclose(fp);
    return true;
}

bool write_list(const struct TodoList *list, const char *file) {
    FILE *fp;
    fp = fopen(file, "w");

    // Write version
    fputc(1, fp);

    for (int i = 0; i < list->count; i++) {
        const struct TodoEntry* entry = &list->entries[i];
        if (entry->completed) {
            fputc('1', fp);
        } else {
            fputc('0', fp);
        }

        int d_size = (int)strlen(entry->desc);
        fputc(d_size, fp);
        for (int x = 0; x < d_size; x++) {
            fputc(entry->desc[x], fp);
        }
    }
    fputc('\0', fp);
    fflush(fp);
    fclose(fp);
    return true;
}

void list_append(struct TodoList *list, struct TodoEntry entry) {
    list->count++;
    list->entries = realloc(list->entries, sizeof(struct TodoEntry) * list->count);
    list->entries[list->count - 1].completed = entry.completed;
    list->entries[list->count - 1].desc = malloc(strlen(entry.desc));
    strcpy(list->entries[list->count - 1].desc, entry.desc);
}
