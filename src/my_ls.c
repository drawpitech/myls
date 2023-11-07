/*
** EPITECH PROJECT, 2023
** bob
** File description:
** bo
*/

#include <stdlib.h>
#include <dirent.h>
#include <stdint.h>
#include <stdio.h>
#include <stdbool.h>

#include "my.h"
#include "my_ls.h"

int return_ls_error(char *str)
{
    if (str == NULL)
        perror("my_ls");
    else
        my_printf("my_ls: %s", str);
    return ERR_RETURN;
}

static
void print_dir(ls_t *ls, bool print_path, uint32_t index)
{
    directory_t *dir = &ls->directories;

    my_strcpy(dir->path, ls->paths[index]);
    get_files_in_dir(ls);
    sort_files(dir);
    if (print_path) {
        if (index != 0)
            my_printf("\n");
        my_printf("%s:\n", dir->path);
    }
    for (uint32_t i = 0; i < dir->n_files; i++)
        my_printf("%s\n", dir->files[i].d_name);
    clear_dir(dir);
}

int my_ls(int argc, char **argv)
{
    uint32_t uargc = (uint32_t)argc;
    char *paths[uargc + 1];
    ls_t ls = {
        .directories = { .path = { 0 }, 0 },
        .paths = paths,
        .nbr_paths = 0,
        .params = { 0 },
    };
    bool ret = false;

    if (argc < 1 || argv == NULL)
        return return_ls_error("invalid args\n");
    get_params(&ls, uargc, argv);
    if (ls.nbr_paths == 1)
        print_dir(&ls, false, 0);
    else
        for (uint32_t i = 0; i < ls.nbr_paths; i++)
            print_dir(&ls, true, i);
    clear_ls(&ls);
    return (ret) ? ERR_RETURN : 0;
}
