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

int get_files_in_dir(struct directory_s *dir, options_t options)
{
    struct dirent *dirent = NULL;
    int ret = 0;

    if (get_dirp(dir) == ERR_RETURN)
        return ERR_RETURN;
    do {
        dirent = readdir(dir->dirp);
        if (dirent == NULL ||
            (!(options & OPT_ALL) && my_str_startswith(dirent->d_name, ".")))
            continue;
        if (dir->n_files + 1 >= dir->allocated) {
            dir->files = my_reallocarray(dir->files, sizeof(struct file_s),
                dir->allocated, (dir->allocated) ? dir->allocated * 2 : 1);
            dir->allocated = (dir->allocated) ? dir->allocated * 2 : 1;
        }
        my_strcpy(dir->files[dir->n_files].filename, dirent->d_name);
        ret |= set_file(dir->path, dir->files + dir->n_files);
        dir->n_files += 1;
    } while (dirent != NULL);
    return ret;
}
