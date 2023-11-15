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

int set_file(char const *dir_path, char const *file_path, struct file_s *file)
{
    static char fullpath[PATH_MAX];

    my_strcpy(file->filename, file_path);
    if (get_fullpath(dir_path, file->filename, fullpath) == NULL)
        return RET_ERROR;
    if (lstat(fullpath, &file->stat) == -1) {
        file->valid = false;
        return return_ls_error("no such file or directory");
    }
    file->valid = true;
    file->passwd = getpwuid(file->stat.st_uid);
    file->group = getgrgid(file->stat.st_gid);
    return RET_VALID;
}

static
int resize_dir(struct directory_s *dir)
{
    struct file_s *ptr;
    uint32_t new = (dir->allocated) ? dir->allocated * 2 : 1;

    ptr = my_reallocarray(
        dir->files, dir->allocated,
        new, sizeof(struct file_s));
    if (ptr == NULL)
        return return_ls_error("malloc failed");
    dir->files = ptr;
    dir->allocated = new;
    return RET_VALID;
}

int get_files_in_dir(struct directory_s *dir, options_t options)
{
    struct dirent *dirent = NULL;
    int ret = RET_VALID;

    dir->dirp = opendir(dir->path);
    if (dir->dirp == NULL)
        return return_ls_error(NULL);
    do {
        dirent = readdir(dir->dirp);
        if (dirent == NULL ||
        (!(options & OPT_ALL_FILES) && my_str_startswith(dirent->d_name, ".")))
            continue;
        if ((dir->n_files + 1 >= dir->allocated)
            && (resize_dir(dir) == RET_ERROR))
            return RET_ERROR;
        ret |= set_file(dir->path, dirent->d_name, dir->files + dir->n_files);
        dir->n_files += 1;
    } while (dirent != NULL);
    return ret;
}
