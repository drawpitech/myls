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
    directory_t *dir = &ls->directories;

    for (uint32_t i = 0; i < dir->n_files; i++)
        my_printf("%s  ", dir->files[i]->d_name);
    my_printf("\n");
}
