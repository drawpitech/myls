/*
** EPITECH PROJECT, 2023
** my_ls
** File description:
** clear
*/

#include <stdlib.h>

#include "my_ls.h"

void clear_dir(struct directory_s *dir)
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
    dir->allocated = 0;
    dir->path[0] = '\0';
}

static
void clear_paths(struct paths_s *paths)
{
    paths->n = 0;
    paths->paths = NULL;
}

void clear_ls(ls_t *ls)
{
    if (ls == NULL)
        return;
    ls->options = 0;
    clear_paths(&ls->paths);
    clear_paths(&ls->alone_files);
    clear_dir(&ls->dir);
}
