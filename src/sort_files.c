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
bool compare_mtim(void *left, void *right)
{
    struct timespec tl = ((struct file_s *)left)->stat.st_mtim;
    struct timespec tr = ((struct file_s *)right)->stat.st_mtim;

    return (
        (tl.tv_sec < tr.tv_sec)
        || ((tl.tv_sec == tr.tv_sec) && (tl.tv_nsec < tr.tv_nsec))
    );
}

static
bool compare_atim(void *left, void *right)
{
    struct timespec tl = ((struct file_s *)left)->stat.st_atim;
    struct timespec tr = ((struct file_s *)right)->stat.st_atim;

    return (
        (tl.tv_sec < tr.tv_sec)
        || ((tl.tv_sec == tr.tv_sec) && (tl.tv_nsec < tr.tv_nsec))
    );
}

static
void select_sort(struct directory_s *dir, options_t options)
{
    if ((options & OPT_DIR_ORDER) == OPT_DIR_ORDER)
        return;
    if (options & OPT_ACCESS_TIME
        && (options & OPT_TIME_SORT || !(options & OPT_LONG_FORMAT))
    ) {
        bubble_sort(
            dir->n_files, dir->files,
            sizeof(struct file_s), &compare_atim);
        return;
    }
    if (options & OPT_TIME_SORT) {
        bubble_sort(
            dir->n_files, dir->files,
            sizeof(struct file_s), &compare_mtim);
        return;
    }
    bubble_sort(
        dir->n_files, dir->files,
        sizeof(struct file_s), &compare_filenames);
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
            swap(paths->paths + x, paths->paths + x + 1, sizeof(char *));
    }
}
