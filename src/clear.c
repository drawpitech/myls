/*
** EPITECH PROJECT, 2023
** my_ls
** File description:
** clear
*/

#include <stdlib.h>

#include "my_ls.h"

void clear_dir(directory_t *dir)
{
    if (dir == NULL)
        return;
    if (dir->dirp != NULL) {
        closedir(dir->dirp);
        dir->dirp = NULL;
    }
    if (dir->files != NULL) {
        free(dir->files);
        dir->files = NULL;
    }
    dir->n_files = 0;
    dir->path[0] = '\0';
}

void clear_ls(ls_t *ls)
{
    if (ls == NULL)
        return;
    ls->nbr_paths = 0;
    ls->paths = NULL;
    ls->params = (struct params_s){0};
    clear_dir(&ls->directories);
}
