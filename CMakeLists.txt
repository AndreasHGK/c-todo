cmake_minimum_required(VERSION 3.24)
project(c-todo C)

set(CMAKE_C_STANDARD 23)

add_executable(c-todo
        subcommands/add.c
        subcommands/add.h
        subcommands/list.c
        subcommands/list.h
        subcommands/toggle.c
        subcommands/toggle.h

        cmd.h
        cmd.c
        todo_list.h
        todo_list.c

        main.c
        )
