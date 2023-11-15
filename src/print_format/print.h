/*
** EPITECH PROJECT, 2023
** my_ls
** File description:
** long
*/

#ifndef LS_LONG_H_
    #define LS_LONG_H_

    #include <sys/stat.h>

    #include "../my_ls.h"

    #define PERMS_SIZE (9)

static const char FT_TABLE[] = {
    [S_IFBLK] = 'b',
    [S_IFCHR] = 'c',
    [S_IFDIR] = 'd',
    [S_IFIFO] = 'i',
    [S_IFLNK] = 'l',
    [S_IFREG] = '-',
    [S_IFSOCK] = 's',
    [0] = '?',
};

/**
 * Print the file name with the correct modfiers.
 * Ex: 'foo bar'
 */
void print_filename(struct file_s const *file, options_t options);

#endif /* LS_LONG_H_ */
