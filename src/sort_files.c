/*
** EPITECH PROJECT, 2023
** bob
** File description:
** bob
*/

#include <stdlib.h>
#include <dirent.h>
#include <stdint.h>
#include <stdio.h>
#include <stdbool.h>

#include "my.h"
#include "my_ls.h"

static
void swap_files(struct dirent *file1, struct dirent *file2)
{
    struct dirent tmp = *file1;

    *file1 = *file2;
    *file2 = tmp;
}

static
bool file_is_upper(struct dirent *file1, struct dirent *file2)
{
    char filename1[256];
    char filename2[256];

    if (file1 == NULL || file2 == NULL)
        return true;
    my_strcpy(filename1, file1->d_name);
    my_strcpy(filename2, file2->d_name);
    my_strlowcase(filename1);
    my_strlowcase(filename2);
    return (my_strcmp(filename1, filename2) > 0);
}

static
void bubble_sort_list(ls_t *ls)
{
    for (uint32_t i = 0; i < ls->n_files - 1; i++)
        if (file_is_upper(ls->files + i, ls->files + i + 1))
            swap_files(ls->files + i, ls->files + i + 1);
}

void sort_files(ls_t *ls)
{
    if (ls == NULL || ls->files == NULL)
        return;
    for (uint32_t i = 0; i < ls->n_files - 1; i++)
        bubble_sort_list(ls);
}
