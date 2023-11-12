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

static
void show_file(struct file_s *file, bool *first)
{
    char *pad = (*first) ? "" : "  ";

    if (!file->valid)
        return;
    *first = false;
    if (my_strstr(file->filename, " ") == NULL)
        my_printf("%s%s", pad, file->filename);
    else
        my_printf("%s'%s'", pad, file->filename);
}

void ls_output_normal(struct directory_s *dir)
{
    bool first = true;

    if (dir == NULL || dir->files == NULL || dir->n_files == 0)
        return;
    for (uint32_t i = 0; i < dir->n_files; i++)
        show_file(dir->files + i, &first);
    if (!first)
        my_printf("\n");
}
