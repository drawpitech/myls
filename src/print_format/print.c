/*
** EPITECH PROJECT, 2023
** my_ls
** File description:
** print
*/

#include <limits.h>
#include <stdbool.h>
#include <stdlib.h>

#include "my.h"
#include "my_ls.h"

static
void recursive_print(ls_t *ls, struct directory_s *dir)
{
    struct file_s *file;
    struct directory_s rec_dir = { 0 };

    if (!ls->params.recursive)
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
    sort_files(dir, &ls->params);
    if (ls->params.long_format)
        ls_output_long(dir, same_dir);
    else
        ls_output_normal(dir);
    recursive_print(ls, dir);
    clear_dir(dir);
}

int print_dir(ls_t *ls, bool show_path, bool line_jmp, struct directory_s *dir)
{
    if (ls == NULL || dir == NULL)
        return return_ls_error("null ptr");
    if (get_files_in_dir(dir, &ls->params) == ERR_RETURN) {
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
