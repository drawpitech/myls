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

int set_file(char *dir_path, char *file_path, struct file_s *file)
{
    static char fullpath[PATH_MAX];

    my_strcpy(file->filename, file_path);
    if (get_fullpath(dir_path, file->filename, fullpath) == NULL)
        return ERR_RETURN;
    if (lstat(fullpath, &file->stat) == -1) {
        file->valid = false;
        return ERR_RETURN;
    }
    file->valid = true;
    file->passwd = getpwuid(file->stat.st_uid);
    file->group = getgrgid(file->stat.st_gid);
    return 0;
}

static
int resize_dir(struct directory_s *dir)
{
    struct file_s *ptr;
    uint32_t new = (dir->allocated) ? dir->allocated * 2 : 1;

    ptr = my_reallocarray(
        dir->files, sizeof(struct file_s),
        dir->allocated, new);
    if (ptr == NULL)
        return return_ls_error("malloc failed");
    dir->files = ptr;
    dir->allocated = new;
    return 0;
}

int get_files_in_dir(struct directory_s *dir, options_t options)
{
    struct dirent *dirent = NULL;
    int ret = 0;

    dir->dirp = opendir(dir->path);
    if (dir->dirp == NULL)
        return return_ls_error(NULL);
    do {
        dirent = readdir(dir->dirp);
        if (dirent == NULL ||
            (!(options & OPT_ALL) && my_str_startswith(dirent->d_name, ".")))
            continue;
        if ((dir->n_files + 1 >= dir->allocated)
            && (resize_dir(dir) == ERR_RETURN))
            return ERR_RETURN;
        ret |= set_file(dir->path, dirent->d_name, dir->files + dir->n_files);
        dir->n_files += 1;
    } while (dirent != NULL);
    return ret;
}
