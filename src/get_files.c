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
int get_dirp(struct directory_s *dir)
{
    if (dir->dirp != NULL)
        closedir(dir->dirp);
    dir->dirp = opendir(dir->path);
    if (dir->dirp == NULL)
        return return_ls_error(NULL);
    return 0;
}

static
uint32_t get_dir_size(ls_t *ls)
{
    struct dirent *directory = NULL;
    uint32_t size = 0;

    if (get_dirp(&ls->dir) == ERR_RETURN)
        return UINT32_MAX;
    do {
        directory = readdir(ls->dir.dirp);
        if (directory == NULL)
            continue;
        if (!ls->params.all && my_str_startswith(directory->d_name, "."))
            continue;
        size++;
    } while (directory != NULL);
    return size;
}

static
void set_file(char *dir_path, struct file_s *file, struct dirent *dirent)
{
    file->dirent = dirent;
    my_strcpy(file->fullpath, dir_path);
    if (dir_path[my_strlen(dir_path) - 1] != '/')
        my_strcat(file->fullpath, "/");
    my_strcat(file->fullpath, file->dirent->d_name);
    lstat(file->fullpath, &file->stat);
}

int get_files_in_dir(ls_t *ls)
{
    struct dirent *dirent = NULL;

    if (ls == NULL)
        return return_ls_error("null pointer");
    ls->dir.n_files = get_dir_size(ls);
    if (ls->dir.n_files == UINT32_MAX)
        return ERR_RETURN;
    ls->dir.files = malloc(ls->dir.n_files * sizeof(struct file_s));
    if (get_dirp(&ls->dir) == ERR_RETURN)
        return ERR_RETURN;
    for (uint32_t i = 0; i < ls->dir.n_files;) {
        dirent = readdir(ls->dir.dirp);
        if (!ls->params.all && my_str_startswith(dirent->d_name, "."))
            continue;
        set_file(ls->dir.path, &ls->dir.files[i++], dirent);
    }
    return 0;
}
