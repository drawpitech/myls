/*
** EPITECH PROJECT, 2023
** my_ls
** File description:
** get_files
*/

#include <dirent.h>
#include <grp.h>
#include <pwd.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

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
uint32_t get_dir_size(struct directory_s *dir, struct params_s *params)
{
    struct dirent *file = NULL;
    uint32_t size = 0;

    if (get_dirp(dir) == ERR_RETURN)
        return UINT32_MAX;
    do {
        file = readdir(dir->dirp);
        if (file == NULL)
            continue;
        if (!params->all && my_str_startswith(file->d_name, "."))
            continue;
        size++;
    } while (file != NULL);
    return size;
}

int set_file(char *dir_path, struct file_s *file)
{
    static char fullpath[PATH_MAX];

    if (get_fullpath(dir_path, file->filename, fullpath) == NULL)
        return ERR_RETURN;
    if (lstat(fullpath, &file->stat) == -1) {
        file->valid = false;
        return return_ls_error(NULL);
    }
    file->valid = true;
    file->passwd = getpwuid(file->stat.st_uid);
    file->group = getgrgid(file->stat.st_gid);
    return 0;
}

int get_files_in_dir(struct directory_s *dir, struct params_s *params)
{
    struct dirent *dirent = NULL;
    int ret = 0;

    dir->n_files = get_dir_size(dir, params);
    if (dir->n_files == UINT32_MAX)
        return ERR_RETURN;
    dir->files = malloc(dir->n_files * sizeof(struct file_s));
    if (get_dirp(dir) == ERR_RETURN)
        return ERR_RETURN;
    for (uint32_t i = 0; i < dir->n_files;) {
        dirent = readdir(dir->dirp);
        if (!params->all && my_str_startswith(dirent->d_name, "."))
            continue;
        my_strcpy(dir->files[i].filename, dirent->d_name);
        ret |= set_file(dir->path, dir->files + i);
        i += 1;
    }
    return ret;
}
