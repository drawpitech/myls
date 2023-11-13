/*
** EPITECH PROJECT, 2023
** my_ls
** File description:
** print
*/

#include <limits.h>
#include <stdbool.h>
#include <stdlib.h>
#include <sys/types.h>

#include "my.h"
#include "my_ls.h"
#include "sys/stat.h"

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
    if (ls->options & OPT_LONG_FORMAT)
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
bool print_color(mode_t mode)
{
    switch (mode & S_IFMT) {
        case S_IFDIR:
            my_printf("%s", "\x1b[1;34m");
            return true;
        case S_IFCHR:
            my_printf("%s%s", "\x1b[40m", "\x1b[1;33m");
            return true;
        case S_IFLNK:
            my_printf("%s", "\x1b[1;36m");
            return true;
        case S_IFREG:
            if (mode & S_IXUSR)
                my_printf("%s", "\x1b[1;32m");
            return (mode & S_IXUSR);
    }
    return false;
}

void print_filename(struct file_s *file, options_t options)
{
    bool need_quotes = (my_strstr(file->filename, " ") != NULL);
    bool need_color = (options & OPT_COLOR);

    if (need_color)
        need_color = print_color(file->stat.st_mode);
    if (!need_quotes)
        my_printf("%s", file->filename);
    else
        my_printf("'%s", file->filename);
    if (options & OPT_CLASSIFY)
        print_classify(file->stat.st_mode);
    if (need_quotes)
        my_putchar('\'');
    if (need_color)
        my_putstr("\x1b[0m");
}

int print_dir(ls_t *ls, bool show_path, bool line_jmp, struct directory_s *dir)
{
    if (ls == NULL || dir == NULL)
        return return_ls_error("null ptr");
    if (get_files_in_dir(dir, ls->options) == ERR_RETURN) {
        clear_dir(dir);
        return ERR_RETURN;
    }
    if (show_path)
        my_printf("%s%s:\n", (line_jmp) ? "\n" : "", dir->path);
    print_files(dir, ls, true);
    return 0;
}

int print_alone_files(ls_t *ls)
{
    int ret = 0;
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
    for (uint32_t i = 0; i < dir->n_files; i++) {
        my_strcpy(dir->files[i].filename, ls->alone_files.paths[i]);
        ret |= set_file(".", dir->files + i);
    }
    print_files(dir, ls, false);
    return ret;
}
