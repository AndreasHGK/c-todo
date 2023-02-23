#pragma once

/// A struct containing the options passed via the command line.
struct CommandOpts {
    /// The file to read the todolist from.
    const char *filepath;
};

/// Parses the command line arguments into a CommandOpts struct.
void parse_opts(struct CommandOpts *, int argc, char *argv[]);
