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
        if (f[x].stat.st_mtim.tv_sec < f[x + 1].stat.st_mtim.tv_sec) {
            swap_files(f + x, f + x + 1);
            continue;
        }
        if (
            (f[x].stat.st_mtim.tv_sec == f[x + 1].stat.st_mtim.tv_sec)
            && (f[x].stat.st_mtim.tv_nsec < f[x + 1].stat.st_mtim.tv_nsec)
        ) {
            swap_files(f + x, f + x + 1);
            continue;
        }
    }
}

static
void sort_access_time_files(struct directory_s *dir)
{
    uint32_t size = dir->n_files - 1;
    struct file_s *f = dir->files;
    uint32_t x;

    for (uint32_t i = 0; i < size * size; i++) {
        x = i % size;
        if (f[x].stat.st_atim.tv_sec < f[x + 1].stat.st_atim.tv_sec) {
            swap_files(f + x, f + x + 1);
            continue;
        }
        if (
            (f[x].stat.st_atim.tv_sec == f[x + 1].stat.st_atim.tv_sec)
            && (f[x].stat.st_atim.tv_nsec < f[x + 1].stat.st_atim.tv_nsec)
        ) {
            swap_files(f + x, f + x + 1);
            continue;
        }
    }
}

static
void select_sort(struct directory_s *dir, options_t options)
{
    if ((options & OPT_DIR_ORDER) == OPT_DIR_ORDER)
        return;
    if (options & OPT_ACCESS_TIME
        && (options & OPT_TIME_SORT || !(options & OPT_LONG_FORMAT))
    ) {
        sort_access_time_files(dir);
        return;
    }
    if (options & OPT_TIME_SORT) {
        sort_time_files(dir);
        return;
    }
    sort_alpha_files(dir);
}

void sort_files(struct directory_s *dir, options_t options)
{
    if (dir == NULL || dir->files == NULL || dir->n_files == 0)
        return;
    select_sort(dir, options);
    if (options & OPT_REVERSE)
        reverse_files(dir);
}

void sort_paths(struct paths_s *paths)
{
    uint32_t size;
    uint32_t x;

    if (paths == NULL || paths->n == 0 || paths->paths == NULL)
        return;
    size = paths->n - 1;
    for (uint32_t i = 0; i < size * size; i++) {
        x = i % size;
        if (my_strcmp_cases(paths->paths[x], paths->paths[x + 1]))
            str_swap(paths->paths + x, paths->paths + x + 1);
    }
}
