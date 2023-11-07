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
}

void clear_ls(ls_t *ls)
{
    if (ls == NULL)
        return;
    clear_dir(&ls->directories);
}
