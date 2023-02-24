#pragma once

#include "../cmd.h"

/// Subcommand that toggles a task from being uncompleted to completed and the other way around.
int subcommand_toggle(const struct CommandOpts *);
