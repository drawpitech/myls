/*
** EPITECH PROJECT, 2023
** bob
** File description:
** bob
*/

#include <stdlib.h>
#include <dirent.h>
#include <stdint.h>
#include <stdio.h>
#include <stdbool.h>

#include "my.h"
#include "my_ls.h"

static
int get_dirp(ls_t *ls)
{
    if (ls == NULL || ls->path == NULL)
        return return_ls_error("null pointer");
    if (ls->dirp != NULL)
        closedir(ls->dirp);
    ls->dirp = opendir(ls->path);
    if (ls->dirp == NULL)
        return return_ls_error(NULL);
    return 0;
}

static
uint32_t get_dir_size(ls_t *ls)
{
    struct dirent *directory = NULL;
    uint32_t size = 0;

    if (get_dirp(ls) == ERR_RETURN)
        return UINT32_MAX;
    do {
        directory = readdir(ls->dirp);
        if (directory == NULL)
            continue;
        if (!ls->show_hidden && my_str_startswith(directory->d_name, "."))
            continue;
        size++;
    } while (directory != NULL);
    return size;
}

int get_files_in_dir(ls_t *ls)
{
    struct dirent *directory = NULL;

    if (ls == NULL)
        return ERR_RETURN;
    ls->n_files = get_dir_size(ls);
    if (ls->n_files == UINT32_MAX)
        return ERR_RETURN;
    ls->files = malloc(ls->n_files * sizeof(struct dirent));
    if (get_dirp(ls) == ERR_RETURN)
        return ERR_RETURN;
    for (uint32_t i = 0; i < ls->n_files; i++) {
        directory = readdir(ls->dirp);
        if (!ls->show_hidden && my_str_startswith(directory->d_name, ".")) {
            i--;
            continue;
        }
        ls->files[i] = *directory;
        my_strcpy(ls->files[i].d_name, directory->d_name);
    }
    return 0;
}
