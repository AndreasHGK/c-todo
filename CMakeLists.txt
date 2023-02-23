cmake_minimum_required(VERSION 3.24)
project(c-todo C)

set(CMAKE_C_STANDARD 23)

add_executable(c-todo main.c cmd.h cmd.c subcommands/list.c subcommands/list.h todo_list.h todo_list.c)
