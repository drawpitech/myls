/*
** EPITECH PROJECT, 2023
** my_ls
** File description:
** print
*/

#include <limits.h>
#include <stdbool.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <sys/types.h>

#include "colors.h"
#include "my.h"

#include "../my_ls.h"
#include "print.h"

static
void recursive_print(ls_t *ls, struct directory_s *dir)
{
    struct file_s *file;
    struct directory_s rec_dir = { 0 };

    if (!(ls->options & OPT_RECURSIVE))
        return;
    for (uint32_t i = 0; i < dir->n_files; i++) {
        file = dir->files + i;
        if (!file->valid || !S_ISDIR(file->stat.st_mode))
            continue;
        if (my_strcmp(file->filename, ".") == 0
            || my_strcmp(file->filename, "..") == 0)
            continue;
        get_fullpath(dir->path, file->filename, rec_dir.path);
        print_dir(ls, true, true, &rec_dir);
    }
}

static
void print_files(
    struct directory_s *dir,
    ls_t *ls,
    bool same_dir
)
{
    sort_files(dir, ls->options);
    if (ls->options & OPT_LONG_FORM)
        ls_output_long(dir, same_dir, ls->options);
    else
        ls_output_normal(dir, ls->options);
    recursive_print(ls, dir);
    clear_dir(dir);
}

static
void print_classify(mode_t mode)
{
    switch (mode & S_IFMT) {
        case S_IFDIR:
            my_putchar('/');
            return;
        case S_IFIFO:
            my_putchar('|');
            return;
        case S_IFLNK:
            my_putchar('@');
            return;
        case S_IFSOCK:
            my_putchar('=');
            return;
        case S_IFREG:
            if (mode & S_IXUSR)
                my_putchar('*');
            return;
    }
}

static
bool print_color(
    struct directory_s const *dir,
    struct file_s const *file)
{
    if (my_strcmp(file->filename, ".") == 0)
        my_putstr("\x1b[0m");
    return (FT_TABLE[file->stat.st_mode & S_IFMT].func != NULL)
        ? FT_TABLE[file->stat.st_mode & S_IFMT].func(dir, file)
        : false;
}

void print_filename(
    struct directory_s const *dir,
    struct file_s const *file,
    options_t options)
{
    bool need_quotes = (my_strstr(file->filename, " ") != NULL);
    bool need_color = (options & OPT_WTH_COLOR);

    if (need_color)
        need_color = print_color(dir, file);
    if (!need_quotes)
        my_printf("%s", file->filename);
    else
        my_printf("'%s", file->filename);
    if (options & OPT_CLASS_CHR)
        print_classify(file->stat.st_mode);
    if (need_quotes)
        my_putchar('\'');
    if (need_color)
        my_putstr(C_RESET);
}

int print_dir(ls_t *ls, bool show_path, bool line_jmp, struct directory_s *dir)
{
    int ret = RET_VALID;

    if (ls == NULL || dir == NULL)
        return return_ls_error("null ptr");
    ret = get_files_in_dir(dir, ls->options);
    if (show_path)
        my_printf("%s%s:\n", (line_jmp) ? "\n" : "", dir->path);
    print_files(dir, ls, true);
    return ret;
}

int print_alone_files(ls_t *ls)
{
    int ret = RET_VALID;
    struct directory_s *dir;

    if (ls == NULL)
        return return_ls_error("null ptr");
    dir = &ls->dir;
    dir->path[0] = '\0';
    dir->dirp = NULL;
    dir->n_files = ls->alone_files.n;
    if (dir->n_files == 0)
        return 0;
    dir->files = malloc(dir->n_files * sizeof(struct file_s));
    for (uint32_t i = 0; i < dir->n_files; i++)
        ret |= set_file(".", ls->alone_files.paths[i], dir->files + i);
    print_files(dir, ls, false);
    return ret;
}
