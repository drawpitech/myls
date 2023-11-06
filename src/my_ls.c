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
    const char *path = (argc < 2) ? "." : argv[1];
    ls_t ls = {
        .path = path,
        .dirp = NULL,
        .show_hidden = false,
        .files = NULL,
        .n_files = 0,
    };

    if (get_files_in_dir(&ls) == ERR_RETURN) {
        clear_ls(&ls);
        return ERR_RETURN;
    }
    print_files(&ls);
    clear_ls(&ls);
    return 0;
}
