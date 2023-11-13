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
#include "sys/stat.h"

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
void add_param(char *param, ls_t *ls)
{
    static struct stat file_stat;

    if (param == NULL)
        return;
    if (param[0] == '-') {
        get_flags(ls, param + 1);
        return;
    }
    if (stat(param, &file_stat) == -1 || !S_ISDIR(file_stat.st_mode)) {
        ls->alone_files.paths[ls->alone_files.n] = param;
        ls->alone_files.n += 1;
        return;
    }
    ls->paths.paths[ls->paths.n] = param;
    ls->paths.n += 1;
}

void get_params(ls_t *ls, uint32_t argc, char **argv)
{
    if (ls == NULL || argv == NULL
        || ls->paths.paths == NULL
        || ls->alone_files.paths == NULL)
        return;
    for (uint32_t i = 1; i < argc; i++)
        add_param(argv[i], ls);
    if (ls->params.directories) {
        for (uint32_t i = 0; i < ls->paths.n; i++) {
            ls->alone_files.paths[ls->alone_files.n] = ls->paths.paths[i];
            ls->alone_files.n += 1;
        }
        ls->paths.n = 0;
    } else if (ls->paths.n == 0 && ls->alone_files.n == 0) {
        ls->paths.paths[ls->paths.n] = ".";
        ls->paths.n = 1;
    }
    sort_paths(&ls->paths);
    sort_paths(&ls->alone_files);
}
