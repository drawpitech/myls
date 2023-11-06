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
void print_files(ls_t *ls)
{
    if (ls == NULL || ls->files == NULL)
        return;
    for (uint32_t i = 0; i < ls->n_files; i++) {
        my_printf("%s\n", ls->files[i].d_name);
    }
}

void clear_ls(ls_t *ls)
{
    if (ls == NULL)
        return;
    if (ls->dirp != NULL) {
        closedir(ls->dirp);
        ls->dirp = NULL;
    }
    if (ls->files != NULL) {
        free(ls->files);
        ls->files = NULL;
    }
}

int my_ls(int argc, char **argv)
{
    ls_t ls = {
        .path = NULL,
        .dirp = NULL,
        .files = NULL,
        .n_files = 0,
        .params = { 0 },
    };

    get_params(&ls, argc, argv);
    if (ls.path == NULL)
        ls.path = ".";
    if (get_files_in_dir(&ls) == ERR_RETURN) {
        clear_ls(&ls);
        return ERR_RETURN;
    }
    sort_files(&ls);
    print_files(&ls);
    clear_ls(&ls);
    return 0;
}
