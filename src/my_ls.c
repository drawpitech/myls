/*
** EPITECH PROJECT, 2023
** my_ls
** File description:
** my_ls
*/

#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

#include "my.h"
#include "my_ls.h"

int return_ls_error(char *str)
{
    if (str == NULL) {
        perror("my_ls");
    } else {
        return_err("my_ls: ");
        return_err(str);
        return_err("\n");
    }
    return ERR_RETURN;
}

static
void ls_output(ls_t *ls, bool print_path, uint32_t index)
{
    if (print_path)
        my_printf("%s%s:\n", (index != 0) ? "\n" : "", ls->dir.path);
    if (ls->dir.n_files == 0)
        return;
    sort_files(ls);
    if (ls->params.long_format)
        ls_output_long(ls);
    else
        ls_output_normal(ls);
}

static
int print_dir(ls_t *ls, bool print_path, uint32_t index)
{
    my_strcpy(ls->dir.path, ls->paths[index]);
    if (get_files(ls) == ERR_RETURN) {
        clear_dir(&ls->dir);
        return ERR_RETURN;
    }
    ls_output(ls, print_path, index);
    clear_dir(&ls->dir);
    return 0;
}

int my_ls(int argc, char **argv)
{
    uint32_t uargc = (uint32_t)argc;
    char *paths[uargc + 1];
    ls_t ls = { 0 };
    int ret = 0;

    if (argc < 1 || argv == NULL)
        return return_ls_error("invalid args");
    ls.paths = paths,
    get_params(&ls, uargc, argv);
    if (ls.nbr_paths == 1 || ls.params.directories)
        ret |= print_dir(&ls, false, 0);
    else
        for (uint32_t i = 0; i < ls.nbr_paths; i++)
            ret |= print_dir(&ls, true, i);
    clear_ls(&ls);
    return ret;
}
