/*
** EPITECH PROJECT, 2023
** my_ls
** File description:
** params
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

void get_params(ls_t *ls, uint32_t argc, char **argv)
{
    if (ls == NULL || argv == NULL || ls->paths == NULL)
        return;
    for (uint32_t i = 1; i < argc; i++) {
        if (argv[i] == NULL)
            return;
        if (argv[i][0] == '-') {
            get_flags(ls, argv[i] + 1);
            continue;
        }
        ls->paths[ls->nbr_paths++] = argv[i];
    }
    if (ls->nbr_paths == 0)
        ls->paths[ls->nbr_paths++] = ".";
    sort_paths(ls->paths, ls->nbr_paths);
}
