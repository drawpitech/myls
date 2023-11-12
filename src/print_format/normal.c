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

void ls_output_normal(struct directory_s *dir)
{
    struct file_s *file;

    if (dir == NULL || dir->files == NULL)
        return;
    my_printf("%s", dir->files[0].filename);
    for (uint32_t i = 1; i < dir->n_files; i++) {
        file = dir->files + i;
        if (my_strstr(file->filename, " ") == NULL)
            my_printf("  %s", file->filename);
        else
            my_printf("  '%s'", file->filename);
    }
    my_printf("\n");
}
