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

void ls_output_long(ls_t *ls)
{
    if (ls == NULL)
        return;
    for (uint32_t i = 0; i < ls->dir.n_files; i++)
        my_printf("%s\n", ls->dir.files[i]->d_name);
}
