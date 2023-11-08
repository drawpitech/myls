/*
** EPITECH PROJECT, 2023
** my_ls
** File description:
** print
*/

#include <pwd.h>
#include <stdint.h>
#include <stdlib.h>
#include <sys/types.h>
#include <grp.h>

#include "my.h"
#include "my_ls.h"

void ls_output_long(ls_t *ls)
{
    struct file_s file;

    if (ls == NULL || ls->dir.files == NULL || ls->dir.n_files == 0)
        return;
    for (uint32_t i = 0; i < ls->dir.n_files; i++) {
        file = ls->dir.files[i];
        my_printf("%u ", file.stat.st_nlink);
        my_printf("%s ", file.passwd->pw_name);
        my_printf("%s ", file.group->gr_name);
        my_printf("%6u ", file.stat.st_size);
        my_printf("%s\n", file.dirent->d_name);
    }
}
