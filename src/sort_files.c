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
int my_strcmp_cases(char *str1, char *str2)
{
    static char filename1[PATH_MAX];
    static char filename2[PATH_MAX];

    my_strcpy(filename1, get_ptr(str1));
    my_strcpy(filename2, get_ptr(str2));
    if (filename1[0] == '\0' && filename2[0] == '\0')
        return my_strlen(str1) - my_strlen(str2);
    my_strlowcase(filename1);
    my_strlowcase(filename2);
    return my_strcmp(filename1, filename2);
}

static
int compare_filenames(void *left, void *right)
{
    return my_strcmp_cases(
        ((struct file_s *)left)->filename,
        ((struct file_s *)right)->filename
    );
}

static
int compare_dates(struct timespec *left, struct timespec *right)
{
    return (int)((right->tv_sec != left->tv_sec)
        ? (right->tv_sec - left->tv_sec)
        : (right->tv_nsec - left->tv_nsec)
    );
}

static
int compare_mtim(void *left, void *right)
{
    return compare_dates(
        &((struct file_s *)left)->stat.st_mtim,
        &((struct file_s *)right)->stat.st_mtim
    );
}

static
int compare_atim(void *left, void *right)
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
    if (options & OPT_ACCS_TIME
        && (options & OPT_TIME_SORT || !(options & OPT_LONG_FORM))
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
        my_qsort(
            dir->files, dir->n_files,
            sizeof(struct file_s), func
        );
    if (options & OPT_REV_ORDER)
        reverse_arr(dir->n_files, dir->files, sizeof(struct file_s));
}

static
int compare_paths(void *left, void *right)
{
    return (my_strcmp_cases(*(char **)left, *(char **)right));
}

void sort_paths(struct paths_s *paths)
{
    if (paths == NULL)
        return;
    my_qsort(
        paths->paths, paths->n,
        sizeof(char *), &compare_paths);
}
