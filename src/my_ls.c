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
int print_dir(ls_t *ls, bool show_path, bool line_jmp, struct directory_s *dir)
{
    if (get_files(dir, &ls->params) == ERR_RETURN) {
        clear_dir(dir);
        return ERR_RETURN;
    }
    if (show_path)
        my_printf("%s%s:\n", (line_jmp) ? "\n" : "", ls->dir.path);
    if (dir->n_files == 0)
        return 0;
    sort_files(ls);
    if (ls->params.long_format)
        ls_output_long(dir, &ls->params);
    else
        ls_output_normal(dir);
    clear_dir(&ls->dir);
    return 0;
}

static
int print_ls(ls_t *ls)
{
    int ret = 0;

    if (ls->nbr_paths == 1 || ls->params.directories) {
        my_strcpy(ls->dir.path, ls->paths[0]);
        return print_dir(ls, false, false, &ls->dir);
    }
    for (uint32_t i = 0; i < ls->nbr_paths; i++) {
        my_strcpy(ls->dir.path, ls->paths[i]);
        ret |= print_dir(ls, true, (i != 0), &ls->dir);
    }
    return ret;
}

int my_ls(int argc, char **argv)
{
    uint32_t uargc = (uint32_t)argc;
    char *paths[uargc];
    ls_t ls = { 0 };
    int ret = 0;

    if (argc < 1 || argv == NULL)
        return return_ls_error("invalid args");
    ls.paths = paths,
    get_params(&ls, uargc, argv);
    ret |= print_ls(&ls);
    clear_ls(&ls);
    return ret;
}
