/*
** EPITECH PROJECT, 2023
** my_ls
** File description:
** sort_files
*/

#include <stdlib.h>
#include <dirent.h>
#include <stdint.h>
#include <stdio.h>
#include <stdbool.h>

#include "my.h"
#include "my_ls.h"

static
void swap_files(struct dirent **file1, struct dirent **file2)
{
    struct dirent *tmp = *file1;

    *file1 = *file2;
    *file2 = tmp;
}

static
void swap_str(char **file1, char **file2)
{
    char *tmp = *file1;

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
bool my_strcmp_cases(char *str1, char *str2)
{
    static char filename1[256];
    static char filename2[256];

    if (str1 == NULL || str2 == NULL)
        return true;
    my_strcpy(filename1, str1);
    my_strcpy(filename2, str2);
    my_strlowcase(filename1);
    my_strlowcase(filename2);
    return (my_strcmp(get_ptr(filename1), get_ptr(filename2)) > 0);
}

void sort_files(directory_t *dir)
{
    uint32_t size;
    uint32_t x;

    if (dir == NULL || dir->files == NULL || dir->n_files == 0)
        return;
    size = dir->n_files - 1;
    for (uint32_t i = 0; i < size * size; i++) {
        x = i % size;
        if (my_strcmp_cases(dir->files[x]->d_name, dir->files[x + 1]->d_name))
            swap_files(&dir->files[x], &dir->files[x + 1]);
    }
}

void sort_paths(char **paths, uint32_t n)
{
    uint32_t size = n - 1;
    uint32_t x;

    if (paths == NULL)
        return;
    for (uint32_t i = 0; i < size * size; i++) {
        x = i % size;
        if (my_strcmp_cases(paths[x], paths[x + 1]))
            swap_str(paths + x, paths + x + 1);
    }
}
