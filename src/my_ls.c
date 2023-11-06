/*
** EPITECH PROJECT, 2023
** bob
** File description:
** bo
*/

#include <stdlib.h>
#include <dirent.h>
#include <stdint.h>
#include <stdio.h>
#include <stdbool.h>

#include "my.h"
#include "my_ls.h"

int return_ls_error(char *str)
{
    if (str == NULL)
        perror("my_ls");
    else
        my_printf("my_ls: %s", str);
    return ERR_RETURN;
}

static
int get_dirp(ls_t *ls)
{
    if (ls == NULL || ls->path == NULL)
        return return_ls_error("null pointer");
    if (ls->dirp != NULL)
        closedir(ls->dirp);
    ls->dirp = opendir(ls->path);
    if (ls->dirp == NULL)
        return return_ls_error(NULL);
    return 0;
}

static
uint32_t get_dir_size(ls_t *ls)
{
    struct dirent *directory = NULL;
    uint32_t size = 0;

    if (get_dirp(ls) == ERR_RETURN)
        return ERR_RETURN;
    do {
        directory = readdir(ls->dirp);
        if (directory == NULL)
            continue;
        if (!ls->show_hidden && my_str_startswith(directory->d_name, "."))
            continue;
        size++;
    } while (directory != NULL);
    return size;
}

static
int read_me_da_dir(ls_t *ls)
{
    struct dirent *directory = NULL;

    ls->n_files = get_dir_size(ls);
    ls->files = malloc(ls->n_files * sizeof(struct dirent));
    if (get_dirp(ls) == ERR_RETURN)
        return ERR_RETURN;
    do {
        directory = readdir(ls->dirp);
        if (directory == NULL)
            continue;
        if (!ls->show_hidden && my_str_startswith(directory->d_name, "."))
            continue;
        my_printf("%s\n", directory->d_name);
    } while (directory != NULL);
    return 0;
}

void clear_ls(ls_t *ls)
{
    if (ls == NULL)
        return;
    if (ls->dirp != NULL) {
        closedir(ls->dirp);
        ls->dirp = NULL;
    }
    if (ls->files != NULL) {
        free(ls->files);
        ls->files = NULL;
    }
}

int my_ls(int argc, char **argv)
{
    const char *path = (argc < 2) ? "." : argv[1];
    ls_t ls = {
        .path = path,
        .dirp = NULL,
        .show_hidden = false,
        .files = NULL,
        .n_files = 0,
    };
    int ret = read_me_da_dir(&ls);

    clear_ls(&ls);
    return ret;
}
