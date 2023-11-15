/*
** EPITECH PROJECT, 2023
** my_ls
** File description:
** long
*/

#ifndef LS_LONG_H_
    #define LS_LONG_H_

    #include <stdbool.h>
    #include <sys/stat.h>

    #include "../my_ls.h"
    #include "colors.h"

    #define PERMS_SIZE (9)

/**
 * Print the file name with the correct modfiers.
 * Ex: 'foo bar'
 */
void print_filename(
    struct directory_s const *dir,
    struct file_s const *file,
    options_t options);

static inline
bool color_dir(
    __attribute__((__unused__)) struct directory_s const *dir,
    __attribute__((__unused__)) struct file_s const *file)
{
    if (file->stat.st_mode & S_ISVTX) {
        if (file->stat.st_mode & S_IWOTH)
            put_color(C_BLK, C_BOLD, C_GRN);
        else
            put_color(C_BLU, C_BOLD, C_BLK);
    } else {
        if (file->stat.st_mode & S_IWOTH)
            put_color(C_BLU, C_BOLD, C_GRN);
        else
            put_color(C_BLU, C_BOLD, 0);
    }
    return true;
}

static inline
bool color_chr(
    __attribute__((__unused__)) struct directory_s const *dir,
    __attribute__((__unused__)) struct file_s const *file)
{
    put_color(C_YEL, C_BOLD, C_BLK);
    return true;
}

static inline
bool color_lnk(
    __attribute__((__unused__)) struct directory_s const *dir,
    __attribute__((__unused__)) struct file_s const *file)
{
    static struct stat file_stat;
    static char fullpath[PATH_MAX];

    get_fullpath(dir->path, file->filename, fullpath);
    if (stat(fullpath, &file_stat) == -1)
        put_color(C_RED, C_BOLD, C_BLK);
    else
        put_color(C_CYN, C_BOLD, 0);
    return true;
}

static inline
bool color_reg(
    __attribute__((__unused__)) struct directory_s const *dir,
    __attribute__((__unused__)) struct file_s const *file)
{
    if (file->stat.st_mode & S_IXUSR) {
        put_color(C_GRN, C_BOLD, 0);
        return true;
    }
    return false;
}

static inline
bool color_sock(
    __attribute__((__unused__)) struct directory_s const *dir,
    __attribute__((__unused__)) struct file_s const *file)
{
    put_color(C_MAG, C_BOLD, 0);
    return true;
}

static inline
bool color_ifo(
    __attribute__((__unused__)) struct directory_s const *dir,
    __attribute__((__unused__)) struct file_s const *file)
{
    put_color(C_YEL, C_BOLD, 0);
    return true;
}

static const struct {
    char c;
    bool (*func)(struct directory_s const *, struct file_s const *);
} FT_TABLE[] = {
    [S_IFBLK] = {'b', &color_chr},
    [S_IFCHR] = {'c', &color_chr},
    [S_IFDIR] = {'d', &color_dir},
    [S_IFIFO] = {'i', &color_ifo},
    [S_IFLNK] = {'l', &color_lnk},
    [S_IFREG] = {'-', &color_reg},
    [S_IFSOCK] = {'s', NULL},
    [0] = {'?', NULL},
};

#endif /* LS_LONG_H_ */
