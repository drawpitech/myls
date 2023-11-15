/*
** EPITECH PROJECT, 2023
** my_ls
** File description:
** print
*/

#include <stdint.h>
#include <stdlib.h>

#include "my.h"

#include "../my_ls.h"
#include "print.h"

static
void show_file(struct file_s const *file, bool *first, options_t options)
{
    if (!file->valid)
        return;
    my_printf("%s", (*first) ? "" : "  ");
    *first = false;
    print_filename(file, options);
}

void ls_output_normal(struct directory_s const *dir, options_t options)
{
    bool first = true;

    if (dir == NULL || dir->files == NULL || dir->n_files == 0)
        return;
    for (uint32_t i = 0; i < dir->n_files; i++)
        show_file(dir->files + i, &first, options);
    if (!first)
        my_printf("\n");
}
