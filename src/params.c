/*
** EPITECH PROJECT, 2023
** bob
** File description:
** bob
*/

#include <stdint.h>
#include <stdlib.h>

#include "my.h"
#include "my_ls.h"

static
int set_flag(char c, arg_t *arr)
{
    for (uint32_t i = 0; arr[i].b != NULL; i++) {
        if (arr[i].c == c) {
            *arr[i].b = true;
            return 0;
        }
    }
    return return_ls_error("invalid option\n");
}

static
void get_flags(ls_t *ls, char *str)
{
    arg_t arr[] = {
        {'a', &ls->params.all},
        {'l', &ls->params.long_format},
        {'r', &ls->params.reverse},
        {'R', &ls->params.recursive},
        {'t', &ls->params.time_sorted},
        {'d', &ls->params.directories},
        {'\0', NULL},
    };

    for (; *str; str++) {
        if (set_flag(*str, arr) == ERR_RETURN) {
            clear_ls(ls);
            exit(ERR_RETURN);
        }
    }
}

static
void init_directories(ls_t *ls, char **paths, uint32_t size)
{
    ls->directories = malloc(size * sizeof(directory_t));
    if (ls->directories == NULL) {
        clear_ls(ls);
        exit(return_ls_error("malloc failed"));
    }
    ls->dir_count = size;
    for (uint32_t i = 0; i < size; i++) {
        ls->directories[i] = (directory_t){ 0 };
        my_strcpy(ls->directories[i].path, paths[i]);
    }
}

void get_params(ls_t *ls, uint32_t argc, char **argv)
{
    char *paths[argc + 1];
    uint32_t index = 0;

    if (ls == NULL || argv == NULL)
        return;
    for (uint32_t i = 1; i < argc; i++) {
        if (argv[i] == NULL)
            return;
        if (argv[i][0] == '-') {
            get_flags(ls, argv[i] + 1);
            continue;
        }
        paths[index++] = argv[i];
    }
    if (index == 0)
        paths[index++] = ".";
    init_directories(ls, paths, index);
}
