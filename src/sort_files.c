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
#include <time.h>

#include "my.h"
#include "my_ls.h"

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
        swap(f + i, f + (dir->n_files - 1 - i), sizeof(struct file_s));
}

static
bool compare_filenames(void *left, void *right)
{
    return my_strcmp_cases(
        ((struct file_s *)left)->filename,
        ((struct file_s *)right)->filename
    );
}

static
bool compare_dates(struct timespec *left, struct timespec *right)
{
    return (
        (left->tv_sec < right->tv_sec) ||
        ((left->tv_sec == right->tv_sec) && (left->tv_nsec < right->tv_nsec))
    );
}

static
bool compare_mtim(void *left, void *right)
{
    return compare_dates(
        &((struct file_s *)left)->stat.st_mtim,
        &((struct file_s *)right)->stat.st_mtim
    );
}

static
bool compare_atim(void *left, void *right)
{
    return compare_dates(
        &((struct file_s *)left)->stat.st_atim,
        &((struct file_s *)right)->stat.st_atim
    );
}

static
compar_func_t *select_sort(options_t options)
{
    if ((options & OPT_DIR_ORDER) == OPT_DIR_ORDER)
        return NULL;
    if (options & OPT_ACCESS_TIME
        && (options & OPT_TIME_SORT || !(options & OPT_LONG_FORMAT))
    )
        return &compare_atim;
    if (options & OPT_TIME_SORT)
        return &compare_mtim;
    return &compare_filenames;
}

void sort_files(struct directory_s *dir, options_t options)
{
    compar_func_t *func;

    if (dir == NULL || dir->files == NULL || dir->n_files == 0)
        return;
    func = select_sort(options);
    if (func != NULL)
        bubble_sort(
            dir->n_files, dir->files,
            sizeof(struct file_s), func
        );
    if (options & OPT_REVERSE)
        reverse_files(dir);
}

static
bool compare_paths(void *left, void *right)
{
    return (my_strcmp_cases(*(char **)left, *(char **)right));
}

void sort_paths(struct paths_s *paths)
{
    if (paths == NULL)
        return;
    bubble_sort(
        paths->n, paths->paths,
        sizeof(char *), &compare_paths);
}
