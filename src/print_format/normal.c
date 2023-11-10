/*
** EPITECH PROJECT, 2023
** my_ls
** File description:
** print
*/

#include <stdint.h>
#include <stdlib.h>

#include "my.h"
#include "my_ls.h"

void ls_output_normal(ls_t *ls)
{
    struct file_s *file;

    if (ls == NULL || ls->dir.files == NULL || ls->dir.n_files == 0)
        return;
    my_printf("%s", ls->dir.files[0].filename);
    for (uint32_t i = 1; i < ls->dir.n_files; i++) {
        file = ls->dir.files + i;
        if (my_strstr(file->filename, " ") == NULL)
            my_printf("  %s", file->filename);
        else
            my_printf("  '%s'", file->filename);
    }
    my_printf("\n");
}
