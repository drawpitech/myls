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

static
void get_max_size(ls_t *ls, int arr[4])
{
    struct file_s *file;

    for (uint32_t i = 0; i < ls->dir.n_files; i++) {
        file = ls->dir.files + i;
        arr[0] = MAX(arr[0], my_nbr_len(file->stat.st_nlink));
        arr[1] = MAX(arr[1], my_strlen(file->passwd->pw_name));
        arr[2] = MAX(arr[2], my_strlen(file->group->gr_name));
        arr[3] = MAX(arr[3], my_nbr_len(file->stat.st_size));
    }
}

static
void show_long_formatting(ls_t *ls)
{
    struct file_s *file;
    int max_size[4] = {0};

    get_max_size(ls, max_size);
    for (uint32_t i = 0; i < ls->dir.n_files; i++) {
        file = ls->dir.files + i;
        my_putnchar(' ', max_size[0] - my_nbr_len(file->stat.st_nlink));
        my_printf("%u ", file->stat.st_nlink);
        my_putnchar(' ', max_size[1] - my_strlen(file->passwd->pw_name));
        my_printf("%s ", file->passwd->pw_name);
        my_putnchar(' ', max_size[2] - my_strlen(file->group->gr_name));
        my_printf("%s ", file->group->gr_name);
        my_putnchar(' ', max_size[3] - my_nbr_len(file->stat.st_size));
        my_printf("%u ", file->stat.st_size);
        my_printf("%s\n", file->dirent->d_name);
    }
}

void ls_output_long(ls_t *ls)
{
    if (ls == NULL || ls->dir.files == NULL || ls->dir.n_files == 0)
        return;
    show_long_formatting(ls);
}
