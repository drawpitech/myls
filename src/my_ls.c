/*
** EPITECH PROJECT, 2023
** bob
** File description:
** bo
*/

#include <stdlib.h>
#include <dirent.h>
#include <stdio.h>
#include <stdbool.h>

#include "my.h"
#include "my_ls.h"

int return_ls_error(void)
{
    perror("my_ls");
    return ERR_RETURN;
}

static
void read_me_da_dir(ls_t *ls)
{
    struct dirent *directory = NULL;

    if (ls == NULL || ls->dirp == NULL)
        return;
    do {
        directory = readdir(ls->dirp);
        if (directory == NULL)
            continue;
        if (!my_str_startswith(directory->d_name, "."))
            my_printf("%s\n", directory->d_name);
    } while (directory != NULL);
}

int my_ls(int argc, char **argv)
{
    const char *path = (argc < 2) ? "." : argv[1];
    ls_t ls = {
        .path = path,
        .dirp = opendir(path),
        .show_hidden = false,
    };

    if (ls.dirp == NULL)
        return return_ls_error();
    read_me_da_dir(&ls);
    closedir(ls.dirp);
    return EXIT_SUCCESS;
}
