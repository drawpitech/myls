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
void print_dir(directory_t *dir, bool print_path, uint32_t index)
{
    if (print_path) {
        if (index != 0)
            my_printf("\n");
        my_printf("%s:\n", dir->path);
    }
    for (uint32_t i = 0; i < dir->n_files; i++)
        my_printf("%s\n", dir->files[i].d_name);
}

static
void print_files(ls_t *ls)
{
    if (ls->dir_count == 1) {
        print_dir(ls->directories, false, 0);
        return;
    }
    for (uint32_t i = 0; i < ls->dir_count; i++)
        print_dir(ls->directories + i, true, i);
}

void clear_ls(ls_t *ls)
{
    if (ls == NULL)
        return;
    for (uint32_t i = 0; i < ls->dir_count; i++) {
        if (ls->directories[i].dirp != NULL) {
            closedir(ls->directories[i].dirp);
            ls->directories[i].dirp = NULL;
        }
        if (ls->directories[i].files != NULL) {
            free(ls->directories[i].files);
            ls->directories[i].files = NULL;
        }
    }
    if (ls->directories != NULL)
        free(ls->directories);
}

int my_ls(int argc, char **argv)
{
    ls_t ls = {
        .directories = NULL,
        .dir_count = 0,
        .params = { 0 },
    };

    if (argc < 1 || argv == NULL)
        return return_ls_error("invalid args\n");
    get_params(&ls, (uint32_t)argc, argv);
    get_files(&ls);
    for (uint32_t i = 0; i < ls.dir_count; i++)
        sort_files(ls.directories + i);
    print_files(&ls);
    clear_ls(&ls);
    return 0;
}
