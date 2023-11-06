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
int get_dirp(directory_t *dir)
{
    if (dir == NULL)
        return return_ls_error("null pointer");
    if (dir->dirp != NULL)
        closedir(dir->dirp);
    dir->dirp = opendir(dir->path);
    if (dir->dirp == NULL)
        return return_ls_error(NULL);
    return 0;
}

static
uint32_t get_dir_size(ls_t *ls, directory_t *dir)
{
    struct dirent *directory = NULL;
    uint32_t size = 0;

    if (get_dirp(dir) == ERR_RETURN)
        return UINT32_MAX;
    do {
        directory = readdir(dir->dirp);
        if (directory == NULL)
            continue;
        if (!ls->params.all && my_str_startswith(directory->d_name, "."))
            continue;
        size++;
    } while (directory != NULL);
    return size;
}

static
int get_files_in_dir(ls_t *ls, directory_t *dir)
{
    struct dirent *directory = NULL;

    dir->n_files = get_dir_size(ls, dir);
    if (dir->n_files == UINT32_MAX)
        return ERR_RETURN;
    dir->files = malloc(dir->n_files * sizeof(struct dirent));
    if (get_dirp(dir) == ERR_RETURN)
        return ERR_RETURN;
    for (uint32_t i = 0; i < dir->n_files; i++) {
        directory = readdir(dir->dirp);
        if (!ls->params.all && my_str_startswith(directory->d_name, ".")) {
            i--;
            continue;
        }
        dir->files[i] = *directory;
        my_strcpy(dir->files[i].d_name, directory->d_name);
    }
    return 0;
}

void get_files(ls_t *ls)
{
    if (ls == NULL)
        return;
    for (uint32_t i = 0; i < ls->dir_count; i++) {
        if (get_files_in_dir(ls, ls->directories + i) == 0)
            continue;
        clear_ls(ls);
        exit(ERR_RETURN);
    }
}
