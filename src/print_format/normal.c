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
    if (ls == NULL || ls->dir.n_files == 0)
        return;
    my_printf("%s", ls->dir.files[0]->d_name);
    for (uint32_t i = 1; i < ls->dir.n_files; i++)
        my_printf("  %s", ls->dir.files[i]->d_name);
    my_printf("\n");
}
