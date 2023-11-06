/*
** EPITECH PROJECT, 2023
** bob
** File description:
** bo
*/

#include <stdlib.h>
#include <dirent.h>
#include <stdio.h>

#include "my.h"
#include "my_ls.h"

int return_ls_error(void)
{
    perror("my_ls");
    return ERR_RETURN;
}

static
void read_me_da_dir(DIR *dirp)
{
    struct dirent *directory = NULL;

    if (dirp == NULL)
        return;
    do {
        directory = readdir(dirp);
        if (directory == NULL)
            continue;
        my_printf("%s\n", directory->d_name);
    } while (directory != NULL);
}

int my_ls(int argc, char **argv)
{
    const char *path = (argc < 2) ? "." : argv[1];
    DIR *dirp = opendir(path);

    if (dirp == NULL)
        return return_ls_error();
    read_me_da_dir(dirp);
    closedir(dirp);
    return EXIT_SUCCESS;
}
