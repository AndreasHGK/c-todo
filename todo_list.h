#pragma once

#include <stdbool.h>

/// A single entry of a todo list.
struct TodoEntry {
    /// The text corresponding to the todo entry.
    char* desc;
    /// Whether the entry has been marked as completed.
    bool completed;
};

/// A todolist struct.
struct TodoList {
    /// The amount of entries.
    int count;
    /// An array of list entries.
    struct TodoEntry* entries;
};

/// Appends a single item to the list. Copies the string into a new location.
void list_append(struct TodoList* list, struct TodoEntry entry);

/// Reads a list from a file into the provided struct's memory location. If this list is already allocated it will be
/// deallocated first. Alternatively, the list content can be NULL. A list with an already freed content pointer should
/// not be provided.
///
/// @param list A pointer to an initialized list location.
/// @param file The file to read from.
bool read_list(struct TodoList* list, const char* file);
/// Writes a list to a file without modifying the provided list.
bool write_list(const struct TodoList* list, const char* file);
