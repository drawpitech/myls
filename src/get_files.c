/*
** EPITECH PROJECT, 2023
** my_ls
** File description:
** get_files
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

int get_files_in_dir(ls_t *ls)
{
    struct dirent *directory = NULL;
    directory_t *dir = &ls->directories;
    uint32_t i = 0;

    dir->n_files = get_dir_size(ls, dir);
    if (dir->n_files == UINT32_MAX)
        return ERR_RETURN;
    dir->files = malloc(dir->n_files * sizeof(struct dirent *));
    if (get_dirp(dir) == ERR_RETURN)
        return ERR_RETURN;
    while (i < dir->n_files) {
        directory = readdir(dir->dirp);
        if (!ls->params.all && my_str_startswith(directory->d_name, "."))
            continue;
        dir->files[i] = directory;
        i++;
    }
    return 0;
}
