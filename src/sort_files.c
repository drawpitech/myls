/*
** EPITECH PROJECT, 2023
** my_ls
** File description:
** sort_files
*/

#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

#include "my.h"
#include "my_ls.h"

static
void swap_files(struct file_s *file1, struct file_s *file2)
{
    struct file_s tmp = *file1;

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
    static char filename1[PATH_MAX];
    static char filename2[PATH_MAX];

    if (str1 == NULL || str2 == NULL)
        return true;
    my_strcpy(filename1, str1);
    my_strcpy(filename2, str2);
    my_strlowcase(filename1);
    my_strlowcase(filename2);
    return (my_strcmp(get_ptr(filename1), get_ptr(filename2)) > 0);
}

static
void reverse_files(struct directory_s *dir)
{
    struct file_s *f = dir->files;

    for (uint32_t i = 0; i < dir->n_files / 2; i++)
        swap_files(f + i, f + (dir->n_files - 1 - i));
}

static
void sort_alpha_files(struct directory_s *dir)
{
    uint32_t size = dir->n_files - 1;
    struct file_s *f = dir->files;
    uint32_t x;

    for (uint32_t i = 0; i < size * size; i++) {
        x = i % size;
        if (my_strcmp_cases(f[x].filename, f[x + 1].filename))
            swap_files(f + x, f + x + 1);
    }
}

static
void sort_time_files(struct directory_s *dir)
{
    uint32_t size = dir->n_files - 1;
    struct file_s *f = dir->files;
    uint32_t x;

    for (uint32_t i = 0; i < size * size; i++) {
        x = i % size;
        if (f[x].stat.st_mtim.tv_sec < f[x + 1].stat.st_mtim.tv_sec)
            swap_files(f + x, f + x + 1);
    }
}

void sort_files(ls_t *ls)
{
    if (ls == NULL || ls->dir.files == NULL || ls->dir.n_files == 0)
        return;
    if (ls->params.time_sorted)
        sort_time_files(&ls->dir);
    else
        sort_alpha_files(&ls->dir);
    if (ls->params.reverse)
        reverse_files(&ls->dir);
}

void sort_paths(char **paths, uint32_t n)
{
    uint32_t size = n - 1;
    uint32_t x;

    if (paths == NULL || n == 0)
        return;
    for (uint32_t i = 0; i < size * size; i++) {
        x = i % size;
        if (my_strcmp_cases(paths[x], paths[x + 1]))
            swap_str(paths + x, paths + x + 1);
    }
}
