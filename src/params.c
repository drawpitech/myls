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
int set_flag(ls_t *ls, char c)
{
    for (uint32_t i = 0; OPTIONS[i].bit_mask != 0; i++) {
        if (OPTIONS[i].c == c) {
            ls->options |= OPTIONS[i].bit_mask;
            return 0;
        }
    }
    return return_ls_error("invalid option\n");
}

static
void get_smol_option(ls_t *ls, char *str)
{
    for (; *str; str++) {
        if (set_flag(ls, *str) == ERR_RETURN) {
            clear_ls(ls);
            exit(ERR_RETURN);
        }
    }
}

static
void get_big_option(ls_t *ls, char *str)
{
    for (uint32_t i = 0; OPTIONS[i].bit_mask != 0; i++) {
        if (OPTIONS[i].word != NULL && my_strcmp(OPTIONS[i].word, str) == 0) {
            ls->options |= OPTIONS[i].bit_mask;
            return;
        }
    }
    exit(return_ls_error("invalid option\n"));
}

static
void add_param(char *param, ls_t *ls)
{
    static struct stat file_stat;

    if (param == NULL || param[0] == '\0')
        exit(return_ls_error("invalid option\n"));
    if (my_strncmp(param, "--", 2) == 0) {
        get_big_option(ls, param + 2);
        return;
    }
    if (param[0] == '-') {
        get_smol_option(ls, param + 1);
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
    if (ls->paths.n == 0 && ls->alone_files.n == 0) {
        ls->paths.paths[ls->paths.n] = ".";
        ls->paths.n = 1;
    }
    if (ls->options & OPT_DIRECTORY) {
        for (uint32_t i = 0; i < ls->paths.n; i++) {
            ls->alone_files.paths[ls->alone_files.n] = ls->paths.paths[i];
            ls->alone_files.n += 1;
        }
        ls->paths.n = 0;
    }
    sort_paths(&ls->paths);
    sort_paths(&ls->alone_files);
}
