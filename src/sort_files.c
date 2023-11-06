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
char *get_ptr(char *filename)
{
    while (*filename == '.')
        filename++;
    return filename;
}

static
bool file_is_upper(struct dirent *file1, struct dirent *file2)
{
    static char filename1[256];
    static char filename2[256];

    if (file1 == NULL || file2 == NULL)
        return true;
    my_strcpy(filename1, file1->d_name);
    my_strcpy(filename2, file2->d_name);
    my_strlowcase(filename1);
    my_strlowcase(filename2);
    return (my_strcmp(get_ptr(filename1), get_ptr(filename2)) > 0);
}

void sort_files(ls_t *ls)
{
    uint32_t size;
    uint32_t x;

    if (ls == NULL || ls->files == NULL)
        return;
    size = ls->n_files - 1;
    for (uint32_t i = 0; i < size * size; i++) {
        x = i % size;
        if (file_is_upper(ls->files + x, ls->files + x + 1))
            swap_files(ls->files + x, ls->files + x + 1);
    }
}
