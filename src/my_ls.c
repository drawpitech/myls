/*
** EPITECH PROJECT, 2023
** my_ls
** File description:
** my_ls
*/

#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

#include "my.h"
#include "my_ls.h"

int return_ls_error(char *str)
{
    if (str == NULL) {
        perror("my_ls");
    } else {
        return_err("my_ls: ");
        return_err(str);
        return_err("\n");
    }
    return ERR_RETURN;
}

static
void print_files(ls_t *ls, bool same_dir)
{
    sort_files(ls);
    if (ls->params.long_format)
        ls_output_long(&ls->dir, same_dir);
    else
        ls_output_normal(&ls->dir);
    clear_dir(&ls->dir);
}

static
int print_dir(ls_t *ls, bool show_path, bool line_jmp, struct directory_s *dir)
{
    if (get_files_in_dir(dir, &ls->params) == ERR_RETURN) {
        clear_dir(dir);
        return ERR_RETURN;
    }
    if (show_path)
        my_printf("%s%s:\n", (line_jmp) ? "\n" : "", ls->dir.path);
    print_files(ls, true);
    return 0;
}

static
int print_alone_files(ls_t *ls)
{
    int ret = 0;

    ls->dir.path[0] = '\0';
    ls->dir.dirp = NULL;
    ls->dir.n_files = ls->alone_files.n;
    if (ls->dir.n_files == 0)
        return 0;
    ls->dir.files = malloc(ls->dir.n_files * sizeof(struct file_s));
    for (uint32_t i = 0; i < ls->dir.n_files; i++) {
        my_strcpy(ls->dir.files[i].filename, ls->alone_files.paths[i]);
        ret |= set_file(".", ls->dir.files + i);
    }
    print_files(ls, false);
    return ret;
}

static
int print_ls(ls_t *ls)
{
    int ret = 0;
    bool has_af = (ls->alone_files.n != 0);

    if (!has_af && (ls->paths.n == 1 || ls->params.directories)) {
        my_strcpy(ls->dir.path, ls->paths.paths[0]);
        return print_dir(ls, false, false, &ls->dir);
    }
    ret |= print_alone_files(ls);
    for (uint32_t i = 0; i < ls->paths.n; i++) {
        my_strcpy(ls->dir.path, ls->paths.paths[i]);
        ret |= print_dir(ls, true, (has_af || i != 0), &ls->dir);
    }
    return ret;
}

int my_ls(int argc, char **argv)
{
    uint32_t uargc = (uint32_t)argc;
    char *paths[uargc];
    char *alone_files[uargc];
    ls_t ls = { 0 };
    int ret = 0;

    if (argc < 1 || argv == NULL)
        return return_ls_error("invalid args");
    ls.paths.paths = paths;
    ls.alone_files.paths = alone_files;
    get_params(&ls, uargc, argv);
    ret |= print_ls(&ls);
    clear_ls(&ls);
    return ret;
}
